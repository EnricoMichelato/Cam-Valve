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
    double rMax = 65;
    double lenValve = 200;
    double diamValve = 80;
    double Alpha = 0*PI;
    double Gamma = PI / 8;
    

    ENRICdevice * device = ENRICinitDevice (rMin, rMax, lenValve, diamValve, Alpha, Gamma);

    ENRICsaveToFile(ENRICtoStringSVG(device, true), "CamValveOriginal.svg");

    ENRICsaveToFile(ENRICloadFromFile("CamValveOriginal.svg"), "CamValveProve.svg");

    ENRICsaveToFile(ENRICAnimationtoStringSVG(device, true), "CamValveAnimation.svg");

return 0;
}