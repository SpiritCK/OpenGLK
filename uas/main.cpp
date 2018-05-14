// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>

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
#define SMOKE_PARTICLE_VERTEX_SHADER_FILE "uas/shader/SmokeParticle.vertexshader"
#define SMOKE_PARTICLE_FRAGMENT_SHADER_FILE "uas/shader/SmokeParticle.fragmentshader"
#define RAIN_PARTICLE_VERTEX_SHADER_FILE "uas/shader/RainParticle.vertexshader"
#define RAIN_PARTICLE_FRAGMENT_SHADER_FILE "uas/shader/RainParticle.fragmentshader"
#define MODEL_FILE "uas/test.obj"
#define TEXTURE_FILE "uas/1lexus.dds"
#define MAX_PARTICLE 50000

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

const int MaxParticles = MAX_PARTICLE;
Particle SmokeParticlesContainer[MaxParticles];
Particle RainParticlesContainer[MaxParticles];
int LastUsedSmokeParticle = 0;
int LastUsedRainParticle = 0;
const float GROUND_LEVEL = -0.4f;

// Finds a Particle in SmokeParticlesContainer which isn't used yet.
// (i.e. life < 0);
int FindUnusedSmokeParticle(){

	for(int i=LastUsedSmokeParticle; i<MaxParticles; i++){
		if (SmokeParticlesContainer[i].life < 0){
			LastUsedSmokeParticle = i;
			return i;
		}
	}

	for(int i=0; i<LastUsedSmokeParticle; i++){
		if (SmokeParticlesContainer[i].life < 0){
			LastUsedSmokeParticle = i;
			return i;
		}
	}
	return 0; // All particles are taken, override the first one
}

int FindUnusedRainParticle(){
	for(int i=LastUsedRainParticle; i<MaxParticles; i++){
		if (RainParticlesContainer[i].life < -10.0f){
			LastUsedRainParticle = i;
			return i;
		}
	}

	for(int i=0; i<LastUsedRainParticle; i++){
		if (RainParticlesContainer[i].life < -10.0f){
			LastUsedRainParticle = i;
			return i;
		}
	}

	return 0; // All particles are taken, override the first one
}

void SortSmokeParticles(){
	std::sort(&SmokeParticlesContainer[0], &SmokeParticlesContainer[MaxParticles]);
}

void SortRainParticles(){
	std::sort(&RainParticlesContainer[0], &RainParticlesContainer[MaxParticles]);
}

bool collideCar(vec3 pos){
	if(pos.x >= -1.13 && pos.x < -0.7 && abs(pos.z) <= 0.43){
		return pos.y <= (0.279*pos.x)+0.41527;
	}
	else if(pos.x >= -0.7 && pos.x < -0.23 && abs(pos.z) <= ((-0,17*pos.x)+0,311)){
		return pos.y <= (0.447*pos.x)+0.533;
	}
	else if(pos.x >= -0.23 && pos.x < 0.43 && abs(pos.z) <= 0.35){
		return pos.y <= (0.03*pos.x)+0.4369;
	}
	else if(pos.x >= 0.43 && pos.x < 1.0 && abs(pos.z) <= ((0.158*pos.x)+0.282)){
		return pos.y <= (-0.33*pos.x)+0.592;
	}
	else if(pos.x >= 1.0 && pos.x < 1.2 && abs(pos.z) <= 0.44){
		return pos.z <= (-0.1*pos.x)+0.36;
	}
	else return false;
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
	glfwWindowHint(GLFW_RESIZABLE,GL_FALSE);
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


	// Create and compile smoke particle shader program
	GLuint smokeParticleProgramID = LoadShaders( SMOKE_PARTICLE_VERTEX_SHADER_FILE, SMOKE_PARTICLE_FRAGMENT_SHADER_FILE );

	// Vertex shader
	GLuint smoke_CameraRight_worldspace_ID  = glGetUniformLocation(smokeParticleProgramID, "CameraRight_worldspace");
	GLuint smoke_CameraUp_worldspace_ID  = glGetUniformLocation(smokeParticleProgramID, "CameraUp_worldspace");
	GLuint smoke_ViewProjMatrixID = glGetUniformLocation(smokeParticleProgramID, "VP");

  GLint smoke_squareAttrib = glGetAttribLocation(smokeParticleProgramID, "squareVertices");
	GLint smoke_xyzsAttrib = glGetAttribLocation(smokeParticleProgramID, "xyzs");
  GLint smoke_colorAttrib = glGetAttribLocation(smokeParticleProgramID, "color");

	static GLfloat* smoke_g_particule_position_size_data = new GLfloat[MaxParticles * 4];
	static GLubyte* smoke_g_particule_color_data         = new GLubyte[MaxParticles * 4];

	for(int i=0; i<MaxParticles; i++){
		SmokeParticlesContainer[i].life = -1.0f;
		SmokeParticlesContainer[i].cameradistance = -1.0f;
	}

	// The VBO containing the 4 vertices of the particles.
	// Thanks to instancing, they will be shared by all particles.
	static const GLfloat smoke_g_vertex_buffer_data[] = {
		 -0.005f, -0.005f, 0.0f,
		  0.005f, -0.005f, 0.0f,
		 -0.005f,  0.005f, 0.0f,
		  0.005f,  0.005f, 0.0f,
	};
	GLuint smoke_billboard_vertex_buffer;
	glGenBuffers(1, &smoke_billboard_vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, smoke_billboard_vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(smoke_g_vertex_buffer_data), smoke_g_vertex_buffer_data, GL_STATIC_DRAW);

	// The VBO containing the positions and sizes of the particles
	GLuint smoke_particles_position_buffer;
	glGenBuffers(1, &smoke_particles_position_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, smoke_particles_position_buffer);
	// Initialize with empty (NULL) buffer : it will be updated later, each frame.
	glBufferData(GL_ARRAY_BUFFER, MaxParticles * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);

	// The VBO containing the colors of the particles
	GLuint smoke_particles_color_buffer;
	glGenBuffers(1, &smoke_particles_color_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, smoke_particles_color_buffer);
	// Initialize with empty (NULL) buffer : it will be updated later, each frame.
	glBufferData(GL_ARRAY_BUFFER, MaxParticles * 4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW);

	//<<<<<<<<<<<<<<<<<<
	// Create and compile our rain particle shader program
	GLuint rain_programID = LoadShaders( RAIN_PARTICLE_VERTEX_SHADER_FILE, RAIN_PARTICLE_FRAGMENT_SHADER_FILE );

	// Vertex shader
	GLuint rain_CameraRight_worldspace_ID  = glGetUniformLocation(rain_programID, "CameraRight_worldspace");
	GLuint rain_CameraUp_worldspace_ID  = glGetUniformLocation(rain_programID, "CameraUp_worldspace");
	GLuint rain_ViewProjMatrixID = glGetUniformLocation(rain_programID, "VP");

  GLint rain_squareAttrib = glGetAttribLocation(rain_programID, "squareVertices");
	GLint rain_xyzsAttrib = glGetAttribLocation(rain_programID, "xyzs");
  GLint rain_colorAttrib = glGetAttribLocation(rain_programID, "color");
	// fragment shader
	GLuint rain_TextureID  = glGetUniformLocation(rain_programID, "myTextureSampler");


	static GLfloat* rain_g_particule_position_size_data = new GLfloat[MaxParticles * 4];
	static GLubyte* rain_g_particule_color_data         = new GLubyte[MaxParticles * 4];

	for(int i=0; i<MaxParticles; i++){
		RainParticlesContainer[i].life = -11.0f;
		RainParticlesContainer[i].cameradistance = -1.0f;
	}



	GLuint rain_Texture = loadDDS("tutorial18/particle.DDS");

	// The VBO containing the 4 vertices of the particles.
	// Thanks to instancing, they will be shared by all particles.
	static const GLfloat rain_g_vertex_buffer_data[] = {
		 -0.008f, -0.016f, 0.0f,
			0.008f, -0.016f, 0.0f,
		 -0.008f,  0.016f, 0.0f,
			0.008f,  0.016f, 0.0f,
	};
	GLuint rain_billboard_vertex_buffer;
	glGenBuffers(1, &rain_billboard_vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, rain_billboard_vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rain_g_vertex_buffer_data), rain_g_vertex_buffer_data, GL_STATIC_DRAW);

	// The VBO containing the positions and sizes of the particles
	GLuint rain_particles_position_buffer;
	glGenBuffers(1, &rain_particles_position_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, rain_particles_position_buffer);
	// Initialize with empty (NULL) buffer : it will be updated later, each frame.
	glBufferData(GL_ARRAY_BUFFER, MaxParticles * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);

	// The VBO containing the colors of the particles
	GLuint rain_particles_color_buffer;
	glGenBuffers(1, &rain_particles_color_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, rain_particles_color_buffer);
	// Initialize with empty (NULL) buffer : it will be updated later, each frame.
	glBufferData(GL_ARRAY_BUFFER, MaxParticles * 4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW);
	//>>>>>>>>>>>>>>>>>>


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




		// Generate 10 new particule each millisecond,
		// but limit this to 16 ms (60 fps), or if you have 1 long frame (1sec),
		// newsmokeparticles will be huge and the next frame even longer.
		int newsmokeparticles = (int)(delta*1000.0);
		if (newsmokeparticles > (int)(0.016f*1000.0))
			newsmokeparticles = (int)(0.016f*1000.0);

		for(int i=0; i<newsmokeparticles; i++){
			int particleIndex = FindUnusedSmokeParticle();
			SmokeParticlesContainer[particleIndex].life = 5.0f; // This particle will live 5 seconds.
			SmokeParticlesContainer[particleIndex].pos = glm::vec3(1.25f,-0.17f,-0.2f);

			float spread = 1.5f;
			glm::vec3 maindir = glm::vec3(8.0f, 0.0f, 0.0f);
			glm::vec3 randomdir = glm::vec3(
				(rand()%2000 - 1000.0f)/1000.0f,
				(rand()%2000 - 1000.0f)/1000.0f,
				(rand()%2000 - 1000.0f)/1000.0f
			);

			SmokeParticlesContainer[particleIndex].speed = (maindir + randomdir*spread) * 0.015f;

			SmokeParticlesContainer[particleIndex].r = 80;
			SmokeParticlesContainer[particleIndex].g = 80;
			SmokeParticlesContainer[particleIndex].b = 80;
			SmokeParticlesContainer[particleIndex].a = 40;

			SmokeParticlesContainer[particleIndex].size = (rand()%1000)/500.0f + 0.1f;

		}

		// Simulate all particles
		int SmokeParticlesCount = 0;
		for(int i=0; i<MaxParticles; i++){

			Particle& p = SmokeParticlesContainer[i]; // shortcut

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
					//SmokeParticlesContainer[i].pos += glm::vec3(0.0f,10.0f, 0.0f) * (float)delta;

					// Fill the GPU buffer
					smoke_g_particule_position_size_data[4*SmokeParticlesCount+0] = p.pos.x;
					smoke_g_particule_position_size_data[4*SmokeParticlesCount+1] = p.pos.y;
					smoke_g_particule_position_size_data[4*SmokeParticlesCount+2] = p.pos.z;

					smoke_g_particule_position_size_data[4*SmokeParticlesCount+3] = p.size;

					smoke_g_particule_color_data[4*SmokeParticlesCount+0] = p.r;
					smoke_g_particule_color_data[4*SmokeParticlesCount+1] = p.g;
					smoke_g_particule_color_data[4*SmokeParticlesCount+2] = p.b;
					smoke_g_particule_color_data[4*SmokeParticlesCount+3] = p.a;

				}else{
					// Particles that just died will be put at the end of the buffer in SortParticles();
					p.cameradistance = -1.0f;
				}

				SmokeParticlesCount++;

			}
		}

		SortSmokeParticles();


		//printf("%d ",SmokeParticlesCount);


		// Update the buffers that OpenGL uses for rendering.
		// There are much more sophisticated means to stream data from the CPU to the GPU,
		// but this is outside the scope of this tutorial.
		// http://www.opengl.org/wiki/Buffer_Object_Streaming


		glBindBuffer(GL_ARRAY_BUFFER, smoke_particles_position_buffer);
		glBufferData(GL_ARRAY_BUFFER, MaxParticles * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW); // Buffer orphaning, a common way to improve streaming perf. See above link for details.
		glBufferSubData(GL_ARRAY_BUFFER, 0, SmokeParticlesCount * sizeof(GLfloat) * 4, smoke_g_particule_position_size_data);

		glBindBuffer(GL_ARRAY_BUFFER, smoke_particles_color_buffer);
		glBufferData(GL_ARRAY_BUFFER, MaxParticles * 4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW); // Buffer orphaning, a common way to improve streaming perf. See above link for details.
		glBufferSubData(GL_ARRAY_BUFFER, 0, SmokeParticlesCount * sizeof(GLubyte) * 4, smoke_g_particule_color_data);


		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Use our shader
		glUseProgram(smokeParticleProgramID);

		// Same as the billboards tutorial
		glUniform3f(smoke_CameraRight_worldspace_ID, ViewMatrix[0][0], ViewMatrix[1][0], ViewMatrix[2][0]);
		glUniform3f(smoke_CameraUp_worldspace_ID   , ViewMatrix[0][1], ViewMatrix[1][1], ViewMatrix[2][1]);

		glUniformMatrix4fv(smoke_ViewProjMatrixID, 1, GL_FALSE, &ViewProjectionMatrix[0][0]);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(smoke_squareAttrib);
		glBindBuffer(GL_ARRAY_BUFFER, smoke_billboard_vertex_buffer);
		glVertexAttribPointer(
			smoke_squareAttrib,                  // attribute. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// 2nd attribute buffer : positions of particles' centers
		glEnableVertexAttribArray(smoke_xyzsAttrib);
		glBindBuffer(GL_ARRAY_BUFFER, smoke_particles_position_buffer);
		glVertexAttribPointer(
			smoke_xyzsAttrib,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			4,                                // size : x + y + z + size => 4
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		// 3rd attribute buffer : particles' colors
		glEnableVertexAttribArray(smoke_colorAttrib);
		glBindBuffer(GL_ARRAY_BUFFER, smoke_particles_color_buffer);
		glVertexAttribPointer(
			smoke_colorAttrib,                                // attribute. No particular reason for 1, but must match the layout in the shader.
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
		glVertexAttribDivisor(smoke_squareAttrib, 0); // particles vertices : always reuse the same 4 vertices -> 0
		glVertexAttribDivisor(smoke_xyzsAttrib, 1); // positions : one per quad (its center)                 -> 1
		glVertexAttribDivisor(smoke_colorAttrib, 1); // color : one per quad                                  -> 1

		// Draw the particules !
		// This draws many times a small triangle_strip (which looks like a quad).
		// This is equivalent to :
		// for(i in SmokeParticlesCount) : glDrawArrays(GL_TRIANGLE_STRIP, 0, 4),
		// but faster.
		glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, SmokeParticlesCount);


		glVertexAttribDivisor(smoke_xyzsAttrib, 0);
		glVertexAttribDivisor(smoke_colorAttrib, 0);
		glDisableVertexAttribArray(smoke_squareAttrib);
		glDisableVertexAttribArray(smoke_xyzsAttrib);
		glDisableVertexAttribArray(smoke_colorAttrib);

		glDisable(GL_BLEND);

		//<<<<<<<<
		// Generate 100 new particule each millisecond,
		// but limit this to 16 ms (60 fps), or if you have 1 long frame (1sec),
		// newrainparticles will be huge and the next frame even longer.
		int newrainparticles = (int)(delta*1000.0);
		if (newrainparticles > (int)(0.016f*10000.0))
			newrainparticles = (int)(0.016f*10000.0);

		for(int i=0; i<newrainparticles; i++){
			int particleIndex = FindUnusedRainParticle();
			RainParticlesContainer[particleIndex].life = 10.0f; // This particle will live 5 seconds.
			float randomX = (float)(rand()%2000 - 1000.0f)/500.0f;
			float randomZ = (float)(rand()%2000 - 1000.0f)/500.0f;
			RainParticlesContainer[particleIndex].pos = glm::vec3(randomX, 3, randomZ);

			vec3 temp = glm::vec3(
										0.0f,
										(rand()%2000 - 1000.0f)/1000.0f,
										0.0f
									);
			RainParticlesContainer[particleIndex].speed = temp * 1.5f * 0.015f;

			// water color
			RainParticlesContainer[particleIndex].r = 254;
			RainParticlesContainer[particleIndex].g = 254;
			RainParticlesContainer[particleIndex].b = 254;
			RainParticlesContainer[particleIndex].a = 64;

			RainParticlesContainer[particleIndex].size = (rand()%1000)/2000.0f + 0.1f;

		}



		// Simulate all particles
		int RainParticlesCount = 0;
		for(int i=0; i<MaxParticles; i++){

			Particle& p = RainParticlesContainer[i]; // shortcut

			if(p.life > 0.0f){
				//check collision, put particle to death if collide
				if (p.pos.y <= GROUND_LEVEL || collideCar(p.pos)) {
					p.life = 0.0f;
				}
				// Decrease life
				p.life -= delta;
				if (p.life > 0.0f){
					// Simulate simple physics : gravity only, no collisions
					//p.speed += glm::vec3(0.0f,-9.81f, 0.0f) * (float)delta * 0.5f;
					p.speed += glm::vec3(0.0f, 0.005f, 0.0f) * (float)delta;
					//p.pos -= p.speed * (float)delta;
					p.pos -= p.speed;
					p.cameradistance = glm::length2( p.pos - CameraPosition );
					//RainParticlesContainer[i].pos += glm::vec3(0.0f,10.0f, 0.0f) * (float)delta;

					// Fill the GPU buffer
					rain_g_particule_position_size_data[4*RainParticlesCount+0] = p.pos.x;
					rain_g_particule_position_size_data[4*RainParticlesCount+1] = p.pos.y;
					rain_g_particule_position_size_data[4*RainParticlesCount+2] = p.pos.z;

					rain_g_particule_position_size_data[4*RainParticlesCount+3] = p.size;

					rain_g_particule_color_data[4*RainParticlesCount+0] = p.r;
					rain_g_particule_color_data[4*RainParticlesCount+1] = p.g;
					rain_g_particule_color_data[4*RainParticlesCount+2] = p.b;
					rain_g_particule_color_data[4*RainParticlesCount+3] = p.a;

				}
				else //after collision effect
				if (p.life > -10.0f) {
					float temp1 = ((float)(rand() % 100) - 50) / 10000;
					float temp2 = ((float)(rand() % 100) - 50) / 10000;
					//printf("%.4f\n",temp1);
					vec3 gg = glm::vec3(temp1, 0.005f - (p.life / 100), temp2);
					p.pos += gg;
					p.cameradistance = glm::length2( p.pos - CameraPosition );

					// Fill the GPU buffer
					rain_g_particule_position_size_data[4*RainParticlesCount+0] = p.pos.x;
					rain_g_particule_position_size_data[4*RainParticlesCount+1] = p.pos.y;
					rain_g_particule_position_size_data[4*RainParticlesCount+2] = p.pos.z;

					rain_g_particule_position_size_data[4*RainParticlesCount+3] = p.size;

					rain_g_particule_color_data[4*RainParticlesCount+0] = p.r;
					rain_g_particule_color_data[4*RainParticlesCount+1] = p.g;
					rain_g_particule_color_data[4*RainParticlesCount+2] = p.b;
					rain_g_particule_color_data[4*RainParticlesCount+3] = p.a;
				}
				else {
					// Particles that just died will be put at the end of the buffer in SortParticles();
					p.cameradistance = -1.0f;
				}

				RainParticlesCount++;

			}
		}

		SortRainParticles();


		//printf("%d ",RainParticlesCount);


		// Update the buffers that OpenGL uses for rendering.
		// There are much more sophisticated means to stream data from the CPU to the GPU,
		// but this is outside the scope of this tutorial.
		// http://www.opengl.org/wiki/Buffer_Object_Streaming


		glBindBuffer(GL_ARRAY_BUFFER, rain_particles_position_buffer);
		glBufferData(GL_ARRAY_BUFFER, MaxParticles * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW); // Buffer orphaning, a common way to improve streaming perf. See above link for details.
		glBufferSubData(GL_ARRAY_BUFFER, 0, RainParticlesCount * sizeof(GLfloat) * 4, rain_g_particule_position_size_data);

		glBindBuffer(GL_ARRAY_BUFFER, rain_particles_color_buffer);
		glBufferData(GL_ARRAY_BUFFER, MaxParticles * 4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW); // Buffer orphaning, a common way to improve streaming perf. See above link for details.
		glBufferSubData(GL_ARRAY_BUFFER, 0, RainParticlesCount * sizeof(GLubyte) * 4, rain_g_particule_color_data);


		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Use our shader
		glUseProgram(rain_programID);

		// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, rain_Texture);
		// Set our "myTextureSampler" sampler to use Texture Unit 0
		glUniform1i(rain_TextureID, 1);

		// Same as the billboards tutorial
		glUniform3f(rain_CameraRight_worldspace_ID, ViewMatrix[0][0], ViewMatrix[1][0], ViewMatrix[2][0]);
		glUniform3f(rain_CameraUp_worldspace_ID   , ViewMatrix[0][1], ViewMatrix[1][1], ViewMatrix[2][1]);

		glUniformMatrix4fv(rain_ViewProjMatrixID, 1, GL_FALSE, &ViewProjectionMatrix[0][0]);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(rain_squareAttrib);
		glBindBuffer(GL_ARRAY_BUFFER, rain_billboard_vertex_buffer);
		glVertexAttribPointer(
			rain_squareAttrib,                  // attribute. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// 2nd attribute buffer : positions of particles' centers
		glEnableVertexAttribArray(rain_xyzsAttrib);
		glBindBuffer(GL_ARRAY_BUFFER, rain_particles_position_buffer);
		glVertexAttribPointer(
			rain_xyzsAttrib,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			4,                                // size : x + y + z + size => 4
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		// 3rd attribute buffer : particles' colors
		glEnableVertexAttribArray(rain_colorAttrib);
		glBindBuffer(GL_ARRAY_BUFFER, rain_particles_color_buffer);
		glVertexAttribPointer(
			rain_colorAttrib,                                // attribute. No particular reason for 1, but must match the layout in the shader.
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
		glVertexAttribDivisor(rain_squareAttrib, 0); // particles vertices : always reuse the same 4 vertices -> 0
		glVertexAttribDivisor(rain_xyzsAttrib, 1); // positions : one per quad (its center)                 -> 1
		glVertexAttribDivisor(rain_colorAttrib, 1); // color : one per quad                                  -> 1

		// Draw the particules !
		// This draws many times a small triangle_strip (which looks like a quad).
		// This is equivalent to :
		// for(i in RainParticlesCount) : glDrawArrays(GL_TRIANGLE_STRIP, 0, 4),
		// but faster.
		glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, RainParticlesCount);

		glVertexAttribDivisor(rain_xyzsAttrib, 0);
		glVertexAttribDivisor(rain_colorAttrib, 0);
		glDisableVertexAttribArray(rain_squareAttrib);
		glDisableVertexAttribArray(rain_xyzsAttrib);
		glDisableVertexAttribArray(rain_colorAttrib);

		glDisable(GL_BLEND);
		//>>>>>>>>

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// Cleanup VBO and shader
	glDeleteBuffers(1, &rain_particles_color_buffer);
	glDeleteBuffers(1, &rain_particles_position_buffer);
	glDeleteBuffers(1, &rain_billboard_vertex_buffer);
	glDeleteProgram(rain_programID);
	glDeleteTextures(1, &rain_Texture);
	glDeleteBuffers(1, &smoke_particles_color_buffer);
	glDeleteBuffers(1, &smoke_particles_position_buffer);
	glDeleteBuffers(1, &smoke_billboard_vertex_buffer);
	glDeleteProgram(smokeParticleProgramID);
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteProgram(programID);
	glDeleteTextures(1, &Texture);
	glDeleteVertexArrays(1, &VertexArrayID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}
