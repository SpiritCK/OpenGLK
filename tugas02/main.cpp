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
#include "common/shape.h"

#define WINDOW_WIDTH 712
#define WINDOW_HEIGHT 712
#define WINDOW_TITLE "Running car"
#define CIRCLE_SIDES 5
#define VERTEX_SHADER_FILE "tugas02/shader/VertexShader.vsgl"
#define FRAGMENT_SHADER_FILE "tugas02/shader/FragmentShader.fsgl"

void addCar(GLfloat* &vertices, int &num_vertices, GLuint* &elements, int &num_elements, std::vector<std::pair<int, int>> &segments) {
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
  
  addPolygon(
      vertices, 
      num_vertices, 
      elements, 
      num_elements, 
      createPolygon(
          carBodyVertices, 
          9, 
          1.0f, 1.0f, 0.0f), 
      9, 
      carBodyElements, 
      21,
      segments);
  addPolygon(
      vertices, 
      num_vertices, 
      elements, 
      num_elements, 
      createPolygon(
          carDoorVertices, 
          6, 
          0.9f,  0.5f, 0.0f), 
      6, 
      carDoorElements, 
      12,
      segments);
  addPolygon(
      vertices, 
      num_vertices, 
      elements, 
      num_elements, 
      createPolygon(
          doorWindowVertices, 
          4, 
          0.1f, 0.5f, 1.0f), 
      4, 
      doorWindowElements, 
      6,
      segments);
  addPolygon(
      vertices, 
      num_vertices, 
      elements, 
      num_elements, 
      createCircle(
          -0.45f, -0.05f, 0.15f,
          0.3f, 0.3f, 0.3f,
          CIRCLE_SIDES),
      CIRCLE_SIDES+1,
      createCircleElements(CIRCLE_SIDES),
      CIRCLE_SIDES+2,
      segments);
  addPolygon(
      vertices, 
      num_vertices, 
      elements, 
      num_elements, 
      createCircle(
          0.5f, -0.05f, 0.15f,
          0.3f, 0.3f, 0.3f,
          CIRCLE_SIDES),
      CIRCLE_SIDES+1,
      createCircleElements(CIRCLE_SIDES),
      CIRCLE_SIDES+2,
      segments);
  
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
  GLfloat* vertices = new GLfloat;
  int vertex_num = 0;
  GLuint* elements = new GLuint;
  int elements_num = 0;
  std::vector<std::pair<int, int>> segments;
  
  addCar(vertices, vertex_num, elements, elements_num, segments);
  printf("Vertex num: %d\n", vertex_num);
  for (int i = 0; i < vertex_num; i++) {
    printf("%d. %.2f %.2f %.2f %.2f %.2f\n", i, vertices[5*i], vertices[5*i+1], vertices[5*i+2], vertices[5*i+3], vertices[5*i+4]);
  }
  printf("Elements num: %d\n", elements_num);
  for (int i = 0; i < elements_num; i++) {
    printf("%d. %d\n", i, elements[i]);
  }
  printf("Segments num: %ld\n", segments.size());
  for (int i = 0; i < segments.size(); i++) {
    printf("%d. %d %d\n", i, segments[i].first, segments[i].second);
  }
  
  GLuint vertexbuffer;
  glGenBuffers(1, &vertexbuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
  glBufferData(GL_ARRAY_BUFFER, vertex_num * sizeof(GLfloat) * 5, vertices, GL_STATIC_DRAW);
  
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
    glDrawElements(GL_TRIANGLES, segments[0].second, GL_UNSIGNED_INT, (void*)(segments[0].first*sizeof(GLuint)));
    glDrawElements(GL_TRIANGLES, segments[1].second, GL_UNSIGNED_INT, (void*)(segments[1].first*sizeof(GLuint)));
    glDrawElements(GL_TRIANGLES, segments[2].second, GL_UNSIGNED_INT, (void*)(segments[2].first*sizeof(GLuint)));

    //activate transformation
    transform1 = glm::translate(transform1, glm::vec3(-0.45f, -0.05f, 0));
    transform1 = glm::rotate(transform1, (float)glfwGetTime()*(-2), glm::vec3(0.0f, 0.0f, 1.0f));
    transform1 = glm::translate(transform1, glm::vec3(0.45f, 0.05f, 0));
    transformLoc = glGetUniformLocation(shaderProgram, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform1));

    //draw back tire
    glDrawElements(GL_TRIANGLE_FAN, segments[3].second, GL_UNSIGNED_INT, (void*)(segments[3].first*sizeof(GLuint)));

    //activate transformation
    transform2 = glm::translate(transform2, glm::vec3(0.5f, -0.05f, -1.0f));
    transform2 = glm::rotate(transform2, (float)glfwGetTime()*(-2), glm::vec3(0.0f, 0.0f, 1.0f));
    transform2 = glm::translate(transform2, glm::vec3(-0.5f, 0.05f, 1.0f));
    transformLoc = glGetUniformLocation(shaderProgram, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform2));
    
    //draw front tire
    glDrawElements(GL_TRIANGLE_FAN, segments[4].second, GL_UNSIGNED_INT, (void*)(segments[4].first*sizeof(GLuint)));
    
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

