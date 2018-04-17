// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

#include <common/shader.hpp>
#include <common/controls.hpp>
#include <common/texture.hpp>
#include "common/polygon.h"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768
#define WINDOW_TITLE "Textured Car"
#define TEXTURE_BMP "tugas05/uvtemplate.bmp"
#define CIRCLE_SIDES 13
#define VERTEX_SHADER_FILE "tugas05/shader/VertexShader.vsgl"
#define FRAGMENT_SHADER_FILE "tugas05/shader/FragmentShader.fsgl"

void addCar(Polygon &p) {
  float carWidth = 0.5f;
  GLfloat vertices[] = {
      -0.66805f, -0.078826f, carWidth/2,//0
      -0.45326f, -0.0760366f, carWidth/2,//1
      -0.416996f, 0.0215956f, carWidth/2,//2
      -0.252416f, 0.0215956f, carWidth/2,//3
      -0.213363f, -0.0760366f, carWidth/2,//4
      0.205061f, -0.078826f, carWidth/2,//5
      0.244113f, 0.0355431f, carWidth/2,//6
      0.419852f, 0.0383326f, carWidth/2,//7
      0.456115f, -0.0788259f, carWidth/2,//8
      0.729485f, -0.0816154f, carWidth/2,//9
      0.662537f, 0.096912f, carWidth/2,//10
      0.311061f, 0.155491f, carWidth/2,//11
      0.129744f, 0.336808f, carWidth/2,//12
      -0.567629f, 0.334019f, carWidth/2,//13


      -0.66805f, -0.078826f, -carWidth/2,
      -0.45326f, -0.0760366f, -carWidth/2,
      -0.416996f, 0.0215956f, -carWidth/2,
      -0.252416f, 0.0215956f, -carWidth/2,
      -0.213363f, -0.0760366f, -carWidth/2,
      0.205061f, -0.078826f, -carWidth/2,
      0.244113f, 0.0355431f, -carWidth/2,
      0.419852f, 0.0383326f, -carWidth/2,
      0.456115f, -0.0788259f, -carWidth/2,
      0.729485f, -0.0816154f, -carWidth/2,
      0.662537f, 0.096912f, -carWidth/2,
      0.311061f, 0.155491f, -carWidth/2,
      0.129744f, 0.336808f, -carWidth/2,
      -0.567629f, 0.334019f, -carWidth/2
  };
  GLfloat uv[] = {
      -0.66805f, -0.078826f,
      -0.45326f, -0.0760366f,
      -0.416996f, 0.0215956f,
      -0.252416f, 0.0215956f,
      -0.213363f, -0.0760366f,
      0.205061f, -0.078826f,
      0.244113f, 0.0355431f,
      0.419852f, 0.0383326f,
      0.456115f, -0.0788259f,
      0.729485f, -0.0816154f,
      0.662537f, 0.096912f,
      0.311061f, 0.155491f,
      0.129744f, 0.336808f,
      -0.567629f, 0.334019f,


      0.66805f, 0.078826f,
      0.45326f, 0.0760366f,
      0.416996f, -0.0215956f,
      0.252416f, -0.0215956f,
      0.213363f, 0.0760366f,
      -0.205061f, 0.078826f,
      -0.244113f, -0.0355431f,
      -0.419852f, -0.0383326f,
      -0.456115f, 0.0788259f,
      -0.729485f, 0.0816154f,
      -0.662537f, -0.096912f,
      -0.311061f, -0.155491f,
      -0.129744f, -0.336808f,
      0.567629f, -0.334019f
  };
  GLuint elements[] = {
      0, 1, 13,
      1, 2, 13,
      2, 3, 13,
      3, 12, 13,
      3, 4, 12,
      4, 5, 12,
      5, 6, 12,
      6, 11, 12,
      6, 7, 11,
      7, 11, 8,
      8, 9, 11,
      9, 10, 11,


      14, 15, 27,
      16, 15, 27,
      17, 16, 27,
      17, 27, 26,
      18, 17, 26,
      19, 18, 26,
      20, 19, 26,
      20, 26, 25,
      21, 20, 25,
      22, 25, 21,
      23, 22, 25,
      23, 25, 24,


      0, 14, 1,
      14, 15, 1,
      1, 15, 2,
      15, 16, 2,
      2, 16, 3,
      16, 17, 3,
      3, 17, 4,
      17, 18, 4,
      4, 18, 5,
      18, 19, 5,
      5, 19, 6,
      19, 20, 6,
      6, 20, 7,
      20, 21, 7,
      7, 21, 8,
      21, 22, 8,
      8, 22, 9,
      22, 23, 9,
      9, 23, 10,
      23, 24, 10,
      10, 24, 11,
      24, 25, 11,
      11, 25, 12,
      25, 26, 12,
      12, 26, 13,
      26, 27, 13,
      13, 27, 0,
      27, 14, 0
  };

  p.addPolygon(
      vertices,
      uv,
      sizeof(vertices) / sizeof(GLfloat) / 3,
      elements,
      sizeof(elements) / sizeof(GLuint));
  p.addCylinder(
      -0.33f, -0.1f, carWidth/2+0.0001f,
      0.12f, Polygon::POS_Z, -0.1f,
      0.3f, 0.3f, 0.3f,
      CIRCLE_SIDES);
  p.addCylinder(
      -0.33f, -0.1f, -carWidth/2-0.0001f,
      0.12f, Polygon::POS_Z, 0.1f,
      0.3f, 0.3f, 0.3f,
      CIRCLE_SIDES);
  p.addCylinder(
      0.33f, -0.1f, carWidth/2+0.0001f,
      0.12f, Polygon::POS_Z, -0.1f,
      0.3f, 0.3f, 0.3f,
      CIRCLE_SIDES);
  p.addCylinder(
      0.33f, -0.1f, -carWidth/2-0.0001f,
      0.12f, Polygon::POS_Z, 0.1f,
      0.3f, 0.3f, 0.3f,
      CIRCLE_SIDES);
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
	window = glfwCreateWindow( WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window.\n" );
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

	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	GLuint VertexArrayID;
  glGenVertexArrays(1, &VertexArrayID);
  glBindVertexArray(VertexArrayID);

  //////// Start coding here ////////
  int dimension[5] = {Polygon::POS_X, Polygon::POS_Y, Polygon::POS_Z, Polygon::TEXTURE_X, Polygon::TEXTURE_Y};
  Polygon p(5, dimension);
  addCar(p);
  p.generateNormal();
  p.print();

  GLfloat* vertices = p.getArrays();
  unsigned int vertex_num = p.dataArray.size();
  GLuint* elements = p.getElements();
  unsigned int elements_num = p.elementArray.size();
  GLfloat* normals = p.getNormal();
  unsigned int normals_num = p.normalArray.size();

  GLuint vertexbuffer;
  glGenBuffers(1, &vertexbuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
  glBufferData(GL_ARRAY_BUFFER, vertex_num * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

  GLuint ebo;
  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements_num * sizeof(GLfloat), elements, GL_STATIC_DRAW);

  GLuint normalBuffer;
  glGenBuffers(1,&normalBuffer);
  glBindBuffer(GL_ARRAY_BUFFER,normalBuffer);
  glBufferData(GL_ARRAY_BUFFER, normals_num * sizeof(GLfloat),normals, GL_STATIC_DRAW);

  //// Create and compile our GLSL program from the shaders ////
  GLuint shaderProgram = LoadShaders( VERTEX_SHADER_FILE, FRAGMENT_SHADER_FILE );

  GLuint transformLoc = glGetUniformLocation(shaderProgram, "transform");

  // Get a handle for our "MVP" uniform
	GLuint MatrixID = glGetUniformLocation(shaderProgram, "MVP");
  GLuint ViewMatrixID = glGetUniformLocation(shaderProgram,"V");
  GLuint ModelMatrixID = glGetUniformLocation(shaderProgram, "M");

	//Texture
	GLuint Texture = loadBMP_custom(TEXTURE_BMP);
	GLuint TextureID  = glGetUniformLocation(shaderProgram, "myTextureSampler");

  //Light
  glUseProgram(shaderProgram);
  GLuint LightID = glGetUniformLocation(shaderProgram, "LightPosition_worldspace");

	// glfwSetKeyCallback(window, key_callback);
	do{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(shaderProgram);

    // Compute the MVP matrix from keyboard and mouse input
    computeMatricesFromInputs();
		glm::mat4 ProjectionMatrix = getProjectionMatrix();
		glm::mat4 ViewMatrix = getViewMatrix();
		glm::mat4 ModelMatrix = glm::mat4(1.0);
		glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
    glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
    glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);

    glm::vec3 lightPos = glm::vec3(4,4,4);
    glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture);
		glUniform1i(TextureID, 0);

		GLint posAttrib = glGetAttribLocation(shaderProgram, "pos");
	  glEnableVertexAttribArray(posAttrib);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	  glVertexAttribPointer(
	  	posAttrib,          // attribute. No particular reason for 0, but must match the layout in the shader.
	  	3,                  // size
	  	GL_FLOAT, 					// type
	  	GL_FALSE,           // normalized?
	    5*sizeof(float),    // stride
	    0                   // array buffer offset
	  );

	  GLint colAttrib = glGetAttribLocation(shaderProgram, "vertexUV");
	  glEnableVertexAttribArray(colAttrib);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	  glVertexAttribPointer(
	  	colAttrib,          			// attribute. No particular reason for 0, but must match the layout in the shader.
	  	2,                  			// size
	  	GL_FLOAT, 								// type
	  	GL_FALSE,           			// normalized?
	    5*sizeof(float),    			// stride
	    (void*)(3*sizeof(float))  // array buffer offset
	  );

    GLint normalAttrib = glGetAttribLocation(shaderProgram, "vertexNormal_modelspace");
    glEnableVertexAttribArray(normalAttrib);
    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glVertexAttribPointer(
			normalAttrib,                                // attribute
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
    );

		//This is for cube
		for (int i = 0; i < 5; i++) {
		  glDrawElements(GL_TRIANGLES, p.sizeArray[i], GL_UNSIGNED_INT, (void*)(p.offsetArray[i]*sizeof(GLuint)));
		}

		glDisableVertexAttribArray(posAttrib);
		glDisableVertexAttribArray(colAttrib);

		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

  // Cleanup VBO
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteVertexArrays(1, &VertexArrayID);
	glDeleteProgram(shaderProgram);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}
