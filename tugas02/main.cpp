// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
using namespace glm;

#include <common/shader.hpp>
#include "common/shape.h"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 712
#define WINDOW_TITLE "Running car"
#define VERTEX_SHADER_FILE "tugas02/shader/VertexShader.vsgl"
#define FRAGMENT_SHADER_FILE "tugas02/shader/FragmentShader.fsgl"

void addCar(GLfloat* &vertices, int &num_vertices, GLuint* &elements, int &num_elements) {
  GLfloat carBodyVertices[] = {
      // Car body
      -0.35f,  0.4f,
       0.25f,  0.35f,
       0.5f,   0.2f,
       0.68f,  0.2f,
       0.71f,  0.05f,
       0.71f, -0.05f,
      -0.75f, -0.05f,
      -0.8f,   0.2f,
      -0.4f,   0.2f
  };
  GLuint carBodyElements[] = {
      // Car body
      0, 1, 2,
      0, 2, 8,
      2, 3, 4,
      2, 4, 8,
      4, 5, 6,
      4, 6, 8,
      6, 7, 8
  };
  GLfloat* carBody = createPolygon(carBodyVertices, 9, 1.0f, 1.0f, 0.0f);
  
  GLfloat carDoorVertices[] = {
      // Car door
      -0.25f,  0.35f,
       0.22f,  0.31f,
       0.4f,   0.2f,
       0.41f,  0.0f,
      -0.18f,  0.0f,
      -0.18f,  0.2f
  };
  GLuint carDoorElements[] = {
      // Car body
      0, 1, 5,
      1, 2, 5,
      2, 4, 5,
      2, 3, 4
  };
  GLfloat* carDoor = createPolygon(carDoorVertices, 6, 0.9f,  0.5f, 0.0f);
  
  GLfloat doorWindowVertices[] = {
      // Door window
      -0.21f,  0.32f,
       0.21f,  0.29f,
       0.38f,  0.2f,
      -0.16f,  0.2f
  };
  GLuint doorWindowElements[] = {
      // Car body
      0, 1, 3,
      1, 2, 3
  };
  GLfloat* doorWindow = createPolygon(doorWindowVertices, 4, 0.1f, 0.5f, 1.0f);
  
  addPolygon(vertices, num_vertices, elements, num_elements, carBody, 9, carBodyElements, 7);
  addPolygon(vertices, num_vertices, elements, num_elements, carDoor, 6, carDoorElements, 4);
  addPolygon(vertices, num_vertices, elements, num_elements, doorWindow, 4, doorWindowElements, 2);
  
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

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	
	GLuint VertexArrayID;
  glGenVertexArrays(1, &VertexArrayID);
  glBindVertexArray(VertexArrayID);
  
  
  
  //////// Start coding here ////////
  
  //// Define data ////
  /*static const GLfloat vertices[] = {
      // Car body
      -0.35f,  0.4f,  1.0f, 1.0f, 0.0f,
       0.25f,  0.35f, 1.0f, 1.0f, 0.0f,
       0.5f,   0.2f,  1.0f, 1.0f, 0.0f,
       0.68f,  0.2f,  1.0f, 1.0f, 0.0f,
       0.71f,  0.05f, 1.0f, 1.0f, 0.0f,
       0.71f, -0.05f, 1.0f, 1.0f, 0.0f,
      -0.75f, -0.05f, 1.0f, 1.0f, 0.0f,
      -0.8f,   0.2f,  1.0f, 1.0f, 0.0f,
      -0.4f,   0.2f,  1.0f, 1.0f, 0.0f,
      
      // Car door
      -0.25f,  0.35f, 0.9f, 0.5f, 0.0f,
       0.22f,  0.31f, 0.9f, 0.5f, 0.0f,
       0.4f,   0.2f,  0.9f, 0.5f, 0.0f,
       0.41f,  0.0f,  0.9f, 0.5f, 0.0f,
      -0.18f,  0.0f,  0.9f, 0.5f, 0.0f,
      -0.18f,  0.2f,  0.9f, 0.5f, 0.0f,
      
      // Door window
      -0.21f,  0.32f, 0.1f, 0.5f, 1.0f,
       0.21f,  0.29f, 0.1f, 0.5f, 1.0f,
       0.38f,  0.2f,  0.1f, 0.5f, 1.0f,
      -0.16f,  0.2f,  0.1f, 0.5f, 1.0f
  };

  GLuint elements[] = {
      // Car body
      0, 1, 2,
      0, 2, 8,
      2, 3, 4,
      2, 4, 8,
      4, 5, 6,
      4, 6, 8,
      6, 7, 8,
      
      // Car door
      9, 10, 14,
      10, 11, 14,
      11, 13, 14,
      11, 12, 13,
      
      // Door window
      15, 16, 18,
      16, 17, 18
  };*/
  
  GLfloat* vertices = new GLfloat;
  int vertex_num = 0;
  GLuint* elements = new GLuint;
  int elements_num = 0;
  
  addCar(vertices, vertex_num, elements, elements_num);
  printf("Num vertex: %d\n", vertex_num);
  for (int i = 0; i < vertex_num; i++) {
    printf("%.2f %.2f %.2f %.2f %.2f\n", vertices[5*i], vertices[5*i+1], vertices[5*i+2], vertices[5*i+3], vertices[5*i+4]);
  }
  printf("Num element: %d\n", elements_num);
  for (int i = 0; i < elements_num; i++) {
    printf("%d %d %d\n", elements[3*i], elements[3*i+1], elements[3*i+2]);
  }
  
  GLuint vertexbuffer;
  glGenBuffers(1, &vertexbuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
  glBufferData(GL_ARRAY_BUFFER, vertex_num * sizeof(GLfloat) * 5, vertices, GL_STATIC_DRAW);
  
  GLuint ebo;
  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements_num * sizeof(GLfloat) * 3, elements, GL_STATIC_DRAW);
  
  //// Create and compile our GLSL program from the shaders ////
  GLuint shaderProgram = LoadShaders( VERTEX_SHADER_FILE, FRAGMENT_SHADER_FILE );
  
  GLint posAttrib = glGetAttribLocation(shaderProgram, "pos");
glEnableVertexAttribArray(posAttrib);
glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE,
                       5*sizeof(float), 0);

GLint colAttrib = glGetAttribLocation(shaderProgram, "inColor");
glEnableVertexAttribArray(colAttrib);
glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE,
                       5*sizeof(float), (void*)(2*sizeof(float)));

	do{
		glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shaderProgram);
    glDrawElements(GL_TRIANGLES, 13*3, GL_UNSIGNED_INT, 0);
    
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

