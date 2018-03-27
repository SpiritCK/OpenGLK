#include "shape.h"

void addPolygon(GLfloat* &arr_a, int &num_of_point_a, GLuint* &ele_a, int &num_of_triangle_a, GLfloat* arr_b, int num_of_point_b, GLuint* ele_b, int num_of_triangle_b) {

    auto arr_result = new GLfloat[5*(num_of_point_a + num_of_point_b)];
    auto ele_result = new GLuint[3*(num_of_triangle_a + num_of_triangle_b)];

    for(int i = 0; i < 5*num_of_point_a; i++) {
        arr_result[i] = arr_a[i];
    }

    for(int i = 0; i < 5*num_of_point_b; i++) {
        arr_result[5*num_of_point_a + i] = arr_b[i];
    }
    
    for (int i = 0; i < 3*num_of_triangle_a; i++) {
        ele_result[i] = ele_a[i];
    }
    
    for (int i = 0; i < 3*num_of_triangle_b; i++) {
        ele_result[3*num_of_triangle_a + i] = ele_b[i] + num_of_point_a;
    }

    /*if (arr_a != NULL)
        delete arr_a;
    if (arr_b != NULL)
        delete arr_b;
    if (ele_a != NULL)
        delete ele_a;
    if (ele_b != NULL)
        delete ele_b;*/

    arr_a = arr_result;
    ele_a = ele_result;
    num_of_point_a = num_of_point_a + num_of_point_b;
    num_of_triangle_a = num_of_triangle_a + num_of_triangle_b;
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
