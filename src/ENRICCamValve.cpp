#include "ENRICCamValve.h"

ENRICdevice * ENRICinitDevice (double rMin, double rMax, double lenValve, double diamValve){
    
    ENRICdevice * device = new(nothrow) ENRICdevice;
    
    device->rMin = rMin;
    device->rMax = rMax;
    device->lenValve = lenValve;
    device->diamValve = diamValve;

    if(ENRICcheckIntegrity(device)){
        delete device;
        return NULL;
    }
    else return device;
};

int ENRICcheckIntegrity (const ENRICdevice * device){
    //Checking if all the measurs make sense (no negative lenghts)
    if (device->rMin <= 0) return 1;
    else if(device->rMax <= 0) return 1;
    else if (device->lenValve <= 0) return 1;
    else if (device->diamValve <= 0) return 1;

    //Checking if the parameters respect the construction constrain
    else if (device->rMax  <= device->rMin) return 2; //Cam constrain
    else if ((device->rMax - device->rMin) >= device->lenValve) return 3; //Constrain on the valve lift

    else return 0;
};

int ENRICdelete (ENRICdevice * device){
    if(device == NULL) return 1;
    else {
        delete device;
        return 0;
    }
}