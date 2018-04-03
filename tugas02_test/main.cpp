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
#include "common/polygon.h"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768
#define WINDOW_TITLE "Colored cube"
#define CIRCLE_SIDES 13
#define VERTEX_SHADER_FILE "tugas02_test/shader/VertexShader.vsgl"
#define FRAGMENT_SHADER_FILE "tugas02_test/shader/FragmentShader.fsgl"

/*
void addCar(Polygon &p) {
  GLfloat carBodyVertices[] = {
      // Car body
       -0.66805f, -0.078826f, 0.0f,
       -0.45326f, -0.0760366f, 0.0f,
       -0.416996f, 0.0215956f, 0.0f,
       -0.252416f, 0.0215956f, 0.0f,
       -0.213363f, -0.0760366f, 0.0f,
       0.205061f, -0.078826f, 0.0f,
       0.244113f, 0.0355431f, 0.0f,
       0.419852f, 0.0383326f, 0.0f,
       0.456115f, -0.0788259f, 0.0f,
       0.729485f, -0.0816154f, 0.0f,
       0.662537f, 0.096912f, 0.0f,
       0.311061f, 0.155491f, 0.0f,
       0.129744f, 0.336808f, 0.0f,
       -0.567629f, 0.334019f, 0.0f
  };
  GLuint carBodyElements[] = {
      // Car body
      0, 1, 13,
      1, 2, 13,
      2, 3, 13,
      3, 13, 12,
      3, 4, 12,
      4, 5, 12,
      5, 6, 12,
      6, 12, 11,
      6, 7, 11,
      7, 8, 11,
      8, 9, 11,
      9, 10, 11
  };
  
  GLfloat carDoorVertices[] = {
      // Car door
       -0.051036f, 0.30187f, 0.0f,
       0.113544f, 0.304659f, 0.0f,
       0.205597f, 0.184711f, 0.0f,
       0.200018f, 0.0563942f, 0.0f,
       0.172123f, -0.0356591f, 0.0f,
       -0.051036f, -0.0356591f, 0.0f,
       -0.0818158f, 0.302335f, 0.0f,
       -0.0818158f, -0.0359436f, 0.0f,
       -0.200164f, -0.0349574f, 0.0f,
       -0.241586f, 0.05479f, 0.0f,
       -0.297801f, 0.0567625f, 0.0f,
       -0.296815f, 0.215546f, 0.0f,
       -0.262297f, 0.303321f, 0.0f
  };
  GLuint carDoorElements[] = {
      // Car body
      0, 1, 2,
      0, 2, 3,
      0, 3, 4,
      0, 4, 5,
      6, 7, 8,
      6, 8, 9,
      6, 9, 10,
      6, 10, 11,
      6, 11, 12
  };
  
  GLfloat doorWindowVertices[] = {
      // Door window
       -0.0344765f, 0.283597f, 0.0f,
       0.103596f, 0.285569f, 0.0f,
       0.172633f, 0.188918f, 0.0f,
       -0.0344764f, 0.19089f, 0.0f,
       
       -0.247503f, 0.284583f, 0.0f,
       -0.0975955f, 0.284583f, 0.0f,
       -0.0966093f, 0.192863f, 0.0f,
       -0.28f, 0.192863f, 0.0f,
       
       -0.293856f, 0.305294f, 0.0f,
       -0.344154f, 0.191877f, 0.0f,
       -0.56f, 0.191877f, 0.0f,
       -0.54f, 0.305f, 0.0f

  };
  GLuint doorWindowElements[] = {
      // Car body
      1, 2, 3,
      0, 1, 3,
      4, 5, 6,
      4, 6, 7,
      8, 9, 11,
      9, 10,11
  };
  
  printf("B1\n");
  p.addPolygon(
      carBodyVertices, 
      14, 
      carBodyElements, 
      36,
      1.0f, 1.0f, 0.0f);
  printf("B2\n");
  p.addPolygon(
      carDoorVertices,  
      13, 
      carDoorElements, 
      27,
      0.9f,  0.5f, 0.0f);
  printf("B3\n");
  p.addPolygon(
      doorWindowVertices, 
      12, 
      doorWindowElements, 
      18,
      0.1f, 0.5f, 1.0f);
  printf("B4\n");
  p.addCircle(
      -0.33f, -0.1f, 0.12f,
      0.3f, 0.3f, 0.3f,
      CIRCLE_SIDES);
  printf("B5\n");
  p.addCircle(
      0.33f, -0.1f, 0.12f,
      0.3f, 0.3f, 0.3f,
      CIRCLE_SIDES);
  printf("B6\n");
  
}
*/

void addCube(Polygon &p) {
  GLfloat vertices[] = {
    -1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,  //1*/
		 1.0f, 1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,  //2
		 1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		 1.0f,-1.0f,-1.0f,  //3
		 1.0f, 1.0f,-1.0f,
		 1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,  //4
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,  //5
		 1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,  //6
		-1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		 1.0f,-1.0f, 1.0f,  //7
		 1.0f, 1.0f, 1.0f,
		 1.0f,-1.0f,-1.0f,
		 1.0f, 1.0f,-1.0f,  //8
		 1.0f,-1.0f,-1.0f,
		 1.0f, 1.0f, 1.0f,
		 1.0f,-1.0f, 1.0f,  //9
		 1.0f, 1.0f, 1.0f,
		 1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,  //10
		 1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,  //11
		 1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		 1.0f,-1.0f, 1.0f   //12
  };
  GLuint elements[] = {
    0,  1,  2, 
    3,  4,  5, 
    6,  7,  8, 
    9,  10, 11,
    12, 13, 14,
    15, 16, 17,
    18, 19, 20,
    21, 22, 23,
    24, 25, 26,
    27, 28, 29,
    30, 31, 32,
    33, 34, 35
  };
  GLfloat colors[] = {
    0.583f,  0.771f,  0.014f,
		0.609f,  0.115f,  0.436f,
		0.327f,  0.483f,  0.844f,  //1*/
		0.822f,  0.569f,  0.201f,
		0.435f,  0.602f,  0.223f,
		0.310f,  0.747f,  0.185f,  //2
		0.597f,  0.770f,  0.761f,
		0.559f,  0.436f,  0.730f,
		0.359f,  0.583f,  0.152f,  //3
		0.483f,  0.596f,  0.789f,
		0.559f,  0.861f,  0.639f,
		0.195f,  0.548f,  0.859f,  //4
		0.014f,  0.184f,  0.576f,
		0.771f,  0.328f,  0.970f,
		0.406f,  0.615f,  0.116f,  //5
		0.676f,  0.977f,  0.133f,
		0.971f,  0.572f,  0.833f,
		0.140f,  0.616f,  0.489f,  //6
		0.997f,  0.513f,  0.064f,
		0.945f,  0.719f,  0.592f,
		0.543f,  0.021f,  0.978f,  //7
		0.279f,  0.317f,  0.505f,
		0.167f,  0.620f,  0.077f,
		0.347f,  0.857f,  0.137f,  //8
		0.055f,  0.953f,  0.042f,
		0.714f,  0.505f,  0.345f,
		0.783f,  0.290f,  0.734f,  //9
		0.722f,  0.645f,  0.174f,
		0.302f,  0.455f,  0.848f,
		0.225f,  0.587f,  0.040f,  //10
		0.517f,  0.713f,  0.338f,
		0.053f,  0.959f,  0.120f,
		0.393f,  0.621f,  0.362f,  //11
		0.673f,  0.211f,  0.457f,
		0.820f,  0.883f,  0.371f,
		0.982f,  0.099f,  0.879f   //12*/
  };

  p.addPolygon(
      vertices, 
      sizeof(vertices) / sizeof(GLfloat) / 3, 
      elements, 
      sizeof(elements) / sizeof(GLuint),
      colors);
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
  int dimension[6] = {Polygon::POS_X, Polygon::POS_Y, Polygon::POS_Z, Polygon::COLOR_R, Polygon::COLOR_G, Polygon::COLOR_B};
  Polygon p(6, dimension);
  addCube(p);
  p.print();
  
  GLfloat* vertices = p.getArrays();
  unsigned int vertex_num = p.dataArray.size();
  GLuint* elements = p.getElements();
  unsigned int elements_num = p.elementArray.size();
  
  GLuint vertexbuffer;
  glGenBuffers(1, &vertexbuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
  glBufferData(GL_ARRAY_BUFFER, vertex_num * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
  
  GLuint ebo;
  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements_num * sizeof(GLfloat), elements, GL_STATIC_DRAW);
  
  //// Create and compile our GLSL program from the shaders ////
  GLuint shaderProgram = LoadShaders( VERTEX_SHADER_FILE, FRAGMENT_SHADER_FILE );
  
  // Get a handle for our "MVP" uniform
	GLuint MatrixID = glGetUniformLocation(shaderProgram, "MVP");

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

		GLint posAttrib = glGetAttribLocation(shaderProgram, "pos");
	  glEnableVertexAttribArray(posAttrib);
	  glVertexAttribPointer(
	  	posAttrib,          // attribute. No particular reason for 0, but must match the layout in the shader.
	  	3,                  // size
	  	GL_FLOAT, 					// type
	  	GL_FALSE,           // normalized?
	    6*sizeof(float),    // stride
	    0                   // array buffer offset
	  );

	  GLint colAttrib = glGetAttribLocation(shaderProgram, "inColor");
	  glEnableVertexAttribArray(colAttrib);
	  glVertexAttribPointer(
	  	colAttrib,          			// attribute. No particular reason for 0, but must match the layout in the shader.
	  	3,                  			// size
	  	GL_FLOAT, 								// type
	  	GL_FALSE,           			// normalized?
	    6*sizeof(float),    			// stride
	    (void*)(3*sizeof(float))  // array buffer offset
	  );

		//This is for cube
		glDrawElements(GL_TRIANGLES, p.sizeArray[0], GL_UNSIGNED_INT, (void*)(p.offsetArray[0]*sizeof(GLuint)));
    
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

