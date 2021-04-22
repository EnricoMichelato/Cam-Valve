#include "ENRICCamValve.h"
#include <iostream>
using namespace std;

int main(){

    double rMin = 5;
    double rMax = 10;
    double lenValve = 15;
    double diamValve = 15;

    ENRICdevice * device = ENRICinitDevice (rMin, rMax, lenValve, diamValve);


return 0;
}