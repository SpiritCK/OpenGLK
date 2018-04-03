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

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768
#define WINDOW_TITLE "Colored cube"
#define CIRCLE_SIDES 13
#define VERTEX_SHADER_FILE "tugas02_test/shader/VertexShader.vsgl"
#define FRAGMENT_SHADER_FILE "tugas02_test/shader/FragmentShader.fsgl"

/*
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
*/

void addCube(Polygon &p) {
  float carWidth = 0.5f;
  GLfloat vertices[] = {
      // Car body
       -0.66805f, -0.078826f, carWidth/2,//0l==========1
       -0.45326f, -0.0760366f, carWidth/2,//1l
       -0.567629f, 0.334019f, carWidth/2,//13l
       -0.45326f, -0.0760366f, carWidth/2,//1l=========2
       -0.416996f, 0.0215956f, carWidth/2,//2l
       -0.567629f, 0.334019f, carWidth/2,//13l
       -0.416996f, 0.0215956f, carWidth/2,//2l===========3
       -0.252416f, 0.0215956f, carWidth/2,//3l
       -0.567629f, 0.334019f, carWidth/2,//13l
       -0.252416f, 0.0215956f, carWidth/2,//3l==========4
       -0.567629f, 0.334019f, carWidth/2,//13l
       0.129744f, 0.336808f, carWidth/2,//12l
       -0.252416f, 0.0215956f, carWidth/2,//3l=========5
       -0.213363f, -0.0760366f, carWidth/2,//4l
       0.129744f, 0.336808f, carWidth/2,//12l
       -0.213363f, -0.0760366f, carWidth/2,//4l==========6
       0.205061f, -0.078826f, carWidth/2,//5l
       0.129744f, 0.336808f, carWidth/2,//12l
       0.205061f, -0.078826f, carWidth/2,//5l==========7
       0.244113f, 0.0355431f, carWidth/2,//6l
       0.129744f, 0.336808f, carWidth/2,//12l
       0.244113f, 0.0355431f, carWidth/2,//6l=========8
       0.129744f, 0.336808f, carWidth/2,//12l
       0.311061f, 0.155491f, carWidth/2,//11l
       0.244113f, 0.0355431f, carWidth/2,//6l============9
       0.419852f, 0.0383326f, carWidth/2,//7l
       0.311061f, 0.155491f, carWidth/2,//11l
       0.419852f, 0.0383326f, carWidth/2,//7l=========10
       0.456115f, -0.0788259f, carWidth/2,//8l
       0.311061f, 0.155491f, carWidth/2,//11l
       0.456115f, -0.0788259f, carWidth/2,//8l==========11
       0.729485f, -0.0816154f, carWidth/2,//9l
       0.311061f, 0.155491f, carWidth/2,//11l
       0.729485f, -0.0816154f, carWidth/2,//9l==========12
       0.662537f, 0.096912f, carWidth/2,//10l
       0.311061f, 0.155491f, carWidth/2,//11l


        -0.66805f, -0.078826f, -carWidth/2,//0r==========13
        -0.45326f, -0.0760366f, -carWidth/2,//1r
        -0.567629f, 0.334019f, -carWidth/2,//13r
        -0.45326f, -0.0760366f, -carWidth/2,//1r=========14
        -0.416996f, 0.0215956f, -carWidth/2,//2r
        -0.567629f, 0.334019f, -carWidth/2,//13r
        -0.416996f, 0.0215956f, -carWidth/2,//2r===========15
        -0.252416f, 0.0215956f, -carWidth/2,//3r
        -0.567629f, 0.334019f, -carWidth/2,//13r
        -0.252416f, 0.0215956f, -carWidth/2,//3r==========16
        -0.567629f, 0.334019f, -carWidth/2,//13r
        0.129744f, 0.336808f, -carWidth/2,//12r
        -0.252416f, 0.0215956f, -carWidth/2,//3r=========17
        -0.213363f, -0.0760366f, -carWidth/2,//4r
        0.129744f, 0.336808f, -carWidth/2,//12r
        -0.213363f, -0.0760366f, -carWidth/2,//4r==========18
        0.205061f, -0.078826f, -carWidth/2,//5r
        0.129744f, 0.336808f, -carWidth/2,//12r
        0.205061f, -0.078826f, -carWidth/2,//5r==========19
        0.244113f, 0.0355431f, -carWidth/2,//6r
        0.129744f, 0.336808f, -carWidth/2,//12r
        0.244113f, 0.0355431f, -carWidth/2,//6r=========20
        0.129744f, 0.336808f, -carWidth/2,//12r
        0.311061f, 0.155491f, -carWidth/2,//11r
        0.244113f, 0.0355431f, -carWidth/2,//6r============21
        0.419852f, 0.0383326f, -carWidth/2,//7r
        0.311061f, 0.155491f, -carWidth/2,//11r
        0.419852f, 0.0383326f, -carWidth/2,//7r=========22
        0.456115f, -0.0788259f, -carWidth/2,//8r
        0.311061f, 0.155491f, -carWidth/2,//11r
        0.456115f, -0.0788259f, -carWidth/2,//8r==========23
        0.729485f, -0.0816154f, -carWidth/2,//9r
        0.311061f, 0.155491f, -carWidth/2,//11r
        0.729485f, -0.0816154f, -carWidth/2,//9r==========24
        0.662537f, 0.096912f, -carWidth/2,//10r
        0.311061f, 0.155491f, -carWidth/2,//11r


         -0.66805f, -0.078826f, carWidth/2,//0l==========25
        -0.66805f, -0.078826f, -carWidth/2,//0r
        -0.45326f, -0.0760366f, carWidth/2,//1l
        -0.45326f, -0.0760366f, -carWidth/2,//1r==26
        -0.45326f, -0.0760366f, carWidth/2,//1l
       -0.66805f, -0.078826f, -carWidth/2,//0r
       -0.45326f, -0.0760366f, carWidth/2,//1l=========27
       -0.45326f, -0.0760366f, -carWidth/2,//1r
       -0.416996f, 0.0215956f, carWidth/2,//2l
       -0.416996f, 0.0215956f, -carWidth/2,//2r==28
       -0.45326f, -0.0760366f, -carWidth/2,//1r
       -0.416996f, 0.0215956f, carWidth/2,//2l
       -0.416996f, 0.0215956f, carWidth/2,//2l========29
       -0.416996f, 0.0215956f, -carWidth/2,//2r
       -0.252416f, 0.0215956f, -carWidth/2,//3r
       -0.416996f, 0.0215956f, carWidth/2,//2l==30
       -0.252416f, 0.0215956f, -carWidth/2,//3r
       -0.252416f, 0.0215956f, carWidth/2,//3l
       -0.252416f, 0.0215956f, -carWidth/2,//3r==========31
       -0.252416f, 0.0215956f, carWidth/2,//3l
       -0.213363f, -0.0760366f, -carWidth/2,//4r
       -0.252416f, 0.0215956f, carWidth/2,//3l==32
       -0.213363f, -0.0760366f, -carWidth/2,//4r
       -0.213363f, -0.0760366f, carWidth/2,//4l
       -0.213363f, -0.0760366f, -carWidth/2,//4r==========33
       -0.213363f, -0.0760366f, carWidth/2,//4l
       0.205061f, -0.078826f, -carWidth/2,//5r
       -0.213363f, -0.0760366f, carWidth/2,//4l==34
       0.205061f, -0.078826f, -carWidth/2,//5r
       0.205061f, -0.078826f, carWidth/2,//5l
       0.205061f, -0.078826f, -carWidth/2,//5r========35
       0.205061f, -0.078826f, carWidth/2,//5l
       0.244113f, 0.0355431f, -carWidth/2,//6r
       0.205061f, -0.078826f, carWidth/2,//5l==36
       0.244113f, 0.0355431f, -carWidth/2,//6r
       0.244113f, 0.0355431f, carWidth/2,//6l
       0.244113f, 0.0355431f, -carWidth/2,//6r=======37
       0.244113f, 0.0355431f, carWidth/2,//6l
       0.419852f, 0.0383326f, -carWidth/2,//7r
       0.244113f, 0.0355431f, carWidth/2,//6l==38
       0.419852f, 0.0383326f, -carWidth/2,//7r
       0.419852f, 0.0383326f, carWidth/2,//7l
       0.419852f, 0.0383326f, -carWidth/2,//7r=========39
       0.419852f, 0.0383326f, carWidth/2,//7l
       0.456115f, -0.0788259f, -carWidth/2,//8r
       0.419852f, 0.0383326f, carWidth/2,//7l==40
       0.456115f, -0.0788259f, -carWidth/2,//8r
       0.456115f, -0.0788259f, carWidth/2,//8l
       0.456115f, -0.0788259f, -carWidth/2,//8r========41
       0.456115f, -0.0788259f, carWidth/2,//8l
       0.729485f, -0.0816154f, -carWidth/2,//9r
       0.456115f, -0.0788259f, carWidth/2,//8l==42
       0.729485f, -0.0816154f, -carWidth/2,//9r
       0.729485f, -0.0816154f, carWidth/2,//9l
       0.729485f, -0.0816154f, -carWidth/2,//9r=======43
       0.729485f, -0.0816154f, carWidth/2,//9l
       0.662537f, 0.096912f, -carWidth/2,//10r
       0.729485f, -0.0816154f, carWidth/2,//9l==44
       0.662537f, 0.096912f, -carWidth/2,//10r
       0.662537f, 0.096912f, carWidth/2,//10l
       0.662537f, 0.096912f, -carWidth/2,//10r=======45
       0.662537f, 0.096912f, carWidth/2,//10l
       0.311061f, 0.155491f, -carWidth/2,//11r
       0.662537f, 0.096912f, carWidth/2,//10l==46
       0.311061f, 0.155491f, -carWidth/2,//11r
       0.311061f, 0.155491f, carWidth/2,//11l
       0.311061f, 0.155491f, -carWidth/2,//11r========47
       0.311061f, 0.155491f, carWidth/2,//11l
       0.129744f, 0.336808f, -carWidth/2,//12r
       0.311061f, 0.155491f, carWidth/2,//11l==48
       0.129744f, 0.336808f, -carWidth/2,//12r
       0.129744f, 0.336808f, carWidth/2,//12l
       0.129744f, 0.336808f, -carWidth/2,//12r========49
       0.129744f, 0.336808f, carWidth/2,//12l
       -0.567629f, 0.334019f, -carWidth/2,//13r
       0.129744f, 0.336808f, carWidth/2,//12l==50
       -0.567629f, 0.334019f, -carWidth/2,//13r
       -0.567629f, 0.334019f, carWidth/2,//13l
       -0.567629f, 0.334019f, -carWidth/2,//13r========51
       -0.567629f, 0.334019f, carWidth/2,//13l
       -0.66805f, -0.078826f, -carWidth/2,//0r
       -0.567629f, 0.334019f, carWidth/2,//13l==52
       -0.66805f, -0.078826f, -carWidth/2,//0r
      -0.66805f, -0.078826f, carWidth/2,//0l

      //carDoor

       -0.051036f, 0.30187f, carWidth/2+0.0001f,
       0.113544f, 0.304659f, carWidth/2+0.0001f,
       0.205597f, 0.184711f, carWidth/2+0.0001f,
       0.200018f, 0.0563942f, carWidth/2+0.0001f,
       0.172123f, -0.0356591f, carWidth/2+0.0001f,
       -0.051036f, -0.0356591f, carWidth/2+0.0001f,
       -0.0818158f, 0.302335f, carWidth/2+0.0001f,
       -0.0818158f, -0.0359436f, carWidth/2+0.0001f,
       -0.200164f, -0.0349574f, carWidth/2+0.0001f,
       -0.241586f, 0.05479f, carWidth/2+0.0001f,
       -0.297801f, 0.0567625f, carWidth/2+0.0001f,
       -0.296815f, 0.215546f, carWidth/2+0.0001f,
       -0.262297f, 0.303321f, carWidth/2+0.0001f,

        -0.051036f, 0.30187f, -carWidth/2-0.0001f,
        0.113544f, 0.304659f, -carWidth/2-0.0001f,
        0.205597f, 0.184711f, -carWidth/2-0.0001f,
        0.200018f, 0.0563942f, -carWidth/2-0.0001f,
        0.172123f, -0.0356591f, -carWidth/2-0.0001f,
        -0.051036f, -0.0356591f, -carWidth/2-0.0001f,
        -0.0818158f, 0.302335f, -carWidth/2-0.0001f,
        -0.0818158f, -0.0359436f, -carWidth/2-0.0001f,
        -0.200164f, -0.0349574f, -carWidth/2-0.0001f,
        -0.241586f, 0.05479f, -carWidth/2-0.0001f,
        -0.297801f, 0.0567625f, -carWidth/2-0.0001f,
        -0.296815f, 0.215546f, -carWidth/2-0.0001f,
        -0.262297f, 0.303321f, -carWidth/2-0.0001f
  };
  GLuint elements[] = {
    //CarBody
    0, 1, 2,//1
    3,4,5,//2
    6,7,8,//3
    9,10,11,//4
    12,13,14,//5
    15,16,17,//6
    18,19,20,//7
    21,22,23,//8
    24,25,26,//9
    27,28,29,//10
    30,31,32,//11
    33,34,35,//12

    36,37,38,//13
    39,40,41,//14
    42,43,44,//15
    45,46,47,//16
    48,49,50,//17
    51,52,53,//18
    54,55,56,//19
    57,58,59,//20
    60,61,62,//21
    63,64,65,//22
    66,67,68,//23
    69,70,71,//24

    72,73,74,//25
    75,76,77,//26
    78,79,80,//27
    81,82,83,//28
    84,85,86,//29
    87,88,89,//30
    90,91,92,//31
    93,94,95,//32
    96,97,98,//33
    99,100,101,//34
    102,103,104,//35
    105,106,107,//36
    108,109,110,//37
    111,112,113,//38
    114,115,116,//39
    117,118,119,//40
    120,121,122,//41
    123,124,125,//42
    126,127,128,//43
    129,130,131,//44
    132,133,134,//45
    135,136,137,//46
    138,139,140,//47
    141,142,143,//48
    144,145,146,//49
    147,148,149,//50
    150,151,152,//51
    153,154,155,//52

    //carDoor

    156,157,158,//53
    156,158,159,//54
    156,159,160,//55
    156,160,161,//56
    162,163,164,//57
    162,164,165,//58
    162,165,166,//59
    162,166,167,//60
    162,167,168,//61

    169,170,171,//62
    169,171,172,//63
    169,172,173,//64
    169,173,174,//65
    175,176,177,//66
    175,177,178,//67
    175,178,179,//68
    175,179,180,//69
    175,180,181//70
  };
  float doorShade = 0.2f;
  GLfloat colors[] = {
    0.583f,  0.771f,  0.014f,
		0.609f,  0.115f,  0.436f,
		0.327f,  0.483f,  0.844f,  //1
		0.822f,  0.569f,  0.201f,
		0.435f,  0.602f,  0.223f,
		0.310f,  0.747f,  0.185f,  //2
		0.597f,  0.770f,  0.761f,
		0.559f,  0.436f,  0.730f,
		0.359f,  0.583f,  0.152f,  //3
		0.483f,  0.596f,  0.789f,
		0.559f,  0.861f,  0.639f,
		0.195f,  0.548f,  0.859f,  //4
		0.014f,  0.184f,  0.576f,
		0.771f,  0.328f,  0.970f,
		0.406f,  0.615f,  0.116f,  //5
		0.676f,  0.977f,  0.133f,
		0.971f,  0.572f,  0.833f,
		0.140f,  0.616f,  0.489f,  //6
		0.997f,  0.513f,  0.064f,
		0.945f,  0.719f,  0.592f,
		0.543f,  0.021f,  0.978f,  //7
		0.279f,  0.317f,  0.505f,
		0.167f,  0.620f,  0.077f,
		0.347f,  0.857f,  0.137f,  //8
		0.055f,  0.953f,  0.042f,
		0.714f,  0.505f,  0.345f,
		0.783f,  0.290f,  0.734f,  //9
		0.722f,  0.645f,  0.174f,
		0.302f,  0.455f,  0.848f,
		0.225f,  0.587f,  0.040f,  //10
		0.517f,  0.713f,  0.338f,
		0.053f,  0.959f,  0.120f,
		0.393f,  0.621f,  0.362f,  //11
		0.673f,  0.211f,  0.457f,
		0.820f,  0.883f,  0.371f,
		0.982f,  0.099f,  0.879f,  //13
    0.583f,  0.771f,  0.014f,
  	0.609f,  0.115f,  0.436f,
  	0.327f,  0.483f,  0.844f,  //14
  	0.822f,  0.569f,  0.201f,
  	0.435f,  0.602f,  0.223f,
  	0.310f,  0.747f,  0.185f,  //15
  	0.597f,  0.770f,  0.761f,
  	0.559f,  0.436f,  0.730f,
  	0.359f,  0.583f,  0.152f,  //16
  	0.483f,  0.596f,  0.789f,
  	0.559f,  0.861f,  0.639f,
  	0.195f,  0.548f,  0.859f,  //17
  	0.014f,  0.184f,  0.576f,
  	0.771f,  0.328f,  0.970f,
  	0.406f,  0.615f,  0.116f,  //18
  	0.676f,  0.977f,  0.133f,
  	0.971f,  0.572f,  0.833f,
  	0.140f,  0.616f,  0.489f,  //19
  	0.997f,  0.513f,  0.064f,
  	0.945f,  0.719f,  0.592f,
  	0.543f,  0.021f,  0.978f,  //20
  	0.279f,  0.317f,  0.505f,
  	0.167f,  0.620f,  0.077f,
  	0.347f,  0.857f,  0.137f,  //21
  	0.055f,  0.953f,  0.042f,
  	0.714f,  0.505f,  0.345f,
  	0.783f,  0.290f,  0.734f,  //22
  	0.722f,  0.645f,  0.174f,
  	0.302f,  0.455f,  0.848f,
  	0.225f,  0.587f,  0.040f,  //23
  	0.517f,  0.713f,  0.338f,
  	0.053f,  0.959f,  0.120f,
  	0.393f,  0.621f,  0.362f,  //24
  	0.673f,  0.211f,  0.457f,
  	0.820f,  0.883f,  0.371f,
  	0.982f,  0.099f,  0.879f,  //25
    0.583f,  0.771f,  0.014f,
    0.609f,  0.115f,  0.436f,
    0.327f,  0.483f,  0.844f,  //26
    0.822f,  0.569f,  0.201f,
    0.435f,  0.602f,  0.223f,
    0.310f,  0.747f,  0.185f,  //27
    0.597f,  0.770f,  0.761f,
    0.559f,  0.436f,  0.730f,
    0.359f,  0.583f,  0.152f,  //28
    0.483f,  0.596f,  0.789f,
    0.559f,  0.861f,  0.639f,
    0.195f,  0.548f,  0.859f,  //29
    0.014f,  0.184f,  0.576f,
    0.771f,  0.328f,  0.970f,
    0.406f,  0.615f,  0.116f,  //30
    0.676f,  0.977f,  0.133f,
    0.971f,  0.572f,  0.833f,
    0.140f,  0.616f,  0.489f,  //31
    0.997f,  0.513f,  0.064f,
    0.945f,  0.719f,  0.592f,
    0.543f,  0.021f,  0.978f,  //32
    0.279f,  0.317f,  0.505f,
    0.167f,  0.620f,  0.077f,
    0.347f,  0.857f,  0.137f,  //33
    0.055f,  0.953f,  0.042f,
    0.714f,  0.505f,  0.345f,
    0.783f,  0.290f,  0.734f,  //34
    0.722f,  0.645f,  0.174f,
    0.302f,  0.455f,  0.848f,
    0.225f,  0.587f,  0.040f,  //35
    0.517f,  0.713f,  0.338f,
    0.053f,  0.959f,  0.120f,
    0.393f,  0.621f,  0.362f,  //36
    0.673f,  0.211f,  0.457f,
    0.820f,  0.883f,  0.371f,
    0.982f,  0.099f,  0.879f,  //37
    0.583f,  0.771f,  0.014f,
  	0.609f,  0.115f,  0.436f,
  	0.327f,  0.483f,  0.844f,  //38
  	0.822f,  0.569f,  0.201f,
  	0.435f,  0.602f,  0.223f,
  	0.310f,  0.747f,  0.185f,  //39
  	0.597f,  0.770f,  0.761f,
  	0.559f,  0.436f,  0.730f,
  	0.359f,  0.583f,  0.152f,  //40
  	0.483f,  0.596f,  0.789f,
  	0.559f,  0.861f,  0.639f,
  	0.195f,  0.548f,  0.859f,  //41
  	0.014f,  0.184f,  0.576f,
  	0.771f,  0.328f,  0.970f,
  	0.406f,  0.615f,  0.116f,  //42
  	0.676f,  0.977f,  0.133f,
  	0.971f,  0.572f,  0.833f,
  	0.140f,  0.616f,  0.489f,  //43
  	0.997f,  0.513f,  0.064f,
  	0.945f,  0.719f,  0.592f,
  	0.543f,  0.021f,  0.978f,  //44
  	0.279f,  0.317f,  0.505f,
  	0.167f,  0.620f,  0.077f,
  	0.347f,  0.857f,  0.137f,  //45
  	0.055f,  0.953f,  0.042f,
  	0.714f,  0.505f,  0.345f,
  	0.783f,  0.290f,  0.734f,  //46
    0.722f,  0.645f,  0.174f,
  	0.302f,  0.455f,  0.848f,
    0.225f,  0.587f,  0.040f,  //47
  	0.517f,  0.713f,  0.338f,
  	0.053f,  0.959f,  0.120f,
  	0.393f,  0.621f,  0.362f,  //48
  	0.673f,  0.211f,  0.457f,
  	0.820f,  0.883f,  0.371f,
  	0.982f,  0.099f,  0.879f,  //49
    0.583f,  0.771f,  0.014f,
		0.609f,  0.115f,  0.436f,
		0.327f,  0.483f,  0.844f,  //50
		0.822f,  0.569f,  0.201f,
		0.435f,  0.602f,  0.223f,
  	0.982f,  0.099f,  0.879f,  //51
    0.583f,  0.771f,  0.014f,
		0.609f,  0.115f,  0.436f,
		0.327f,  0.483f,  0.844f,  //52
		0.822f,  0.569f,  0.201f,
		0.435f,  0.602f,  0.223f,
  	doorShade,doorShade,doorShade,  //53
  	doorShade,doorShade,doorShade,
  	doorShade,doorShade,doorShade,
  	doorShade,doorShade,doorShade,    //54
  	doorShade,doorShade,doorShade,
  	doorShade,doorShade,doorShade,
  	doorShade,doorShade,doorShade,    //55
  	doorShade,doorShade,doorShade,
  	doorShade,doorShade,doorShade,
  	doorShade,doorShade,doorShade,    //56
  	doorShade,doorShade,doorShade,
  	doorShade,doorShade,doorShade,
  	doorShade,doorShade,doorShade,//57
  	doorShade,doorShade,doorShade,
  	doorShade,doorShade,doorShade,
  	doorShade,doorShade,doorShade,//58
  	doorShade,doorShade,doorShade,
  	doorShade,doorShade,doorShade,
  	doorShade,doorShade,doorShade,    //59
  	doorShade,doorShade,doorShade,
  	doorShade,doorShade,doorShade,
  	doorShade,doorShade,doorShade,//60
  	doorShade,doorShade,doorShade,
  	doorShade,doorShade,doorShade,
  	doorShade,doorShade,doorShade,//61
  	doorShade,doorShade,doorShade,
  	doorShade,doorShade,doorShade,
  	doorShade,doorShade,doorShade,//62
  	doorShade,doorShade,doorShade,
  	doorShade,doorShade,doorShade,
  	doorShade,doorShade,doorShade,//63
  	doorShade,doorShade,doorShade,
  	doorShade,doorShade,doorShade,
  	doorShade,doorShade,doorShade,//64
  	doorShade,doorShade,doorShade,
  	doorShade,doorShade,doorShade,
  	doorShade,doorShade,doorShade,//65
  	doorShade,doorShade,doorShade,
  	doorShade,doorShade,doorShade,
  	doorShade,doorShade,doorShade,//66
  	doorShade,doorShade,doorShade,
  	doorShade,doorShade,doorShade,
  	doorShade,doorShade,doorShade,//67
  	doorShade,doorShade,doorShade,
  	doorShade,doorShade,doorShade,
  	doorShade,doorShade,doorShade,//68
  	doorShade,doorShade,doorShade,
  	doorShade,doorShade,doorShade,
  	doorShade,doorShade,doorShade,//69
  	doorShade,doorShade,doorShade,
  	doorShade,doorShade,doorShade,
  	doorShade,doorShade,doorShade,//70
  	doorShade,doorShade,doorShade,
  	doorShade,doorShade,doorShade,
  	doorShade,doorShade,doorShade,//71
  	doorShade,doorShade,doorShade,
  	doorShade,doorShade,doorShade
  };

  p.addPolygon(
      vertices,
      sizeof(vertices) / sizeof(GLfloat) / 3,
      elements,
      sizeof(elements) / sizeof(GLuint),
      colors);
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

	glfwWindowHint(GLFW_SAMPLES, 4);
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

	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	GLuint VertexArrayID;
  glGenVertexArrays(1, &VertexArrayID);
  glBindVertexArray(VertexArrayID);



  //////// Start coding here ////////
  int dimension[6] = {Polygon::POS_X, Polygon::POS_Y, Polygon::POS_Z, Polygon::COLOR_R, Polygon::COLOR_G, Polygon::COLOR_B};
  Polygon p(6, dimension);
  addCube(p);
  p.print();

  GLfloat* vertices = p.getArrays();
  unsigned int vertex_num = p.dataArray.size();
  GLuint* elements = p.getElements();
  unsigned int elements_num = p.elementArray.size();

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
  glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE,
                         6*sizeof(float), 0);

  GLint colAttrib = glGetAttribLocation(shaderProgram, "inColor");
  glEnableVertexAttribArray(colAttrib);
  glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE,
                         6*sizeof(float), (void*)(3*sizeof(float)));

  GLuint transformLoc = glGetUniformLocation(shaderProgram, "transform");

  // Get a handle for our "MVP" uniform
	GLuint MatrixID = glGetUniformLocation(shaderProgram, "MVP");

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
	// Camera matrix
	glm::mat4 View       = glm::lookAt(
								glm::vec3(4,3,-3), // Camera is at (4,3,-3), in World Space
								glm::vec3(0,0,0), // and looks at the origin
								glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
						   );
	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model      = glm::mat4(1.0f);
	// Our ModelViewProjection : multiplication of our 3 matrices
	glm::mat4 MVP        = Projection * View * Model; // Remember, matrix multiplication is the other way around

	do{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(shaderProgram);

		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

    //create transformation
    glm:mat4 transform, transform1, transform2;
    transform = glm::rotate(transform, 0.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));


		//This is for cube
		glDrawElements(GL_TRIANGLES, p.sizeArray[0], GL_UNSIGNED_INT, (void*)(p.offsetArray[0]*sizeof(GLuint)));

		//This is for car, not needed now
/*
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

*/

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
