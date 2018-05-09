#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <cstring>

using namespace std;

int main(int argc, char** argv) {

  if (argc != 2) {
    printf("How large will you resize?\n");
    exit(1);
  }
  
  int size = atoi(argv[1]);
  
	while( 1 ){

		char lineHeader[128];
		// read the first word of the line
		int res = scanf("%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

		// else : parse lineHeader
		
		if ( strcmp( lineHeader, "v" ) == 0 ){
			float x, y, z;
			scanf("%f %f %f\n", &x, &y, &z );
			x /= size;
			y /= size;
			z /= size;
			printf("v  %.4f %.4f %.4f\n", x, z - 0.3, -y);
		} else {
		  string temp;
		  getline(cin, temp);
		  printf("%s ", lineHeader);
		  cout << temp << endl;
		}
		/*else if ( strcmp( lineHeader, "vt" ) == 0 ){
		  float x, y;
			scanf("%f %f\n", &x, &y );
			printf("vt %f %f
		}else if ( strcmp( lineHeader, "vn" ) == 0 ){
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
			temp_normals.push_back(normal);
		}else if ( strcmp( lineHeader, "f" ) == 0 ){
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[4], uvIndex[4], normalIndex[4];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2], &vertexIndex[3], &uvIndex[3], &normalIndex[3] );
			if (matches == 9) {
			  vertexIndices.push_back(vertexIndex[0]);
			  vertexIndices.push_back(vertexIndex[1]);
			  vertexIndices.push_back(vertexIndex[2]);
			  uvIndices    .push_back(uvIndex[0]);
			  uvIndices    .push_back(uvIndex[1]);
			  uvIndices    .push_back(uvIndex[2]);
			  normalIndices.push_back(normalIndex[0]);
			  normalIndices.push_back(normalIndex[1]);
			  normalIndices.push_back(normalIndex[2]);
			}
			else if (matches == 12) {
			  vertexIndices.push_back(vertexIndex[0]);
			  vertexIndices.push_back(vertexIndex[1]);
			  vertexIndices.push_back(vertexIndex[2]);
			  uvIndices    .push_back(uvIndex[0]);
			  uvIndices    .push_back(uvIndex[1]);
			  uvIndices    .push_back(uvIndex[2]);
			  normalIndices.push_back(normalIndex[0]);
			  normalIndices.push_back(normalIndex[1]);
			  normalIndices.push_back(normalIndex[2]);
			  
			  vertexIndices.push_back(vertexIndex[2]);
			  vertexIndices.push_back(vertexIndex[3]);
			  vertexIndices.push_back(vertexIndex[0]);
			  uvIndices    .push_back(uvIndex[2]);
			  uvIndices    .push_back(uvIndex[3]);
			  uvIndices    .push_back(uvIndex[0]);
			  normalIndices.push_back(normalIndex[2]);
			  normalIndices.push_back(normalIndex[3]);
			  normalIndices.push_back(normalIndex[0]);
			}
		}else{
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}*/

	}
	return 0;
}
