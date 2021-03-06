#ifndef CONTROLS_HPP
#define CONTROLS_HPP

void computeMatricesFromInputs();
void setPosition(float x, float y, float z);
glm::mat4 getViewMatrix();
glm::mat4 getProjectionMatrix();
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

#endif
