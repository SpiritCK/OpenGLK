// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <iostream>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/norm.hpp>
using namespace glm;

#include <common/shader.hpp>
#include <common/texture.hpp>
#include <common/controls.hpp>
#include <common/objloader.hpp>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define SCREEN_TITLE "Mobil bagus"
#define VERTEX_SHADER_FILE "uas/shader/Car.vertexshader"
#define FRAGMENT_SHADER_FILE "uas/shader/Car.fragmentshader"
#define PARTICLE_VERTEX_SHADER_FILE "uas/shader/Particle.vertexshader"
#define PARTICLE_FRAGMENT_SHADER_FILE "uas/shader/Particle.fragmentshader"
#define MODEL_FILE "uas/test.obj"
#define TEXTURE_FILE "uas/1lexus.dds"
#define MAX_PARTICLE_SMOKE 10000
#define MAX_PARTICLE_RAIN 10000

// CPU representation of a particle
struct Particle{
	glm::vec3 pos, speed;
	unsigned char r,g,b,a; // Color
	float size, angle, weight;
	float life; // Remaining life of the particle. if <0 : dead and unused.
	float cameradistance; // *Squared* distance to the camera. if dead : -1.0f

	bool operator<(const Particle& that) const {
		// Sort in reverse order : far particles drawn first.
		return this->cameradistance > that.cameradistance;
	}
};

Particle SmokeContainer[MAX_PARTICLE_SMOKE];
int LastUsedSmoke = 0;
Particle RainContainer[MAX_PARTICLE_RAIN];
int LastUsedRain = 0;

// Finds a Particle in SmokeContainer which isn't used yet.
// (i.e. life < 0);
int FindUnusedParticle(Particle container[], int &lastUsed, int max){

	for(int i=lastUsed; i<max; i++){
		if (container[i].life < 0){
			lastUsed = i;
			return i;
		}
	}

	for(int i=0; i<lastUsed; i++){
		if (container[i].life < 0){
			lastUsed = i;
			return i;
		}
	}

	return 0; // All particles are taken, override the first one
}

void SortParticles(Particle container[], int max){
	std::sort(&container[0], &container[max]);
}

bool isHitCar(vec3 &pos) {
  if (pos.x > -1.13f && pos.x < -0.7f && pos.z < 0.43f && pos.z > -0.43f && (1.2f*pos.x - 4.3f*pos.y + 1.786f) > 0) {
    pos.y = (1.2f*pos.x + 1.786f) / 4.3f;
    return true;
  }
  else if (pos.x > -0.7f && pos.x < -0.23f && (0.8f*pos.x + 4.7f*pos.z - 1.461f) < 0 && (0.8f*pos.x - 4.7f*pos.z - 1.461f) < 0 && (2.1f*pos.x - 4.7f*pos.y + 2.504f) > 0) {
    pos.y = (2.1f*pos.x + 2.504f) / 4.7f;
    return true;
  }
  else if (pos.x > -0.23f && pos.x < 0.43f && pos.z < 0.35f && pos.z > -0.35f && (0.1f*pos.x - 3.3f*pos.y + 1.442f) > 0) {
    pos.y = (0.1f*pos.x + 1.442f) / 3.3f;
    return true;
  }
  else if (pos.x > 0.43f && pos.x < 1.0f && (0.9f*pos.x + 5.7f*pos.z + 1.608f) > 0 && (0.9f*pos.x - 5.7f*pos.z + 1.608f) > 0 && (pos.x + 3.0f*pos.y - 1.78f) < 0) {
    pos.y = (pos.x - 1.78f) / - 3.0f;
    return true;
  }
  else if (pos.x > 1.0f && pos.x < 1.2f && pos.z < 0.44f && pos.z > -0.44f && (pos.x + 10.0f*pos.y - 3.6f) > 0) {
    pos.y = (pos.x - 3.6f) / - 10.0f;
    return true;
  }
  return false;
}

int main( void )
{
	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE, NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    // Hide the mouse and enable unlimited mouvement
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    // Set the mouse at the center of the screen
    glfwPollEvents();
    glfwSetCursorPos(window, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS); 

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders( VERTEX_SHADER_FILE, FRAGMENT_SHADER_FILE );

	// Get a handle for our "MVP" uniform
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");
  GLuint ViewMatrixID = glGetUniformLocation(programID,"V");
  GLuint ModelMatrixID = glGetUniformLocation(programID, "M");

	// Load the texture
	GLuint Texture = loadDDS(TEXTURE_FILE);
	
	// Get a handle for our "myTextureSampler" uniform
	GLuint TextureID  = glGetUniformLocation(programID, "myTextureSampler");
  GLuint LightID = glGetUniformLocation(programID, "LightPosition_worldspace");
  GLuint LightAttrib = glGetUniformLocation(programID, "LightPower");
  GLint posAttrib = glGetAttribLocation(programID, "pos");
	GLint colAttrib = glGetAttribLocation(programID, "vertexUV");
  GLint normalAttrib = glGetAttribLocation(programID, "vertexNormal_modelspace");

	// Read our .obj file
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals; // Won't be used at the moment.
	bool res = loadOBJ(MODEL_FILE, vertices, uvs, normals);

	// Load it into a VBO

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

	GLuint normalbuffer;
	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
  
  glm::vec3 lightPos = glm::vec3(4,4,4);
  float lightPower = 50.0;
	
	
	// Create and compile particle shader program
	GLuint particleProgramID = LoadShaders( PARTICLE_VERTEX_SHADER_FILE, PARTICLE_FRAGMENT_SHADER_FILE );

	// Vertex shader
	GLuint CameraRight_worldspace_ID  = glGetUniformLocation(particleProgramID, "CameraRight_worldspace");
	GLuint CameraUp_worldspace_ID  = glGetUniformLocation(particleProgramID, "CameraUp_worldspace");
	GLuint ViewProjMatrixID = glGetUniformLocation(particleProgramID, "VP");
	
  GLint squareAttrib = glGetAttribLocation(particleProgramID, "squareVertices");
	GLint xyzsAttrib = glGetAttribLocation(particleProgramID, "xyzs");
  GLint colorAttrib = glGetAttribLocation(particleProgramID, "color");
  
	static GLfloat* g_smoke_particule_position_size_data = new GLfloat[MAX_PARTICLE_SMOKE * 4];
	static GLubyte* g_smoke_particule_color_data         = new GLubyte[MAX_PARTICLE_SMOKE * 4];

	for(int i=0; i<MAX_PARTICLE_SMOKE; i++){
		SmokeContainer[i].life = -1.0f;
		SmokeContainer[i].cameradistance = -1.0f;
	}

	// The VBO containing the 4 vertices of the particles.
	// Thanks to instancing, they will be shared by all particles.
	static const GLfloat g_smoke_vertex_buffer_data[] = { 
		 /*-0.005f, -0.005f, 0.0f,
		  0.005f, -0.005f, 0.0f,
		 -0.005f,  0.005f, 0.0f,
		  0.005f,  0.005f, 0.0f,*/
		  
		 -0.005f, -0.005f, -0.005f,
		  0.005f, -0.005f, -0.005f,
		 -0.005f,  0.005f, -0.005f,
		  0.005f,  0.005f, -0.005f,
		  0.005f,  0.005f,  0.005f,
		  0.005f, -0.005f, -0.005f,
		  0.005f, -0.005f,  0.005f,
		 -0.005f, -0.005f, -0.005f,
		 -0.005f, -0.005f,  0.005f,
		 -0.005f,  0.005f, -0.005f,
		 -0.005f,  0.005f,  0.005f,
		  0.005f,  0.005f,  0.005f,
		 -0.005f, -0.005f,  0.005f,
		  0.005f, -0.005f,  0.005f,
	};
	
	static GLfloat* g_rain_particule_position_size_data = new GLfloat[MAX_PARTICLE_SMOKE * 4];
	static GLubyte* g_rain_particule_color_data         = new GLubyte[MAX_PARTICLE_SMOKE * 4];

	for(int i=0; i<MAX_PARTICLE_RAIN; i++){
		RainContainer[i].life = -1.0f;
		RainContainer[i].cameradistance = -1.0f;
	}

	// The VBO containing the 4 vertices of the particles.
	// Thanks to instancing, they will be shared by all particles.
	static const GLfloat g_rain_vertex_buffer_data[] = { 
		 -0.005f, -0.01f, -0.005f,
		  0.005f, -0.01f, -0.005f,
		 -0.005f,  0.01f, -0.005f,
		  0.005f,  0.01f, -0.005f,
		  0.005f,  0.01f,  0.005f,
		  0.005f, -0.01f, -0.005f,
		  0.005f, -0.01f,  0.005f,
		 -0.005f, -0.01f, -0.005f,
		 -0.005f, -0.01f,  0.005f,
		 -0.005f,  0.01f, -0.005f,
		 -0.005f,  0.01f,  0.005f,
		  0.005f,  0.01f,  0.005f,
		 -0.005f, -0.01f,  0.005f,
		  0.005f, -0.01f,  0.005f,
	};
	
	GLuint billboard_vertex_buffer;
	glGenBuffers(1, &billboard_vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, billboard_vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_smoke_vertex_buffer_data), g_smoke_vertex_buffer_data, GL_STATIC_DRAW);

	// The VBO containing the positions and sizes of the particles
	GLuint particles_position_buffer;
	glGenBuffers(1, &particles_position_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
	// Initialize with empty (NULL) buffer : it will be updated later, each frame.
	glBufferData(GL_ARRAY_BUFFER, MAX_PARTICLE_SMOKE * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);

	// The VBO containing the colors of the particles
	GLuint particles_color_buffer;
	glGenBuffers(1, &particles_color_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, particles_color_buffer);
	// Initialize with empty (NULL) buffer : it will be updated later, each frame.
	glBufferData(GL_ARRAY_BUFFER, MAX_PARTICLE_SMOKE * 4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW);
  

  setPosition(0, 1, 6);

	double lastTime = glfwGetTime();
	do{
	  // Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		double currentTime = glfwGetTime();
		double delta = currentTime - lastTime;
		lastTime = currentTime;


		computeMatricesFromInputs();
		glm::mat4 ProjectionMatrix = getProjectionMatrix();
		glm::mat4 ViewMatrix = getViewMatrix();
		glm::vec3 CameraPosition(glm::inverse(ViewMatrix)[3]);
		glm::mat4 ViewProjectionMatrix = ProjectionMatrix * ViewMatrix;
		glm::mat4 ModelMatrix = glm::mat4(1.0);
		glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;





		// Use our shader
		glUseProgram(programID);
		
		if (glfwGetKey( window, GLFW_KEY_Q ) == GLFW_PRESS){
		  if (lightPower < 100) lightPower += 1;
	  } else if (glfwGetKey( window, GLFW_KEY_W ) == GLFW_PRESS){
		  if (lightPower > 0) lightPower -= 1;
	  }
    glUniform1f(LightAttrib, lightPower);

		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
    glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
    glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);
    
    // Send light position
    vec4 tempLight = glm::rotate(glm::mat4(1.0f), (float)glfwGetTime()*(-2), glm::vec3(0.0f, 0.0f, 1.0f)) * vec4(lightPos, 1.0);
    glUniform3f(LightID, tempLight.x, tempLight.y, tempLight.z);

		// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture);
		// Set our "myTextureSampler" sampler to use Texture Unit 0
		glUniform1i(TextureID, 0);

		// 1rst attribute buffer : vertices
	  glEnableVertexAttribArray(posAttrib);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			posAttrib,          // attribute
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// 2nd attribute buffer : UVs
	  glEnableVertexAttribArray(colAttrib);

		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glVertexAttribPointer(
			colAttrib,                        // attribute
			2,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		// 3rd attribute buffer : Normals
	  glEnableVertexAttribArray(normalAttrib);
		glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
		glVertexAttribPointer(
			normalAttrib,                     // attribute
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		// Draw the triangles !
		glDrawArrays(GL_TRIANGLES, 0, vertices.size() );

		glDisableVertexAttribArray(posAttrib);
		glDisableVertexAttribArray(colAttrib);
		glDisableVertexAttribArray(normalAttrib);



    // Smoke particle
		// Generate 10 new particule each millisecond,
		// but limit this to 16 ms (60 fps), or if you have 1 long frame (1sec),
		// newparticles will be huge and the next frame even longer.
		int newparticles = (int)(delta*1000.0);
		if (newparticles > (int)(0.016f*1000.0))
			newparticles = (int)(0.016f*1000.0);
		
		for(int i=0; i<newparticles; i++){
			int particleIndex = FindUnusedParticle(SmokeContainer, LastUsedSmoke, MAX_PARTICLE_SMOKE);
			SmokeContainer[particleIndex].life = 5.0f; // This particle will live 5 seconds.
			SmokeContainer[particleIndex].pos = glm::vec3(1.25f,-0.17f,-0.2f);

			float spread = 1.5f;
			glm::vec3 maindir = glm::vec3(8.0f, 0.0f, 0.0f);
			glm::vec3 randomdir = glm::vec3(
				(rand()%2000 - 1000.0f)/1000.0f,
				(rand()%2000 - 1000.0f)/1000.0f,
				(rand()%2000 - 1000.0f)/1000.0f
			);
			
			SmokeContainer[particleIndex].speed = (maindir + randomdir*spread) * 0.015f;

			SmokeContainer[particleIndex].r = 80;
			SmokeContainer[particleIndex].g = 80;
			SmokeContainer[particleIndex].b = 80;
			SmokeContainer[particleIndex].a = 40;

			SmokeContainer[particleIndex].size = (rand()%1000)/500.0f + 0.1f;
			
		}

		// Simulate all particles
		int ParticlesCount = 0;
		for(int i=0; i<MAX_PARTICLE_SMOKE; i++){

			Particle& p = SmokeContainer[i]; // shortcut

			if(p.life > 0.0f){

				// Decrease life
				p.life -= delta;
				if (p.life > 0.0f){

					// Simulate simple physics : gravity only, no collisions
					//p.speed += glm::vec3(0.0f,-9.81f, 0.0f) * (float)delta * 0.5f;
			    p.speed += glm::vec3(-0.01f, 0.015f, 0.0f) * (float)delta;
				  if (p.speed.x < 0)
			      p.speed.x = 0.0f;
					p.pos += p.speed * (float)delta;
					p.cameradistance = glm::length2( p.pos - CameraPosition );
					//SmokeContainer[i].pos += glm::vec3(0.0f,10.0f, 0.0f) * (float)delta;

					// Fill the GPU buffer
					g_smoke_particule_position_size_data[4*ParticlesCount+0] = p.pos.x;
					g_smoke_particule_position_size_data[4*ParticlesCount+1] = p.pos.y;
					g_smoke_particule_position_size_data[4*ParticlesCount+2] = p.pos.z;
												   
					g_smoke_particule_position_size_data[4*ParticlesCount+3] = p.size;
												   
					g_smoke_particule_color_data[4*ParticlesCount+0] = p.r;
					g_smoke_particule_color_data[4*ParticlesCount+1] = p.g;
					g_smoke_particule_color_data[4*ParticlesCount+2] = p.b;
					g_smoke_particule_color_data[4*ParticlesCount+3] = p.a;

				}else{
					// Particles that just died will be put at the end of the buffer in SortParticles();
					p.cameradistance = -1.0f;
				}

				ParticlesCount++;

			}
		}

		SortParticles(SmokeContainer, MAX_PARTICLE_SMOKE);


		//printf("%d ",ParticlesCount);


		// Update the buffers that OpenGL uses for rendering.
		// There are much more sophisticated means to stream data from the CPU to the GPU, 
		// but this is outside the scope of this tutorial.
		// http://www.opengl.org/wiki/Buffer_Object_Streaming

	  glBindBuffer(GL_ARRAY_BUFFER, billboard_vertex_buffer);
	  glBufferData(GL_ARRAY_BUFFER, sizeof(g_smoke_vertex_buffer_data), g_smoke_vertex_buffer_data, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
		glBufferData(GL_ARRAY_BUFFER, MAX_PARTICLE_SMOKE * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW); // Buffer orphaning, a common way to improve streaming perf. See above link for details.
		glBufferSubData(GL_ARRAY_BUFFER, 0, ParticlesCount * sizeof(GLfloat) * 4, g_smoke_particule_position_size_data);

		glBindBuffer(GL_ARRAY_BUFFER, particles_color_buffer);
		glBufferData(GL_ARRAY_BUFFER, MAX_PARTICLE_SMOKE * 4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW); // Buffer orphaning, a common way to improve streaming perf. See above link for details.
		glBufferSubData(GL_ARRAY_BUFFER, 0, ParticlesCount * sizeof(GLubyte) * 4, g_smoke_particule_color_data);


		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Use our shader
		glUseProgram(particleProgramID);

		// Same as the billboards tutorial
		glUniform3f(CameraRight_worldspace_ID, ViewMatrix[0][0], ViewMatrix[1][0], ViewMatrix[2][0]);
		glUniform3f(CameraUp_worldspace_ID   , ViewMatrix[0][1], ViewMatrix[1][1], ViewMatrix[2][1]);

		glUniformMatrix4fv(ViewProjMatrixID, 1, GL_FALSE, &ViewProjectionMatrix[0][0]);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(squareAttrib);
		glBindBuffer(GL_ARRAY_BUFFER, billboard_vertex_buffer);
		glVertexAttribPointer(
			squareAttrib,                  // attribute. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);
		
		// 2nd attribute buffer : positions of particles' centers
		glEnableVertexAttribArray(xyzsAttrib);
		glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
		glVertexAttribPointer(
			xyzsAttrib,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			4,                                // size : x + y + z + size => 4
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		// 3rd attribute buffer : particles' colors
		glEnableVertexAttribArray(colorAttrib);
		glBindBuffer(GL_ARRAY_BUFFER, particles_color_buffer);
		glVertexAttribPointer(
			colorAttrib,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			4,                                // size : r + g + b + a => 4
			GL_UNSIGNED_BYTE,                 // type
			GL_TRUE,                          // normalized?    *** YES, this means that the unsigned char[4] will be accessible with a vec4 (floats) in the shader ***
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		// These functions are specific to glDrawArrays*Instanced*.
		// The first parameter is the attribute buffer we're talking about.
		// The second parameter is the "rate at which generic vertex attributes advance when rendering multiple instances"
		// http://www.opengl.org/sdk/docs/man/xhtml/glVertexAttribDivisor.xml
		glVertexAttribDivisor(squareAttrib, 0); // particles vertices : always reuse the same 4 vertices -> 0
		glVertexAttribDivisor(xyzsAttrib, 1); // positions : one per quad (its center)                 -> 1
		glVertexAttribDivisor(colorAttrib, 1); // color : one per quad                                  -> 1

		// Draw the particules !
		// This draws many times a small triangle_strip (which looks like a quad).
		// This is equivalent to :
		// for(i in ParticlesCount) : glDrawArrays(GL_TRIANGLE_STRIP, 0, 4), 
		// but faster.
		glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 14, ParticlesCount); 


		glVertexAttribDivisor(xyzsAttrib, 0);
		glVertexAttribDivisor(colorAttrib, 0);
		glDisableVertexAttribArray(squareAttrib);
		glDisableVertexAttribArray(xyzsAttrib);
		glDisableVertexAttribArray(colorAttrib);
		
		
		
		// Rain particle
		// Generate 10 new particule each millisecond,
		// but limit this to 16 ms (60 fps), or if you have 1 long frame (1sec),
		// newparticles will be huge and the next frame even longer.
		newparticles = (int)(delta*1000.0);
		if (newparticles > (int)(0.016f*1000.0))
			newparticles = (int)(0.016f*1000.0);
	  
		for(int i=0; i<newparticles; i++){
			int particleIndex = FindUnusedParticle(RainContainer, LastUsedRain, MAX_PARTICLE_RAIN);
			RainContainer[particleIndex].life = 5.0f; // This particle will live 5 seconds.
			RainContainer[particleIndex].pos = glm::vec3(
				(rand()%2000 - 1000.0f)/1000.0f * 1.5f,
				(rand()%2000 - 1000.0f)/10000.0f + 1.3f,
				(rand()%2000 - 1000.0f)/1000.0f * 1.5f
			);

			glm::vec3 maindir = glm::vec3(0.0f, 0.0f, 0.0f);
			glm::vec3 randomdir = glm::vec3(
				0.0f,
				(rand()%2000 - 1000.0f)/10000.0f + 0.1f,
				0.0f
			);
			
			RainContainer[particleIndex].speed = (maindir + randomdir) * 0.015f;

			RainContainer[particleIndex].r = 10;
			RainContainer[particleIndex].g = 10;
			RainContainer[particleIndex].b = 255;
			RainContainer[particleIndex].a = 160;

			RainContainer[particleIndex].size = (rand()%1000)/500.0f + 0.1f;
			
		}

		// Simulate all particles
		ParticlesCount = 0;
		for(int i=0; i<MAX_PARTICLE_RAIN; i++){

			Particle& p = RainContainer[i]; // shortcut

			if(p.life > 0.0f){

				// Decrease life
				p.life -= delta;
				if (p.pos.y < -1.5f)
				  p.life = -1.0f;
				if (p.life > 0.0f){

					// Simulate simple physics : gravity only, no collisions
					p.speed += glm::vec3(0.0f,-9.18f, 0.0f) * (float)delta * 0.5f;
			    p.pos += p.speed * (float)delta;
			    if (isHitCar(p.pos)) {
			      p.speed *= -0.3f;
			      float spread = 1.5f;
			      glm::vec3 randomdir = glm::vec3(
				      (rand()%2000 - 1000.0f)/5000.0f,
				      (rand()%2000 - 1000.0f)/5000.0f + 0.2f,
				      (rand()%2000 - 1000.0f)/5000.0f
			      );
			      p.speed += randomdir*spread;
			      p.life = (p.life < 1.0f) ? p.life : 1.0f;
			    }
					p.cameradistance = glm::length2( p.pos - CameraPosition );
					//RainContainer[i].pos += glm::vec3(0.0f,10.0f, 0.0f) * (float)delta;

					// Fill the GPU buffer
					g_rain_particule_position_size_data[4*ParticlesCount+0] = p.pos.x;
					g_rain_particule_position_size_data[4*ParticlesCount+1] = p.pos.y;
					g_rain_particule_position_size_data[4*ParticlesCount+2] = p.pos.z;
												   
					g_rain_particule_position_size_data[4*ParticlesCount+3] = p.size;
												   
					g_rain_particule_color_data[4*ParticlesCount+0] = p.r;
					g_rain_particule_color_data[4*ParticlesCount+1] = p.g;
					g_rain_particule_color_data[4*ParticlesCount+2] = p.b;
					g_rain_particule_color_data[4*ParticlesCount+3] = p.a;

				}else{
					// Particles that just died will be put at the end of the buffer in SortParticles();
					p.cameradistance = -1.0f;
				}

				ParticlesCount++;

			}
		}

		SortParticles(RainContainer, MAX_PARTICLE_RAIN);


		//printf("%d ",ParticlesCount);


		// Update the buffers that OpenGL uses for rendering.
		// There are much more sophisticated means to stream data from the CPU to the GPU, 
		// but this is outside the scope of this tutorial.
		// http://www.opengl.org/wiki/Buffer_Object_Streaming

    glBindBuffer(GL_ARRAY_BUFFER, billboard_vertex_buffer);
	  glBufferData(GL_ARRAY_BUFFER, sizeof(g_rain_vertex_buffer_data), g_rain_vertex_buffer_data, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
		glBufferData(GL_ARRAY_BUFFER, MAX_PARTICLE_RAIN * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW); // Buffer orphaning, a common way to improve streaming perf. See above link for details.
		glBufferSubData(GL_ARRAY_BUFFER, 0, ParticlesCount * sizeof(GLfloat) * 4, g_rain_particule_position_size_data);

		glBindBuffer(GL_ARRAY_BUFFER, particles_color_buffer);
		glBufferData(GL_ARRAY_BUFFER, MAX_PARTICLE_RAIN * 4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW); // Buffer orphaning, a common way to improve streaming perf. See above link for details.
		glBufferSubData(GL_ARRAY_BUFFER, 0, ParticlesCount * sizeof(GLubyte) * 4, g_rain_particule_color_data);
		

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(squareAttrib);
		glBindBuffer(GL_ARRAY_BUFFER, billboard_vertex_buffer);
		glVertexAttribPointer(
			squareAttrib,                  // attribute. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);
		
		// 2nd attribute buffer : positions of particles' centers
		glEnableVertexAttribArray(xyzsAttrib);
		glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
		glVertexAttribPointer(
			xyzsAttrib,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			4,                                // size : x + y + z + size => 4
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		// 3rd attribute buffer : particles' colors
		glEnableVertexAttribArray(colorAttrib);
		glBindBuffer(GL_ARRAY_BUFFER, particles_color_buffer);
		glVertexAttribPointer(
			colorAttrib,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			4,                                // size : r + g + b + a => 4
			GL_UNSIGNED_BYTE,                 // type
			GL_TRUE,                          // normalized?    *** YES, this means that the unsigned char[4] will be accessible with a vec4 (floats) in the shader ***
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		// These functions are specific to glDrawArrays*Instanced*.
		// The first parameter is the attribute buffer we're talking about.
		// The second parameter is the "rate at which generic vertex attributes advance when rendering multiple instances"
		// http://www.opengl.org/sdk/docs/man/xhtml/glVertexAttribDivisor.xml
		glVertexAttribDivisor(squareAttrib, 0); // particles vertices : always reuse the same 4 vertices -> 0
		glVertexAttribDivisor(xyzsAttrib, 1); // positions : one per quad (its center)                 -> 1
		glVertexAttribDivisor(colorAttrib, 1); // color : one per quad                                  -> 1

		// Draw the particules !
		// This draws many times a small triangle_strip (which looks like a quad).
		// This is equivalent to :
		// for(i in ParticlesCount) : glDrawArrays(GL_TRIANGLE_STRIP, 0, 4), 
		// but faster.
		glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 14, ParticlesCount); 


		glVertexAttribDivisor(xyzsAttrib, 0);
		glVertexAttribDivisor(colorAttrib, 0);
		glDisableVertexAttribArray(squareAttrib);
		glDisableVertexAttribArray(xyzsAttrib);
		glDisableVertexAttribArray(colorAttrib);
		
		glDisable(GL_BLEND);
		

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// Cleanup VBO and shader
	glDeleteBuffers(1, &particles_color_buffer);
	glDeleteBuffers(1, &particles_position_buffer);
	glDeleteBuffers(1, &billboard_vertex_buffer);
	glDeleteProgram(particleProgramID);
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteProgram(programID);
	glDeleteTextures(1, &Texture);
	glDeleteVertexArrays(1, &VertexArrayID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}

