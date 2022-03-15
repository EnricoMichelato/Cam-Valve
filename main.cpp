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

    ENRICcommandLineParam(argc, argv);

    double rMin = 50;
    double rMax = 70;
    double lenValve = 200;
    double diamValve = 80;
    double Alpha = 0*PI;
    double Gamma = PI / 8;

    double axle_radius = rMin;
    double reference_radius = rMax*2;
    double teeth = 30;
    

    ENRICdevice * device = ENRICinitDevice (rMin, rMax, lenValve, diamValve, Alpha, Gamma);

    ENRICdistribution * distribution = ENRICinitDistribution(reference_radius, axle_radius, teeth);

    ENRICsaveToFile(ENRICtoStringSVG(device, true), "CamValveOriginal.svg");

    ENRICsaveToFile(g_to_svg(distribution->gearCenter, false, false, 60), "GearProva.svg");

    ENRICsaveToFile(ENRICAnimationtoStringSVG(device, true), "CamValveAnimation.svg");

    ENRICsaveToFile(ENRICdistributionToStringSVG(distribution, false), "Distribution.svg");   

return 0;
}