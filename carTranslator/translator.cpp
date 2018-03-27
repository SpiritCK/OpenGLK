#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;
string inputName = "carBody";
string outputName = "output";

float winHeight=712;
float winWidth=1024;
float magicNumber=271;


int main(){
  ifstream inFile ("carBody");
  ofstream outFile("outputName");

  string buff;
  float currentX=0;
  float currentY=0;
  while(!inFile.eof()){
    inFile >> buff;
    if(buff.find(",") !=-1){
      string posX = buff.substr(0,buff.find(","));
      string posY = buff.substr(buff.find(",")+1);
      currentX += std::strtod(posX.c_str(),0);
      currentY += std::strtod(posY.c_str(),0);
      /*
      float convertedX = ((currentX*winWidth/magicNumber)*2/winWidth)-1;
      float convertedY = ((currentY*winWidth/magicNumber)*2/winHeight)-1;
      */
      float convertedX = (currentX*2/magicNumber);
      float convertedY = (currentY*2/magicNumber);
      cout << "       " << convertedX*100 << ", " << convertedY*100 << ",\n";
    }
    else{
      cout << buff << "\n";
      currentX=0;
      currentY=0;
    }
  }

}
