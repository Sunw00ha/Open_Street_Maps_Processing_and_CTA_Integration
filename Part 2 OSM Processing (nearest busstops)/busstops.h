/*busstops.h*/

// This file defines the BusStops class, which represents a collection of bus stops

// Irene Ha
// Northwestern University
// CS 211

// Original author: Prof. Joe Hummel

#pragma once
#include "busstop.h"

#include <string>
#include <vector>
#include <iostream>

using namespace std;



/* bus stops COME BACK

stores all the bus stops
*/

class BusStops {
public:
    vector<BusStop> stops; //this class is just a vector of busstop objects

    // constructor
    // this is needed because we want to load the bus stops from a file 
    // automatically when the object is created, so we need a consturctor 
    // to handle this initialization
    BusStops();

    /* 
    Function: readBusStopsFromFile
    Reads bus stop data from a specified file and stores each bus stop's information 
    in the BusStops vector. 
    
    Parameters: filename
    Returns: none
    */
    void readBusStopsFromFile(const string& filename);

    /* 
    function: print
    Prints all the bus stops stored in the BusStops class, ordered by ID.
    paramter: none
    return: none
    */
    void print() const;


    /* 
    function: findClosetStops
    new method for finding closest stops
    paramter: lat and lon
    return: pair<BusStop, BusStop>
    */
    pair<BusStop, BusStop> findClosestStops(double lat, double lon) const;

    /* 
    function: getNumBusStops
    Returns the total number of bus stops stored in the BusStops class.
    parameters: none
    returns: int
    */
   int getNumBusStops();
};