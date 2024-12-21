/*buildings.h*/

// a collection of buildings in the Open Street Map

// Irene Ha
// Northwestern University
// CS 211

// Original author: Prof. Joe Hummel

#pragma once

#include <vector>
#include "building.h"
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;

// keep track of all the buildings in the map

class Buildings
{
    public:
    vector<Building> MapBuildings;

    // readMapBuildings
    // given a XML doc, it reads through the doc and stores all the buildings into the given vector
    // parameters: xmldoc
    //returns: none (void)
    void readMapBuildings(XMLDocument& xmldoc);

    // accessors / getters
    // getNumMapBuildings
    // returns total number of buildings in the vector
    // returns: int
    int getNumMapBuildings() const;

};