// Include GLFW
#include <GLFW/glfw3.h>
extern GLFWwindow* window; // The "extern" keyword here is to access the variable "window" declared in tutorialXXX.cpp. This is a hack to keep the tutorials simple. Please avoid this.

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;
#include <stdio.h>
#include "controls.hpp"

// Initial horizontal angle : toward -Z
float horizontalAngle = 3.14f;
// Initial vertical angle : none
float verticalAngle = 0.0f;
// Initial Field of View
float initialFoV = 30.0f;
// Direction : Spherical coordinates to Cartesian coordinates conversion
glm::vec3 direction = glm::vec3 (
    cos(verticalAngle) * sin(horizontalAngle),
    sin(verticalAngle),
    cos(verticalAngle) * cos(horizontalAngle)
);
// Right vector
glm::vec3 right = glm::vec3(
    sin(horizontalAngle - 3.14f/2.0f),
    0,
    cos(horizontalAngle - 3.14f/2.0f)
);
// Up vector : perpendicular to both direction and right
glm::vec3 up = glm::cross( right, direction );
// Initial position : on +Z
glm::vec3 position = glm::vec3( 0, 0, 5 ); 
glm::vec3 center = glm::vec3(0.0f, 0.0f, 0.0f);

glm::mat4 ViewMatrix = glm::lookAt(
								position,           // Camera is here
								center, // and looks here 
								up // Head is up (set to 0,-1,0 to look upside-down)
						   );     
glm::mat4 ProjectionMatrix = glm::perspective(glm::radians(initialFoV), 4.0f / 3.0f, 0.1f, 100.0f);

glm::mat4 getViewMatrix(){
	return ViewMatrix;
}
glm::mat4 getProjectionMatrix(){
	return ProjectionMatrix;
}

// void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
// {
// 	glm::mat4 transform;
// 	glm::vec4 temp;
//   if (key == GLFW_KEY_UP){
// 		transform = glm::rotate(glm::mat4(1.0f), glm::radians(5.0f), right);
//   	temp = transform * vec4(position, 1.0f);
//   	position = vec3(temp.x, temp.y, temp.z);
// 	}
// 	// Move backward
// 	if (key == GLFW_KEY_DOWN){
// 		transform = glm::rotate(glm::mat4(1.0f), glm::radians(-5.0f), right);
//   	temp = transform * vec4(position, 1.0f);
//   	position = vec3(temp.x, temp.y, temp.z);
// 	}
// 	// Strafe right
// 	if (key == GLFW_KEY_RIGHT){
// 		transform = glm::rotate(glm::mat4(1.0f), glm::radians(-5.0f), up);
//   	temp = transform * vec4(position, 1.0f);
//   	position = vec3(temp.x, temp.y, temp.z);
// 	}
// 	// Strafe left
// 	if (key == GLFW_KEY_LEFT){
// 		transform = glm::rotate(glm::mat4(1.0f), glm::radians(5.0f), up);
//   	temp = transform * vec4(position, 1.0f);
//   	position = vec3(temp.x, temp.y, temp.z);
// 	}
// 	// Camera matrix
// 	ViewMatrix = glm::lookAt(
// 								position, // Camera is here
// 								center, // and looks here : at the same position, plus "direction"
// 								up // Head is up (set to 0,-1,0 to look upside-down)
// 						   );        
// }	

void computeMatricesFromInputs(){
	glm::mat4 transform;
	glm::vec4 temp;

	// Move forward
	if (glfwGetKey( window, GLFW_KEY_UP ) == GLFW_PRESS){
		transform = glm::rotate(glm::mat4(1.0f), glm::radians(4.0f), right);
  	temp = transform * vec4(position, 1.0f);
  	position = vec3(temp.x, temp.y, temp.z);
	}
	// Move backward
	if (glfwGetKey( window, GLFW_KEY_DOWN ) == GLFW_PRESS){
		transform = glm::rotate(glm::mat4(1.0f), glm::radians(-4.0f), right);
  	temp = transform * vec4(position, 1.0f);
  	position = vec3(temp.x, temp.y, temp.z);
	}
	// Strafe right
	if (glfwGetKey( window, GLFW_KEY_RIGHT ) == GLFW_PRESS){
		transform = glm::rotate(glm::mat4(1.0f), glm::radians(-4.0f), up);
  	temp = transform * vec4(position, 1.0f);
  	position = vec3(temp.x, temp.y, temp.z);
	}
	// Strafe left
	if (glfwGetKey( window, GLFW_KEY_LEFT ) == GLFW_PRESS){
		transform = glm::rotate(glm::mat4(1.0f), glm::radians(4.0f), up);
  	temp = transform * vec4(position, 1.0f);
  	position = vec3(temp.x, temp.y, temp.z);
	}

	float FoV = initialFoV;// - 5 * glfwGetMouseWheel(); // Now GLFW 3 requires setting up a callback for this. It's a bit too complicated for this beginner's tutorial, so it's disabled instead.

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	ProjectionMatrix = glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);
	// Camera matrix
	ViewMatrix = glm::lookAt(
								position,           // Camera is here
								glm::vec3(0.0f, 0.0f, 0.0f), // and looks here : at the same position, plus "direction"
								glm::vec3(0.0f, 1.0f, 0.0f) // Head is up (set to 0,-1,0 to look upside-down)
						   );
}
