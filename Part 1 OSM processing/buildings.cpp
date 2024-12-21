/*buildings.cpp*/

// implements functionality for handling and storing buildings from an Open Street Map XML doc


// Irene Ha
// Northwestern University
// CS 211

// Original author: Prof. Joe Hummel


#include <iostream>
#include <string>
#include <cassert>

#include "buildings.h"
#include "building.h"
#include "node.h"
#include "nodes.h"
#include "osm.h"
#include "tinyxml2.h"



using namespace std;
using namespace tinyxml2;


/* 
Function: readMapBuildings

reads through an Open Street Map XML document and extracts all the "way" elements that represent buildings
filters for buildings, retrieves the buildings name and street addy and stores the data in the MapBuildings vector

Parameters: xmldoc

returns: none bc its a void function

*/
void Buildings::readMapBuildings(XMLDocument& xmldoc) { // :: tells the compiler that the function belongs to Buildings class
    XMLElement* osm = xmldoc.FirstChildElement("osm"); // osm is the root element
    assert(osm != nullptr); //make sure root <osm> element exists

    XMLElement* way = osm->FirstChildElement("way");

    while (way != nullptr) { //make sure <way> element exists
        // If the way element contains the (key, value) pair (“building”, “university”)
        if (osmContainsKeyValue(way, "building", "university")) {
            //building object that needs to be created
            
            //grab way id 
            const XMLAttribute* wayIDAttribute = way->FindAttribute("id"); // looks for an attribute named "id" in the way element
            assert(wayIDAttribute != nullptr); // make sure the ID attribute exists
            long long id = wayIDAttribute->Int64Value(); // get the way id as a long long type
            
            //grab building name and street addy
            string name = osmGetKeyValue(way, "name");
            string streetAddr = osmGetKeyValue(way, "addr:housenumber")
            + " "
            + osmGetKeyValue(way, "addr:street");

            //create building object b
            Building B(id, name, streetAddr);
            
            //Loop through the “nd” references, adding each node reference attribute to B's NodeIDs vector
            XMLElement* nd = way->FirstChildElement("nd");

            while (nd != nullptr) 
            {
                const XMLAttribute* ndref = nd->FindAttribute("ref");
                assert(ndref != nullptr);

                long long id = ndref->Int64Value();

                B.add(id);

                //advance to next node ref:
                nd = nd->NextSiblingElement("nd");
            }

            MapBuildings.push_back(B);
        }
        
        //move to the next <way> element **added
        way = way->NextSiblingElement("way");
        }
    }



/* 
Function: getNumMapBuildings

returns the total number of buildings stored in the MapBuildings vector

returns: size of the MapBuildings vector (int)

*/

// write getNumMapBuildings
int Buildings::getNumMapBuildings() const {
    return MapBuildings.size(); // return the size of the vector of buildings
}