#include<math.h>
#include<iostream>
#include "polygon.h"

using namespace std;

Polygon::Polygon(int n, int* a) {
  this->n = n;
  for (int i = 0; i <n; i++) {
    offset[a[i]] = i;
  }
}

void Polygon::pushData(GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat g, GLfloat b, GLfloat tx, GLfloat ty) {
  unsigned int start = dataArray.size();
  for (int i = 0; i < n; i++) {
    dataArray.push_back(0);
  }
  //printf("Start push at: %d\n", start);
  //printf("Offset pos x: %d\n", offset[POS_X]);
  if (offset[POS_X] != -1) {
    dataArray[start + offset[POS_X]] = x;
    printf("  Pushing pos x: %.2f\n", x);
  }
  //printf("Offset pos y: %d\n", offset[POS_Y]);
  if (offset[POS_Y] != -1) {
    dataArray[start + offset[POS_Y]] = y;
    printf("  Pushing pos y: %.2f\n", y);
  }
  //printf("Offset pos z: %d\n", offset[POS_Z]);
  if (offset[POS_Z] != -1) {
    dataArray[start + offset[POS_Z]] = z;
    printf("  Pushing pos z: %.2f\n", z);
  }
  //printf("Offset col r: %d\n", offset[COLOR_R]);
  if (offset[COLOR_R] != -1) {
    dataArray[start + offset[COLOR_R]] = r;
    printf("  Pushing col r: %.2f\n", r);
  }
  //printf("Offset col g: %d\n", offset[COLOR_G]);
  if (offset[COLOR_G] != -1) {
    dataArray[start + offset[COLOR_G]] = g;
    printf("  Pushing col g: %.2f\n", g);
  }
  //printf("Offset col b: %d\n", offset[COLOR_B]);
  if (offset[COLOR_B] != -1) {
    dataArray[start + offset[COLOR_B]] = b;
    printf("  Pushing col b: %.2f\n", b);
  }
  //printf("Offset tex x: %d\n", offset[TEXTURE_X]);
  if (offset[TEXTURE_X] != -1) {
    dataArray[start + offset[TEXTURE_X]] = tx;
    printf("  Pushing tex x: %.2f\n", tx);
  }
  //printf("Offset tex y: %d\n", offset[TEXTURE_Y]);
  if (offset[TEXTURE_Y] != -1) {
    dataArray[start + offset[TEXTURE_Y]] = ty;
    printf("  Pushing tex y: %.2f\n", ty);
  }
  //printf("Done\n");
}

/*
    arr: position x, y, z
    num_of_point * 3 = arr.size
*/
void Polygon::addPolygon(GLfloat* arr, int num_of_point, GLuint* ele, int num_of_ele, GLfloat r, GLfloat g, GLfloat b) {
  
  offsetArray.push_back(elementArray.size());
  sizeArray.push_back(num_of_ele);
  GLuint lastEle = dataArray.size() / n;
  printf("Last element: %d\n", lastEle);
  
  printf("Pushing data\n");
  for (int i = 0; i < num_of_point; i++) {
    printf("  Push from %lu:\n    %.2f, %.2f, %.2f\n    %.2f, %.2f, %.2f\n    %.2f, %.2f\n", dataArray.size(), arr[3*i + 0], arr[3*i + 1], arr[3*i + 2], r, g, b, (GLfloat) 0.0f, (GLfloat) 0.0f);
    pushData(arr[3*i + 0], arr[3*i + 1], arr[3*i + 2], r, g, b, (GLfloat) 0.0f, (GLfloat) 0.0f);
  }
  
  printf("Pushing element\n");
  for (int i = 0; i < num_of_ele; i++) {
    printf("  Push %d\n", ele[i] + lastEle);
    elementArray.push_back(ele[i] + lastEle);
  }
  //printf("X6\n");
}

void Polygon::addCircle(GLfloat x, GLfloat y, GLfloat r, GLfloat color_r, GLfloat color_g, GLfloat color_b, int n) {
  
  offsetArray.push_back(elementArray.size());
  sizeArray.push_back(n+2);
  GLuint lastEle = dataArray.size() / this->n;
  printf("Size now: %lu\n", dataArray.size());
  printf("N now: %d\n", n);
  printf("Last element: %u\n", lastEle);

  printf("Pushing data\n");
  printf("  Push from %lu:\n    %.2f, %.2f, %.2f\n    %.2f, %.2f, %.2f\n    %.2f, %.2f\n", dataArray.size(), x, y, (GLfloat) 0.0f, color_r, color_g, color_b, (GLfloat) 0.0f, (GLfloat) 0.0f);
  pushData(x, y, (GLfloat) 0.0f, color_r, color_g, color_b, (GLfloat) 0.0f, (GLfloat) 0.0f);
  printf("  Size now: %lu\n", dataArray.size());

 for (int i = 1; i < n+1; i++) {
      printf("  Push from %lu:\n    %.2f, %.2f, %.2f\n    %.2f, %.2f, %.2f\n    %.2f, %.2f\n", dataArray.size(), x + (r * cos(i*2*M_PI / n)), y + (r * sin(i*2*M_PI / n)), (GLfloat) 0.0f, color_r, color_g, color_b, (GLfloat) 0.0f, (GLfloat) 0.0f);
      pushData(x + (r * cos(i*2*M_PI / n)), y + (r * sin(i*2*M_PI / n)), (GLfloat) 0.0f, color_r, color_g, color_b, (GLfloat) 0.0f, (GLfloat) 0.0f);
  printf("  Size now: %lu\n", dataArray.size());
  }
    
  printf("Pushing element\n");
  for (int i = 0; i < n+1; i++) {
    printf("  Push %d\n", i + lastEle);
      elementArray.push_back(i + lastEle);
  }
    printf("  Push %d\n", 1 + lastEle);
  elementArray.push_back(1 + lastEle);
}

GLfloat* Polygon::getArrays() {
  auto result = new GLfloat[dataArray.size()];
    
  for (int i = 0; i < dataArray.size(); i++) {
    result[i] = dataArray[i];
  }

  return result;
}

GLuint* Polygon::getElements() {
  auto result = new GLuint[elementArray.size()];
    
  for (int i = 0; i < elementArray.size(); i++) {
    result[i] = elementArray[i];
  }

  return result;
}

void Polygon::print() {
  printf("Dimension: %d\n", n);
  printf("    Offset pos x: %d\n", offset[POS_X]);
  printf("    Offset pos y: %d\n", offset[POS_Y]);
  printf("    Offset pos z: %d\n", offset[POS_Z]);
  printf("    Offset col r: %d\n", offset[COLOR_R]);
  printf("    Offset col g: %d\n", offset[COLOR_G]);
  printf("    Offset col b: %d\n", offset[COLOR_B]);
  printf("    Offset tex x: %d\n", offset[TEXTURE_X]);
  printf("    Offset tex y: %d\n", offset[TEXTURE_Y]);
  
  printf("\nPoints: %lu", dataArray.size());
  for (int i = 0; i < dataArray.size(); i++) {
    if (i % n == 0)
      printf("\n    ");
    printf("%.2f ", dataArray[i]);
  }
  
  printf("\nElements: %lu\n", elementArray.size());
  for (int i = 0; i < elementArray.size(); i++) {
    printf("    %d\n", elementArray[i]);
  }
  
  printf("\nOffsets: %lu\n", offsetArray.size());
  for (int i = 0; i < offsetArray.size(); i++) {
    printf("    %d\n", offsetArray[i]);
  }
  
  printf("\nSize: %lu\n", sizeArray.size());
  for (int i = 0; i < sizeArray.size(); i++) {
    printf("    %d\n", sizeArray[i]);
  }
}

