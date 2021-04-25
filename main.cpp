#include "ENRICCamValve.h"
#include <iostream>

#include <fstream>
#include <streambuf>
#include <string>
#include <sstream>

using namespace std;

int main(){

    double rMin = 5;
    double rMax = 10;
    double lenValve = 15;
    double diamValve = 15;

    ENRICdevice * device = ENRICinitDevice (rMin, rMax, lenValve, diamValve);

    // Create and open a text file
    ofstream MyFile("CamValve.svg");
 
    // Write to the file
    MyFile << ENRICtoStringSVG(device);
 
    // Close the file
    MyFile.close();

return 0;
}