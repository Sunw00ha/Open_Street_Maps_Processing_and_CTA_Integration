/*busstops.cpp*/

// Implementation of the BusStops class, which manages a collection of bus stops

// Irene Ha
// Northwestern University
// CS 211

// Original author: Prof. Joe Hummel

#include "busstops.h"
#include "iostream"
#include "dist.h"
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>

BusStops::BusStops() {
    string filename = "bus-stops.txt"; //hardcode the file name
    readBusStopsFromFile(filename); 
}

/* 
Function: readBusStopsFromFile
Reads bus stop data from a specified file and stores each bus stop's information 
in the BusStops vector. 

Parameters: filename
Returns: none
*/
void BusStops::readBusStopsFromFile(const string& filename) {
    ifstream infile;

    // Open the bus stop data file and parse each line to extract bus stop details

    infile.open(filename); // open input file
    if (!infile.good()) {// if the file is not found
        cout << "Error: could not open file" << filename << endl;
        return;
    }

    string line;
    while(getline(infile, line)) { //read a line from the input file

        if (infile.fail())
            break;

        stringstream parser(line); // setup to parse the line

        string id_str;
        string route_str;
        string stopName;
        string direction;
        string location;
        string lat_str;
        string lon_str;
        
        // extract each value
        getline(parser, id_str, ',');
        getline(parser, route_str, ',');
        getline(parser, stopName, ',');
        getline(parser, direction, ',');
        getline(parser, location, ',');
        getline(parser, lat_str, ',');
        getline(parser, lon_str, ',');

        //convert strign to appropriate data types
        int id = stoi(id_str);
        int route = std::stoi(route_str);
        double lat = std::stod(lat_str);
        double lon = std::stod(lon_str);

        //make a BusStop object and add it to the stops vector

        BusStop busStopObject(id, route, stopName, direction, location, lat, lon);
        stops.push_back(busStopObject);

        // // DEBUG: this line is added to check if stops are loaded
        // cout << "Loaded bus stop: " << stopName << endl;
    }

    infile.close(); //close the file when done

}


/* 
function: print
Prints all the bus stops stored in the BusStops class, ordered by ID.
paramter: none
return: none
*/
void BusStops::print()  const{
    // sort the bus stops by ID
    vector<BusStop> sortedStopsVector = stops; // copy the currently unsorted stops vector
    sort(sortedStopsVector.begin(), sortedStopsVector.end(),
        [](const BusStop& s1, const BusStop& s2) {return s1.id < s2.id;}); // sort by stop id

    //print the bus stops
    for (const BusStop& stop : sortedStopsVector) {
        cout << stop.id << ": bus " << stop.busRoute << ", " << stop.stopName << ", " 
             << stop.travelDirection << ", " << stop.stopLocation << ", location (" 
             << stop.lat << ", " << stop.lon << ")" << endl;
    }
}



/* 
function: findClosetStops
new method for finding closest stops
paramter: lat and lon
return: pair<BusStop, BusStop>
*/
pair<BusStop, BusStop> BusStops::findClosestStops(double lat, double lon) const {
    // Initialize distances and closest stops
    double initialSBdistance = 1.0 / 0.0;
    double initialNBdistance = 1.0 / 0.0;

    BusStop closestSB;
    BusStop closestNB;
    
    for (const BusStop& s : stops) {
        // set distance equal to using the distBetween2Points(double lat1, double lon1, double lat2, double lon2) function
        double distance = distBetween2Points(lat, lon, s.lat, s.lon);
        
        //check if bus stop is SB
        if (s.travelDirection == "Southbound") {
            if (distance < initialSBdistance) {
                initialSBdistance = distance;
                closestSB = s;
            }
        }

        //check if the bus stop is NB
        if (s.travelDirection == "Northbound") {
            if (distance < initialNBdistance) {
                initialNBdistance = distance;
                closestNB = s;
            }
        }
    }

    // return a pair of closest SB and NB
    return make_pair(closestSB, closestNB);

}


/*
function: getNumBusStops
    Returns the total number of bus stops stored in the BusStops class.
    parameters: none
    returns: int
*/
int BusStops::getNumBusStops() {
  return (int) this->stops.size();
}