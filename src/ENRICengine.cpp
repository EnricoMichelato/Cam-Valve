#include "ENRICengine.h"

ENRICdistribution * ENRICinitDistribution(double reference_radius, double axle_radius, int teeth){

    ENRICdistribution * ret = new ENRICdistribution;

    double rMin = axle_radius;
    double rMax = axle_radius*9/7;
    double diamValve = rMax;
    double lenValve = rMax*2;
    double Alpha = 0 * PI;
    double Gamma = PI /8;

    ret->cam = ENRICinitDevice (rMin, rMax, lenValve, diamValve, Alpha, Gamma);
    ret->gearCenter = g_init(true, reference_radius, axle_radius, teeth, 20);
    ret->gearLeft = g_init_for_connection(ret->gearCenter, true, reference_radius, axle_radius);
    ret->gearRight = g_init_for_connection(ret->gearLeft, true, reference_radius, axle_radius);

    if (ret->gearCenter == NULL || ret->gearLeft == NULL) {
     cout << "Gear is null" << endl;
        return 0;
    }

    return ret;
}

ENRICengine * ENRICinitEngine(const int n, double reference_radius, double axle_radius, int teeth){

    ENRICengine * ret = new ENRICengine;
    
    ret->n = n;
    
    ret->distributions = new ENRICdistribution* [n];
    for(int i=0; i<ret->n; i++){
        ret->distributions[i] = ENRICinitDistribution(reference_radius, axle_radius, teeth);
    }

    return ret;
}

string ENRICdistributionToStringSVG(ENRICdistribution * distribution, double cxShaft, double cyShaft, bool quote, bool header){

    if(distribution == NULL) return "";

    string distributionSVG = "";

    distributionSVG += ENRICtoStringSVG(distribution->cam, cxShaft, cyShaft, false, false);

    Connection* conn = g_init_connection(distribution->gearCenter, distribution->gearLeft, 0);

    Connection* conn2 = g_init_connection(distribution->gearLeft, distribution->gearRight, 0);

    g_set_next_connection(&conn, conn2);
    

    distributionSVG += "\n" + g_tostring_connection(conn, cxShaft, cyShaft);

    if(header){
        distributionSVG = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n\n"
        "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"800\" height=\"600\" >\n\n" + distributionSVG + "</svg>\n";
    
    }

    return distributionSVG;

}

ENRICcmdlineRet * ENRICcommandLineParam(int argc, char** argv){ 

    ENRICcmdlineRet * ret = new ENRICcmdlineRet;
    ret->device = NULL;
    ret->engine = NULL;

    string sargv[argc];
    for(int i=0;i<argc;i++) sargv[i] = string(argv[i]);
    // ./mainentry -device/engine -i /path_da_cui_importare -eq cx cy /path_dove_esportare -p <param>*6
    if(argc == 1) return NULL; //no params

    if(sargv[1] == "-h"){//help
        string help =   "--HELP\n"
                        "Command format: ./mainentry -\"struct\" -i importPath -e/-eq/-ea (n T) cxShaft cyShaft exportPath -p params...\n"
                        "-\"struct\" must be device or distribution: define which one"
                        "-i import a struct from the file with path importPath\n"
                        "-e export a struct (-eq export with quotes, -ea export animated) on the file with path exportPath.\n"
                        "   The struct is taken from:\n"
                        "       an imported file called with the option -i (prioritized action)\n"
                        "       the one created with the params passed after the option -p (ignoerd if -i is called)\n"
                        "   cxShaft cyShaft are the coordinates of the shaft's center on the SVG draw, needed only with device\n"
                        "-eq export a struct with quotes on the file with path exportPath (options as before)\n"
                        "-ea export a struct animated on the file with path exportPath\n"
                        "-p followed by the params of the struct to be exported (can't be called if -e or -eq isn't called before)\n"
                        "   Params: rMin, rMax, lenValve, diamValve, Alpha, Gamma for device \n"
                        "           reference_radius, axle_radius, teeth for distribution\n";
        cout << help << endl;
        return NULL;
    }

    else if(sargv[1] == "-device"){//device
    // ./mainentry -device -i /path_da_cui_importare -eq /path_dove_esportare -p <param>*6
        if(argc >= 4){
            if(sargv[2] == "-i"){ //import
                cout << "DEBUG: Importing device from " << sargv[3] << endl;
                string file = ENRICloadFromFile(sargv[3]);
                if(file == "") { //file not found
                    cout << "DEBUG: File not found" << endl;
                    return NULL;
                } 

                //ret->device = ENRICdeviceFromStringSVG(file);

                if(ret->device == NULL) {  //string isn't a device
                    cout << "DEBUG: Can't import device from file " << sargv[3] <<", wrong format" << endl;
                    return NULL;
                }
                cout << "DEBUG: Import successful" << endl;

                if(argc >= 8){ //requested import + export
                    if(sargv[4] == "-e"){ //export
                        cout << "DEBUG: Exporting device on file " << sargv[7] << endl;
                        ENRICsaveToFile(ENRICtoStringSVG(ret->device, stod(sargv[5]), stod(sargv[6])), sargv[7]);
                    }
                    else if(sargv[4] == "-eq"){ //export with quotes
                        cout << "DEBUG: Exporting device with quotes on file " << sargv[7] << endl;
                        ENRICsaveToFile(ENRICtoStringSVG(ret->device, stod(sargv[5]), stod(sargv[6]), true), sargv[7]);
                    }
                    else if(sargv[4] == "-ea" && argc >= 10){ //export animated
                        cout << "DEBUG: Exporting device animated on file " << sargv[9] << endl;
                        ENRICsaveToFile(ENRICAnimationtoStringSVG(ret->device), sargv[7]);
                    }
                    cout << "DEBUG: Export successful" << endl;
                }
                else if(argc >= 5 && (sargv[4] == "-e" || sargv[4] == "-eq" || sargv[4] == "-ea")){ //more than 4 arguments but not enough to export
                    cout << "DEBUG: Missing arguments for export" << endl;
                }

                return ret;
            }

            else if(argc >= 13){// only export with params
            // ./mainentry -device -i /path_da_cui_importare -eq /path_dove_esportare -p <param>*6
                if(sargv[2] == "-e" || sargv[2] == "-eq"){ 
                    cout << "DEBUG: Exporting device with params on file " << sargv[5] << endl;
                    if(sargv[6] != "-p"){ //params not found
                        cout << "DEBUG: Params not found or wrong syntax" << endl;
                        return NULL;
                    } 

                    if(argc == 13) ret->device = ENRICinitDevice(stod(sargv[5]), stod(sargv[6]), stod(sargv[7]), stod(sargv[8]), stod(sargv[9]), stod(sargv[10]));

                    if(ret->device == NULL) { //params don't match constraints
                        cout << "DEBUG: Unable to init device with the given params, see README and check the constraints" << endl;
                        return NULL;
                    } 
                    if(sargv[2] == "-e") ENRICsaveToFile(ENRICtoStringSVG(ret->device, stod(sargv[3]), stod(sargv[4])), sargv[5]);
                    else if(sargv[2] == "-eq") ENRICsaveToFile(ENRICtoStringSVG(ret->device, stod(sargv[3]), stod(sargv[4]), true), sargv[5]);

                    cout << "DEBUG: Export successful" << endl;
                    
                    return ret;
                }
                // ./mainentry -device -i /path_da_cui_importare -eq cX cY/path_dove_esportare -p <param>*6
                else if(sargv[2] == "-ea"){
                    cout << "DEBUG: Exporting device animated with params on file " << sargv[7] << endl;
                    if(sargv[8] != "-p"){ //params not found
                        cout << "DEBUG: Params not found or wrong syntax" << endl;
                        return NULL;
                    } 
                    if(argc == 14) ret->device = ENRICinitDevice(stod(sargv[9]), stod(sargv[10]), stod(sargv[11]), stod(sargv[12]), stod(sargv[13]), stod(sargv[14]));

                    if(ret->device == NULL) { //params don't match constraints
                        cout << "DEBUG: Unable to init device with the given params, see README and check the constraints" << endl;
                        return NULL;
                    }
                    
                    ENRICsaveToFile(ENRICAnimationtoStringSVG(ret->device), sargv[3]);
                    cout << "DEBUG: Export successful" << endl;

                    return ret;
                }
            }
        }
    }

    else if(sargv[1] == "-distribution"){//distribution
    // ./mainentry -distribution -i /path_da_cui_importare -eq/ea cx cy /path_dove_esportare -p <param>*3
        if(argc >= 4){
            if(sargv[2] == "-i"){ //import
                cout << "DEBUG: Importing distribution from " << sargv[3] << endl;
                string file = ENRICloadFromFile(sargv[3]);
                if(file == "") { //file not found
                    cout << "DEBUG: File not found" << endl;
                    return NULL;
                } 

                //ret->distribution = ENRICdistributionFromStringSVG(file);

                if(ret->distribution == NULL) {  //string isn't a distribution
                    cout << "DEBUG: Can't import distribution from file " << sargv[3] <<", wrong format" << endl;
                    return NULL;
                }
                cout << "DEBUG: Import successful" << endl;

    // ./mainentry -distribution -i /path_da_cui_importare -eq/ea cx cy /path_dove_esportare -p <param>*3

                if(argc >= 8){ //requested export
                    if(sargv[4] == "-e"){ //export
                        cout << "DEBUG: Exporting distribution on file " << sargv[7] << endl;
                        ENRICsaveToFile(ENRICdistributionToStringSVG(ret->distribution, stod(sargv[5]), stod(sargv[6]), false, true), sargv[5]);
                    }
                    else if(sargv[4] == "-eq"){ //export with quotes
                        cout << "DEBUG: Exporting distribution with quotes on file " << sargv[7] << endl;
                        ENRICsaveToFile(ENRICdistributionToStringSVG(ret->distribution, stod(sargv[5]), stod(sargv[6]), true, true), sargv[5]);
                    }
                    cout << "DEBUG: Export successful" << endl;
                }
                else if(argc >= 5 && (sargv[4] == "-e" || sargv[4] == "-eq" || sargv[4] == "-ea")){ //more than 4 arguments but not enough to export
                    cout << "DEBUG: Missing arguments for export" << endl;
                }
                return ret;
            }

            // ./mainentry -distribution -i /path_da_cui_importare -eq/ea cx cy /path_dove_esportare -p <param>*3
            else if(argc >= 8){
                if(sargv[2] == "-e" || sargv[2] == "-eq"){ //export with params
                    cout << "DEBUG: Exporting distribution with params on file " << sargv[3] << endl;
                    if(sargv[4] != "-p"){ //params not found
                        cout << "DEBUG: Params not found" << endl;
                        return NULL;
                    } 

                    if(argc == 8) ret->distribution = ENRICinitDistribution(stoi(sargv[5]), stod(sargv[6]), stod(sargv[7]));

                    if(ret->distribution == NULL) { //params don't match constraints
                        cout << "DEBUG: Unable to init distribution with the given params, see README and check the constraints" << endl;
                        return NULL;
                    } 
                    if(sargv[2] == "-e") ENRICsaveToFile(ENRICdistributionToStringSVG(ret->distribution, stod(sargv[6]), stod(sargv[7]), false, true), sargv[5]);
                    else ENRICsaveToFile(ENRICdistributionToStringSVG(ret->distribution, stod(sargv[6]), stod(sargv[7]), true, true), sargv[5]);
                    cout << "DEBUG: Export successful" << endl;
                    
                    return ret;
                }
            }
        }
    }
    return NULL;
}

string ENRICengineToStringSVG(ENRICengine * engine, double cyShaft){
    if(engine == NULL) return "";

    string engineSVG = "";

    for(int i=0; i<engine->n; i++){

        double cxShaft = (1.2 + 4*i)*g_get_reference_radius(engine->distributions[i]->gearCenter);

        engineSVG += ENRICdistributionToStringSVG(engine->distributions[1], cxShaft, cyShaft, false, false);

    }

    engineSVG = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n\n"
    "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"800\" height=\"600\" >\n\n" + engineSVG + "</svg>\n";
    
    return engineSVG;
}
