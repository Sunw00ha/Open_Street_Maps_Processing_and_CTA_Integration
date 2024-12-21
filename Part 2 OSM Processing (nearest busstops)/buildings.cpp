/*buildings.cpp*/

//
// A collection of buildings in the Open Street Map.
// 
// Irene Ha
// Northwestern University
// CS 211

// Original author: Prof. Joe Hummel

#include <iostream>
#include <string>
#include <vector>
#include <cassert>

#include "buildings.h"
#include "curl_util.h"
#include "osm.h"
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;


//
// readMapBuildings
//
// Given an XML document, reads through the document and 
// stores all the buildings into the given vector.
//
void Buildings::readMapBuildings(XMLDocument& xmldoc)
{
  XMLElement* osm = xmldoc.FirstChildElement("osm");
  assert(osm != nullptr);

  //
  // Parse the XML document way by way, looking for university buildings:
  //
  XMLElement* way = osm->FirstChildElement("way");

  while (way != nullptr)
  {
    const XMLAttribute* attr = way->FindAttribute("id");
    assert(attr != nullptr);

    //
    // if this is a building, store info into vector:
    //
    if (osmContainsKeyValue(way, "building", "university"))
    {
      string name = osmGetKeyValue(way, "name");

      string streetAddr = osmGetKeyValue(way, "addr:housenumber")
        + " "
        + osmGetKeyValue(way, "addr:street");

      //
      // create building object, then add the associated
      // node ids to the object:
      //
      long long id = attr->Int64Value();

      Building B(id, name, streetAddr);

      XMLElement* nd = way->FirstChildElement("nd");

      while (nd != nullptr)
      {
        const XMLAttribute* ndref = nd->FindAttribute("ref");
        assert(ndref != nullptr);

        long long id = ndref->Int64Value();

        B.add(id);

        // advance to next node ref:
        nd = nd->NextSiblingElement("nd");
      }

      //
      // add the building to the vector:
      //
      this->MapBuildings.push_back(B);
    }//if

    way = way->NextSiblingElement("way");
  }//while

  //
  // done:
  //
}

//
// accessors / getters
//
int Buildings::getNumMapBuildings() {
  return (int) this->MapBuildings.size();
}


/* 
  Function: print
  Purpose: Prints the ID, name, and street address of each building 
  stored in the MapBuildings vector.
  
  parameters: none
  return: none
  */
void Buildings::print() {
  for (Building B : MapBuildings) { // for every building in the buildings vector
        cout << B.ID << ": " << B.Name << ", " << B.StreetAddress << endl;
  }
}


// step 1c: declaration of print variable 
/* 
Function: findAndPrint
searches and prints over the Buildings class
parameters: name, nodes, busStopsObject, curl
return: none
*/
void Buildings::findAndPrint(const string& name, const Nodes& nodes, const BusStops& busStopsObject, CURL* curl) {
  // find every building that contains this name:
  bool foundAtLeastOne = false;

  // loop through all buildings in the MapBuildings vector
  // Calculate distances between the building's location and each closest bus stop
  for (Building B : MapBuildings)
  {
    if (B.Name.find(name) != string::npos) {  // contains name:
      foundAtLeastOne = true;
      B.print(nodes, busStopsObject, curl); // print the building's details along wiht bus stop info
    }
  }

  if (!foundAtLeastOne) {
    cout << "No such building" << endl;
  }
}


/*
function: find
find and return which building were looking at based on name

parameters: name
returns: building
*/
Building* Buildings::find(const string& name) {
  for (Building& B : MapBuildings) { // for every building in the vector of buildings
    if (B.Name.find(name) != string::npos) {  // contains name:
      return &B;  // Return a pointer to the building
    }
  }
  return nullptr;  // Return nullptr if no building found
}
