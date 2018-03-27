#include<iostream>
#include<math.h>
#include "shape.h"

void addPolygon(GLfloat* &arr_a, int &num_of_point_a, GLuint* &ele_a, int &num_of_element_a, GLfloat* arr_b, int num_of_point_b, GLuint* ele_b, int num_of_element_b, std::vector<std::pair<int, int>> &segments) {

    segments.push_back(std::make_pair(num_of_element_a, num_of_element_b));

    auto arr_result = new GLfloat[5*(num_of_point_a + num_of_point_b)];
    auto ele_result = new GLuint[num_of_element_a + num_of_element_b];

    for(int i = 0; i < 5*num_of_point_a; i++) {
        arr_result[i] = arr_a[i];
    }

    for(int i = 0; i < 5*num_of_point_b; i++) {
        arr_result[5*num_of_point_a + i] = arr_b[i];
    }
    
    for (int i = 0; i < num_of_element_a; i++) {
        ele_result[i] = ele_a[i];
    }
    
    for (int i = 0; i < num_of_element_b; i++) {
        ele_result[num_of_element_a + i] = ele_b[i] + num_of_point_a;
    }

    delete[] arr_a;
    delete[] ele_a;

    arr_a = arr_result;
    ele_a = ele_result;
    num_of_point_a = num_of_point_a + num_of_point_b;
    num_of_element_a = num_of_element_a + num_of_element_b;
    
}

GLfloat* createPolygon(GLfloat* arr, int num_of_point, GLfloat r, GLfloat g, GLfloat b) {
  
  GLfloat* result_arr = new GLfloat[num_of_point * 5];
  for (int i = 0; i < num_of_point; i++) {
    result_arr[5*i] = arr[2*i];
    result_arr[5*i + 1] = arr[2*i + 1];
    result_arr[5*i + 2] = r;
    result_arr[5*i + 3] = g;
    result_arr[5*i + 4] = b;
  }
  
  return result_arr;
  
}

GLfloat* createCircle(GLfloat x, GLfloat y, GLfloat r, GLfloat color_r, GLfloat color_g, GLfloat color_b, int n) {

    auto result = new GLfloat[(n + 1) * 5];
    
    result[0] = x;
    result[1] = y;
    result[2] = color_r;
    result[3] = color_g;
    result[4] = color_b;

    for (int i = 1; i < n+1; i++) {
        result[5*i] = x + (r * cos(i*2*M_PI / n));
        result[5*i + 1] = y + (r * sin(i*2*M_PI / n));
        result[5*i + 2] = color_r;
        result[5*i + 3] = color_g;
        result[5*i + 4] = color_b;
    }

    return result;
}

GLuint* createCircleElements(int n) {

    auto result = new GLuint[(n + 2)];

    for (int i = 0; i < n+1; i++) {
        result[i] = i;
    }
    result[n+1] = 1;

    return result;
}
