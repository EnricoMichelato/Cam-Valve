#include "ENRICCamValve.h"
#include "ENRICengine.h"
#include "Gear.h"

#include <iostream>

#include <fstream>
#include <streambuf>
#include <string>
#include <sstream>

#ifndef PI
#define PI 3.14159265
#endif

using namespace std;

int main(int argc, char ** argv){

    //ENRICcommandLineParam(argc, argv);

    double rMin = 50;
    double rMax = 70;
    double lenValve = 200;
    double diamValve = 80;
    double Alpha = 0*PI;
    double Gamma = PI / 8;

    double axle_radius = rMin;
    double reference_radius = rMax;
    double teeth = 30;
    
    ENRICdevice * device = ENRICinitDevice (rMin, rMax, lenValve, diamValve, Alpha, Gamma);

    ENRICdistribution * distribution = ENRICinitDistribution(reference_radius, axle_radius, teeth);

    //Gear * gear = g_init(true, reference_radius, axle_radius, teeth);

    //ENRICsaveToFile(g_to_svg(gear), "Gear.svg");

    //ENRICdistributionToStringSVG(distribution, "Connection.svg");

    ENRICsaveToFile(ENRICtoStringSVG(device, true, true), "CamValveQuote.svg");

    //ENRICsaveToFile(ENRICAnimationtoStringSVG(device), "CamValveAnimation.svg");

    //ENRICsaveToFile(ENRICdistributionToStringSVG(distribution, false, true), "Distribution.svg");  

return 0;
}