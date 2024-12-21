/*building.h*/

//
// A building in the Open Street Map.
// 
// Irene Ha
// Northwestern University
// CS 211

// Original author: Prof. Joe Hummel

#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include <curl/curl.h>

#include "node.h"
#include "nodes.h"
#include "busstops.h"

using namespace std;


//
// Building
//
// Defines a campus building with a name (e.g. "Mudd"), a street
// address (e.g. "2233 Tech Dr"), and the IDs of the nodes that
// define the position / outline of the building.
// 
// NOTE: the Name could be empty "", the HouseNumber could be
// empty, and the Street could be empty. Imperfect data.
//
class Building
{
public:
  long long ID;
  string Name;
  string StreetAddress;
  vector<long long> NodeIDs;

  //
  // constructor
  //
  Building(long long id, string name, string streetAddr);

  //
  // adds the given nodeid to the end of the vector.
  //
  void add(long long nodeid);

  // step 1b: declaration of print variable 
  /* 
  Function: print
  printing building information
  parameters: nodes
  return: none
  */
  void print(const Nodes& nodes, const BusStops& busStopsObject, CURL* curl);  

  // step 3: make get location function
  /* 
  Function: getLocation
  get building location which consists of a position in lat and lon
  parameters: nodes
  return: pair<double, double>
  */
  pair<double, double> getLocation(const Nodes& nodes) const;

  /*
  Function: printClosestStops
  This function prints the closest bus stops' details and distances

  parameters: nodes, busStopObject
  returns: none
  */
  void printClosestStops(const Nodes& nodes, const BusStops& busStopObject, CURL* curl);


  /*
  getClosestStops
  This function finds the closest bus stops to the building's location
  extracts the closest stops to be used in main for step 7
  i want to leave it separate from the getClosestStops to avoid changing the return from void to pair

  parameters: nodes, busStopObject
  returns: pair<BusStop, BusStop>
  */
  pair<BusStop, BusStop> getClosestStops(const Nodes& nodes, const BusStops& busStopObject) const;


  /*
  getBusPredictions
  This function calls the CTA API to retrieve bus predictions for a given bus route and stop ID.
  Parameters: curl, apiKey, busRoute, stopID
  returns: none
  */
  void getBusPredictions(CURL* curl, const string& apiKey, int busRoute, int stopId);

};