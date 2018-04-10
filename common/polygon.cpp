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
  if (offset[POS_X] != -1) {
    dataArray[start + offset[POS_X]] = x;
  }
  if (offset[POS_Y] != -1) {
    dataArray[start + offset[POS_Y]] = y;
  }
  if (offset[POS_Z] != -1) {
    dataArray[start + offset[POS_Z]] = z;
  }
  if (offset[COLOR_R] != -1) {
    dataArray[start + offset[COLOR_R]] = r;
  }
  if (offset[COLOR_G] != -1) {
    dataArray[start + offset[COLOR_G]] = g;
  }
  if (offset[COLOR_B] != -1) {
    dataArray[start + offset[COLOR_B]] = b;
  }
  if (offset[TEXTURE_X] != -1) {
    dataArray[start + offset[TEXTURE_X]] = tx;
  }
  if (offset[TEXTURE_Y] != -1) {
    dataArray[start + offset[TEXTURE_Y]] = ty;
  }
}

/*
    arr: position x, y, z
    num_of_point * 3 = arr.size
*/
void Polygon::addPolygon(GLfloat* arr, int num_of_point, GLuint* ele, int num_of_ele, GLfloat r, GLfloat g, GLfloat b) {
  
  offsetArray.push_back(elementArray.size());
  sizeArray.push_back(num_of_ele);
  GLuint lastEle = dataArray.size() / n;
  
  for (int i = 0; i < num_of_point; i++) {
    pushData(arr[3*i + 0], arr[3*i + 1], arr[3*i + 2], r, g, b, (GLfloat) 0.0f, (GLfloat) 0.0f);
  }
  
  for (int i = 0; i < num_of_ele; i++) {
    elementArray.push_back(ele[i] + lastEle);
  }
}

/*
    col: colors (r, g, b), should be the same as the number of vertices
*/
void Polygon::addPolygon(GLfloat* arr, int num_of_point, GLuint* ele, int num_of_ele, GLfloat* col) {
  
  offsetArray.push_back(elementArray.size());
  sizeArray.push_back(num_of_ele);
  GLuint lastEle = dataArray.size() / n;
  
  for (int i = 0; i < num_of_point; i++) {
    pushData(arr[3*i + 0], arr[3*i + 1], arr[3*i + 2], col[3*i + 0], col[3*i + 1], col[3*i + 2], (GLfloat) 0.0f, (GLfloat) 0.0f);
  }
  
  for (int i = 0; i < num_of_ele; i++) {
    elementArray.push_back(ele[i] + lastEle);
  }
}

void Polygon::addPolygon(GLfloat* arr, GLfloat* tex, int num_of_point, GLuint* ele, int num_of_ele) {
  offsetArray.push_back(elementArray.size());
  sizeArray.push_back(num_of_ele);
  GLuint lastEle = dataArray.size() / n;
  
  for (int i = 0; i < num_of_point; i++) {
    pushData(arr[3*i + 0], arr[3*i + 1], arr[3*i + 2], (GLfloat) 0.0f, (GLfloat) 0.0f, (GLfloat) 0.0f, tex[2*i + 0], tex[2*i + 1]);
  }
  
  for (int i = 0; i < num_of_ele; i++) {
    elementArray.push_back(ele[i] + lastEle);
  }
}

void Polygon::addCircle(GLfloat x, GLfloat y, GLfloat r, GLfloat color_r, GLfloat color_g, GLfloat color_b, int n) {
  
  offsetArray.push_back(elementArray.size());
  sizeArray.push_back(n+2);
  GLuint lastEle = dataArray.size() / this->n;

  pushData(x, y, (GLfloat) 0.0f, color_r, color_g, color_b, (GLfloat) 0.0f, (GLfloat) 0.0f);

 for (int i = 1; i < n+1; i++) {
      pushData(x + (r * cos(i*2*M_PI / n)), y + (r * sin(i*2*M_PI / n)), (GLfloat) 0.0f, color_r, color_g, color_b, (GLfloat) 0.0f, (GLfloat) 0.0f);
  }
    
  for (int i = 0; i < n+1; i++) {
      elementArray.push_back(i + lastEle);
  }
  elementArray.push_back(1 + lastEle);
}

void Polygon::addCylinder(GLfloat x, GLfloat y, GLfloat z, GLfloat r, int direction, GLfloat l, GLfloat color_r, GLfloat color_g, GLfloat color_b, int n) {
  
  offsetArray.push_back(elementArray.size());
  sizeArray.push_back(4*n*3);
  GLuint lastEle = dataArray.size() / this->n;
  
  GLfloat pairX, pairY, pairZ;

  switch (direction) {
    case POS_X :
      pairX = x+l;
      pairY = y;
      pairZ = z;
      break;
    case POS_Y :
      pairX = x;
      pairY = y+l;
      pairZ = z;
      break;
    case POS_Z :
      pairX = x;
      pairY = y;
      pairZ = z+l;
      break;
  }
  pushData(x, y, z, color_r, color_g, color_b, (GLfloat) 0.0f, (GLfloat) 0.0f);
  pushData(pairX, pairY, pairZ, color_r, color_g, color_b, (GLfloat) 0.0f, (GLfloat) 0.0f);

  for (int i = 0; i < n; i++) {
      switch (direction) {
        case POS_X:
          pushData(x, y + (r * cos(i*2*M_PI / n)), z + (r * sin(i*2*M_PI / n)), color_r, color_g, color_b, (GLfloat) 0.0f, (GLfloat) 0.0f);
          pushData(pairX, pairY + (r * cos(i*2*M_PI / n)), pairZ + (r * sin(i*2*M_PI / n)), color_r, color_g, color_b, (GLfloat) 0.0f, (GLfloat) 0.0f);
        break;
        case POS_Y:
          pushData(x + (r * sin(i*2*M_PI / n)), y, z + (r * cos(i*2*M_PI / n)), color_r, color_g, color_b, (GLfloat) 0.0f, (GLfloat) 0.0f);
          pushData(pairX + (r * sin(i*2*M_PI / n)), pairY, pairZ + (r * cos(i*2*M_PI / n)), color_r, color_g, color_b, (GLfloat) 0.0f, (GLfloat) 0.0f);
        break;
        case POS_Z:
          pushData(x + (r * cos(i*2*M_PI / n)), y + (r * sin(i*2*M_PI / n)), z, color_r, color_g, color_b, (GLfloat) 0.0f, (GLfloat) 0.0f);
          pushData(pairX + (r * cos(i*2*M_PI / n)), pairY + (r * sin(i*2*M_PI / n)), pairZ, color_r, color_g, color_b, (GLfloat) 0.0f, (GLfloat) 0.0f);
        break;
      }
      
  }
    
  for (int i = 0; i < n; i++) {
      elementArray.push_back(2*i+2 + lastEle);
      elementArray.push_back(lastEle);
      elementArray.push_back(2*((i+1)%n)+2 + lastEle);
  }
  for (int i = 0; i < n; i++) {
      elementArray.push_back(2*i+3 + lastEle);
      elementArray.push_back(1 + lastEle);
      elementArray.push_back(2*((i+1)%n)+3 + lastEle);
  }
  for (int i = 0; i < 2*n; i++) {
      elementArray.push_back(i+2 + lastEle);
      elementArray.push_back((i+1)%(2*n)+2 + lastEle);
      elementArray.push_back((i+2)%(2*n)+2 + lastEle);
  }
  
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
  
  printf("\nPoints: %lu", dataArray.size() / n);
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

