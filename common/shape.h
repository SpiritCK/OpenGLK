#ifndef OPENGLK_SHAPE_H
#define OPENGLK_SHAPE_H

#include <GLFW/glfw3.h>
#include <vector>
#include <utility>

void addPolygon(GLfloat* &arr_a, int &num_of_point_a, GLuint* &ele_a, int &num_of_triangle_a, GLfloat* arr_b, int num_of_point_b, GLuint* ele_b, int num_of_triangle_b, std::vector<std::pair<int, int>> &segments);
GLfloat* createPolygon(GLfloat* arr, int num_of_point, GLfloat r, GLfloat g, GLfloat b);
GLfloat* createCircle(GLfloat x, GLfloat y, GLfloat r, GLfloat color_r, GLfloat color_g, GLfloat color_b, int n);
GLuint* createCircleElements(int n);

#endif
