#ifndef ENGINE
#define ENGINE

#include "ENRICCamValve.h"
#include "Gear.h"

#include <vector>       //variable lenght vector
#include <fstream>      //file
#include <streambuf>    //file
#include <sstream>      //file
#include <cstdio>
#include <cstdlib>
#include <iostream>

#include <iostream>
#include <math.h>
#include <new>
#include <string>

#ifndef PI
#define PI 3.14159265
#endif

using namespace std;

typedef struct ENRICdistribution{
    ENRICdevice * cam;
    Gear * gearCenter, * gearLeft, * gearRight;
} ENRICdistribution;

typedef struct ENRICengine{
    int n; //number of cams of the engine
    ENRICdistribution ** distributions;
} ENRICengine;

typedef struct ENRICcmdlineRet{
    ENRICdevice * device;
    ENRICdistribution * distribution;
    ENRICengine * engine;
} ENRICcmdlineRet;


/**
 * Manage the params red by command line
 * @param argc number of params passed
 * @param argv array where the params are stored as char arrays
 * @return pointer to struct created following commands
 *      NULL if error occurs or no creation is requested
*/
ENRICcmdlineRet * ENRICcommandLineParam(int argc, char** argv);

/**
 * Given the engine struct, set the offset for each distribution
 * @param engine struct to be modified
 * @return @return 0 if the function succeed;
 *      1 if error occures
 */
int ENRICsetOffsets(ENRICengine * engine);

/**
 * ALLOCATE an ENRICdistribution structure.
 * @param reference_radius radius of the gear
 * @param axle_radius radius of the axle of the gear
 * @param teeth number of teeth of the gear
 * @return pointer to initialized distribution structure;
*/
ENRICdistribution * ENRICinitDistribution (double reference_radius, double axle_radius, int teeth);

/**
 * ALLOCATE an ENRICengine structure.
 * It checks if the parameters follow the constraints given to the device
 * If the parameters violets the constraints, the structure is DEALLOCATED.
 * @param n number of distributions of the engine
*/
ENRICengine * ENRICinitEngine (const int n);

/**
 * DEALLOCATE the structure pointed by the given pointer
 * @param distribution pointer to structure to be deallocated
 * @return 0 if the function succeed;
 *      1 if error occures
*/
int ENRICdeleteDistribution(ENRICengine * distribution);

/**
 * DEALLOCATE the structure pointed by the given pointer
 * @param engine pointer to structure to be deallocated
 * @return 0 if the function succeed;
 *      1 if error occures
*/
int ENRICdeleteEngine(ENRICengine * engine);

/**
 * Modify n of the struct pointed by the given pointer
 * @param engine pointer to structure to be modified
 * @param n new value
 * @return 0 if the function succeed;
 *      1 if error occures, and keeps the original value
 */
int ENRICsetengineN(ENRICengine * engine, const int n);

/**
 * Compare two engine structes ignoring angle
 * @param a first struct to compare
 * @param b second struct to compare
 * @return true if the structs have the same values
 *      false otherways (also if one pointer is NULL)
 */
bool ENRICengineCompare(ENRICengine * a, ENRICengine * b);

/**
 * Create an SVG string to represent the distribution
 * @param distribution pointer to structure to be represented
 * @param cxShaft x coordinate of the shaft's axis within the drawing area
 * @param cyShaft y coordinate of the shaft's axis within the drawing area
 * @param quote flag: if true quotes the distribution (default false)
 * @param header flag: if true add the SVG header (default false)
 * @return string distributionSVG;
 *      EMPTY if error occures
*/
string ENRICdistributionToStringSVG (ENRICdistribution * distribution, bool quote = false);

/**
 * Create an SVG string to represent the engine
 * @param engine pointer to structure to be represented
 * @param quote flag: if true quotes the engine (default false)
 * @param header flag: if true add the SVG header (default true)
 * @return string engineSVG;
 *      EMPTY if error occures
*/
string ENRICengineToStringSVG(ENRICengine * engine, bool quote = false, bool header = true);

/**
 * Read an SVG string and return the engine associated to the drawing
 * @param s string to be analized, must have the same format of the one created by ENRICengineToStringSVG
 * @return pointer to device device if the function succeed;
 *      NULL if error occures
 */
ENRICengine * ENRICengineFromStringSVG(string s);

#endif