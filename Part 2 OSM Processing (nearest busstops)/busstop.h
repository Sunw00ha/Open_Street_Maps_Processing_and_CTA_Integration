/*busstop.h*/

// Declaration of the BusStop class, representing individual bus stops in the system

// Irene Ha
// Northwestern University
// CS 211

// Original author: Prof. Joe Hummel

#pragma once

#include <string>
#include <vector>
#include <iostream>

using namespace std;



/* bus stop class

defines a model for a campus bus stop with a stop id, bus route, stop name, 
direction of travel, location of stop, and position in lattitude 
and longitude
*/

class BusStop {
public:
  int id;
  int busRoute;
  string stopName;
  string travelDirection;
  string stopLocation;
  // position is in lat and lon
  double lat;
  double lon;

  // default constructor
  BusStop() : id(0), busRoute(0), stopName(""), travelDirection(""), stopLocation(""), lat(0.0), lon(0.0) {}


  /* constructor
  This is the constructor for the BusStop class. 
  The constructor is responsible for initializing all 
  the data members of the class when you create a 
  BusStop object.
  */

  BusStop(int id, int busRoute, string stopName, string travelDirection, string stopLocation, double lat, double lon)
    : id(id), busRoute(busRoute), stopName(stopName), travelDirection(travelDirection), stopLocation(stopLocation), lat(lat), lon(lon) {}

/* 
function: print
Prints the details of a bus stop including its ID, name, route, location, 
and the calculated distance from a reference point.

parameters: distance
returns: none
*/
void print(double distance) const;


};