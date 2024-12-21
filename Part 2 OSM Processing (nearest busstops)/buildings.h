/*buildings.h*/

//
// A collection of buildings in the Open Street Map.
// 
// Irene Ha
// Northwestern University
// CS 211

// Original author: Prof. Joe Hummel

#pragma once

#include <vector>

#include "building.h"
#include "tinyxml2.h"
#include "curl_util.h"

using namespace std;
using namespace tinyxml2;


//
// Keeps track of all the buildings in the map.
//
class Buildings
{
public:
  vector<Building> MapBuildings;

  //
  // readMapBuildings
  //
  // Given an XML document, reads through the document and 
  // stores all the buildings into the given vector.
  //
  void readMapBuildings(XMLDocument& xmldoc);

  //
  // accessors / getters
  //
  int getNumMapBuildings();


  // step 1a: declaration of print variable 
  /* 
  Function: print
  printing building information
  return: none
  */
  void print();

  // step 1c: declaration of print variable 
  /* 
  Function: findAndPrint
  searches and prints over the Buildings class
  parameters: name and nodes, busStopsObject, curl
  return: none
  */
  void findAndPrint(const string& name, const Nodes& nodes, const BusStops& busStopsObject, CURL* curl);


  /*
  function: find
  find and return which building were looking at based on name

  parameters: name
  returns: building
  */
  Building* find(const string& name);


};


