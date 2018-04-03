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
#include "common/polygon.h"

#define WINDOW_WIDTH 712
#define WINDOW_HEIGHT 712
#define WINDOW_TITLE "Running car"
#define CIRCLE_SIDES 13
#define VERTEX_SHADER_FILE "tugas02_test/shader/VertexShader.vsgl"
#define FRAGMENT_SHADER_FILE "tugas02_test/shader/FragmentShader.fsgl"

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
  int dimension[5] = {Polygon::POS_X, Polygon::POS_Y, Polygon::COLOR_R, Polygon::COLOR_G, Polygon::COLOR_B};
  printf("A\n");
  Polygon p(5, dimension);
  printf("B\n");
  addCar(p);
  printf("C\n");
  p.print();
  
  
  GLfloat* vertices = p.getArrays();
  unsigned int vertex_num = p.dataArray.size();
  GLuint* elements = p.getElements();
  unsigned int elements_num = p.elementArray.size();
  
  printf("Vertex num: %d\n", vertex_num);
  for (int i = 0; i < vertex_num; i++) {
    printf("%d. %.2f %.2f %.2f %.2f %.2f\n", i, vertices[5*i], vertices[5*i+1], vertices[5*i+2], vertices[5*i+3], vertices[5*i+4]);
  }
  printf("Elements num: %d\n", elements_num);
  for (int i = 0; i < elements_num; i++) {
    printf("%d. %d\n", i, elements[i]);
  }
  printf("Segments num: %ld\n", p.offsetArray.size());
  for (int i = 0; i < p.offsetArray.size(); i++) {
    printf("%d. %d %d\n", i, p.offsetArray[i], p.sizeArray[i]);
  }
  
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
    //glDrawElements(GL_TRIANGLES, 39, GL_UNSIGNED_INT, 0);
    //glDrawElements(GL_TRIANGLE_FAN, CIRCLE_SIDES+2, GL_UNSIGNED_INT, (void*)(39*sizeof(GLuint)));

    //create transformation
    glm:mat4 transform, transform1, transform2;
    transform = glm::rotate(transform, 0.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

    //draw car's body
    glDrawElements(GL_TRIANGLES, p.sizeArray[0], GL_UNSIGNED_INT, (void*)(p.offsetArray[0]*sizeof(GLuint)));
    glDrawElements(GL_TRIANGLES, p.sizeArray[1], GL_UNSIGNED_INT, (void*)(p.offsetArray[1]*sizeof(GLuint)));
    glDrawElements(GL_TRIANGLES, p.sizeArray[2], GL_UNSIGNED_INT, (void*)(p.offsetArray[2]*sizeof(GLuint)));

    //activate transformation
    transform1 = glm::translate(transform1, glm::vec3(-0.33f, -0.1f, 0));
    transform1 = glm::rotate(transform1, (float)glfwGetTime()*(-2), glm::vec3(0.0f, 0.0f, 1.0f));
    transform1 = glm::translate(transform1, glm::vec3(0.33f, 0.1f, 0));
    transformLoc = glGetUniformLocation(shaderProgram, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform1));

    //draw back tire
    glDrawElements(GL_TRIANGLE_FAN, p.sizeArray[3], GL_UNSIGNED_INT, (void*)(p.offsetArray[3]*sizeof(GLuint)));

    //activate transformation
    transform2 = glm::translate(transform2, glm::vec3(0.33f, -0.1f, -1.0f));
    transform2 = glm::rotate(transform2, (float)glfwGetTime()*(-2), glm::vec3(0.0f, 0.0f, 1.0f));
    transform2 = glm::translate(transform2, glm::vec3(-0.33f, 0.1f, 1.0f));
    transformLoc = glGetUniformLocation(shaderProgram, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform2));
    
    //draw front tire
    glDrawElements(GL_TRIANGLE_FAN, p.sizeArray[4], GL_UNSIGNED_INT, (void*)(p.offsetArray[4]*sizeof(GLuint)));
    
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

