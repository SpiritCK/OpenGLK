#ifndef OPENGLK_POLYGON_H
#define OPENGLK_POLYGON_H

#include <GLFW/glfw3.h>
#include <vector>
#include <utility>

class Polygon {
public:
  static const int POS_X = 0;
  static const int POS_Y = 1;
  static const int POS_Z = 2;
  static const int COLOR_R = 3;
  static const int COLOR_G = 4;
  static const int COLOR_B = 5;
  static const int TEXTURE_X = 6;
  static const int TEXTURE_Y = 7;
  
  std::vector<GLfloat> dataArray;
  std::vector<GLuint> elementArray;
  std::vector<unsigned int> offsetArray;
  std::vector<unsigned int> sizeArray;
  std::vector<GLenum> modeArray;
  
  Polygon() {}
  Polygon(int n, int* a);
  void addPolygon(GLfloat* arr, int num_of_point, GLuint* ele, int num_of_ele, GLfloat r, GLfloat g, GLfloat b);
  void addPolygon(GLfloat* arr, int num_of_point, GLuint* ele, int num_of_ele, GLfloat* col);
  void addCircle(GLfloat x, GLfloat y, GLfloat r, GLfloat color_r, GLfloat color_g, GLfloat color_b, int n);
  
  GLfloat* getArrays();
  GLuint* getElements();
  void print();

private:
  int n;
  int offset[8] = {-1, -1, -1, -1, -1, -1, -1, -1};

  void pushData(GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat g, GLfloat b, GLfloat tx, GLfloat ty);
};

#endif
