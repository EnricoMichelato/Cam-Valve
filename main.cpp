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

    double rMin = 25;
    double rMax = 35;
    double lenValve = 100;
    double diamValve = 40;
    double Alpha = 0*PI;
    double Gamma = PI / 8;
    int n = 3;

    double axle_radius = rMin;
    double reference_radius = 1.5*rMax;
    double teeth = 30;

    double cxShaft = 1.2*reference_radius;
    double cyShaft = 1.2*reference_radius;

    
    ENRICdevice * device = ENRICinitDevice (rMin, rMax, lenValve, diamValve, Alpha, Gamma);

    ENRICdistribution * distribution = ENRICinitDistribution(reference_radius, axle_radius, teeth);

    ENRICengine * engine = ENRICinitEngine(n, reference_radius, axle_radius, teeth);

    ENRICsaveToFile(ENRICdistributionToStringSVG(engine->distributions[1], cxShaft, cyShaft, false, true), "Connection.svg");

    ENRICsaveToFile(ENRICengineToStringSVG(engine, cyShaft), "Engine.svg");

    //Gear * gear = g_init(true, reference_radius, axle_radius, teeth);
    //ENRICsaveToFile(g_to_svg(gear), "Gear.svg");
    //ENRICsaveToFile(ENRICtoStringSVG(device, true, true), "CamValveQuote.svg");
    //ENRICsaveToFile(ENRICAnimationtoStringSVG(device), "CamValveAnimation.svg");
    //ENRICsaveToFile(ENRICdistributionToStringSVG(distribution, false, true), "Distribution.svg"); 

return 0;
}