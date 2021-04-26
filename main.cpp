#include "ENRICCamValve.h"
#include <iostream>

#include <fstream>
#include <streambuf>
#include <string>
#include <sstream>

#ifndef PI
#define PI 3.14159265
#endif

using namespace std;

int main(){

    double rMin = 50;
    double rMax = 75;
    double lenValve = 200;
    double diamValve = 80;
    double Alpha = 0;
    double Gamma = PI / 8;

    ENRICdevice * device = ENRICinitDevice (rMin, rMax, lenValve, diamValve, Alpha, Gamma);

    // Create and open a text file
    ofstream MyFile("CamValve.svg");
 
    // Write to the file
    MyFile << ENRICtoStringSVG(device, true);
 
    // Close the file
    MyFile.close();

return 0;
}