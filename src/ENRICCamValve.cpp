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

int ENRICsetrMin (ENRICdevice * device, double newrMin){
    double var = device->rMin;
    device->rMin = newrMin;
    
    if(ENRICcheckIntegrity(device)){
        device->rMin = var;
        return 1;
    }
    else return 0;
};

int ENRICsetrMax (ENRICdevice * device, double newrMax){
    double var = device->rMax;
    device->rMax = newrMax;
    
    if(ENRICcheckIntegrity(device)){
        device->rMax = var;
        return 1;
    }
    else return 0;
};

int ENRICsetlenValve (ENRICdevice * device, double newlenValve){
    double var = device->lenValve;
    device->lenValve = newlenValve;
    
    if(ENRICcheckIntegrity(device)){
        device->lenValve = var;
        return 1;
    }
    else return 0;
};

int ENRICdelete (ENRICdevice * device){
    if(device == NULL) return 1;
    else {
        delete device;
        return 0;
    }
}


string ENRICtoStringSVG (ENRICdevice * device){
    string deviceSVG = "";
    double xCam, yCam; //cooridnates center of rotation (first circle of the cam)
    double x2Cam, y2Cam; //coordinates second circle of the cam
    double r1, r2;  //radius of the two circles componing the cam
    double LEN = device->lenValve; //length of the valve
    double DIAM = device->diamValve;  // diameter of the valve

    //Defining parameters
    xCam = 100;
    yCam = 225;
    x2Cam = 70;
    y2Cam = 200;
    r1 = 25;
    r2 = 10;
    LEN = 100;
    DIAM = 20;

    //Building the cam
        //First circle of the cam
    deviceSVG += "\t<circle cx=\"" + to_string(xCam) + "\" cy=\"" + to_string(yCam) + "\" "; // defining the starting point
    deviceSVG += "r=\"" + to_string(r1) +"\" style=\"fill:grey\" />\n\n"; //defining radius and colour
        //Second circle of the cam
    deviceSVG += "\t<circle cx=\"" + to_string(x2Cam) + "\" =\"" + to_string(y2Cam) + "\" "; // defining the starting point
    deviceSVG += "r=\"" + to_string(r2) +"\" style=\"fill:grey\" />\n\n"; //defining radius and colour
        //Connecting the two circles with a rectangle
    

    //Valve
        //First rectangle componing the valve
    deviceSVG += "\t<rect x=\"" + to_string(xCam) + "\" y=\"" + to_string(yCam - LEN) + "\" "; //defining the starting point
    deviceSVG += "width=\"" + to_string(r1/3) + "\" height\"" + to_string(LEN) + "\" "; //defining dimension
    deviceSVG += "style=\"fill:red\" />\n\n"; //defining colour
        //Second rectangle componing the valve
    deviceSVG += "\t<rect x=\"" + to_string(xCam) + "\" y=\"" + to_string(yCam - LEN) + "\" "; //defining the starting point
    deviceSVG += "width=\"" + to_string(DIAM) + "\" height\"" + to_string(r1/3) + "\" "; //defining dimension
    deviceSVG += "style=\"fill:red\" />\n\n"; //defining colour

    //defining file e sheet dimension
    deviceSVG = "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"200\" height=\"200\" >\n\n" + deviceSVG;
    deviceSVG = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n\n" + deviceSVG;
    deviceSVG += "</svg>\n";


    
    return deviceSVG;
};
