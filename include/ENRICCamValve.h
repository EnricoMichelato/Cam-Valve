#ifndef CAMVALVE
#define CAMVALVE

#include <iostream>
#include <math.h>
#include <new>
#include <string.h>

using namespace std;

typedef struct ENRICdevice{
    double rMin; //Minimum cam radius
    double rMax; //Maximum cam radius
    double lenValve; //Valve length
    double diamValve; //Valve diameter
    } ENRICdevice;

/**
 * Dinamically allocates a ENRICdevice struct.
 * @param rMin; //Minimum cam radius
 * @param rMax; //Maximum cam radius
 * @param lenValve; //Valve length
 * @param diamValve; //Valve diameter
 * 
 * 
 * Checks if the parameters allow the device to be assemblated
 * If the parameters don't allow the device to be assemblated, the pointer will be deallocated
 * @return pointer to device
*/
ENRICdevice * ENRICinitDevice (double rMin, double rMax, double lenValve, double diamValve);
/**
 * Checks if the parameters allow the device to be built
 * @param device pointer to device
 * @return 0 if the integrity is respected
 * @return 1 in case of error
*/
int ENRICcheckIntegrity (const ENRICdevice * device);

/**
 * Deallocates the structure pointed by device
 * @param device pointer to the struct that has to be deallocated
 * @return 0 if the checking process was succesfull
 * @return 1 in case of error
*/
int ENRICdelete (ENRICdevice * device);

#endif