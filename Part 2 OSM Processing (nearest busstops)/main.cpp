/*main.cpp*/

//
// Program to input Nodes (positions) and Buildings from
// an Open Street Map file.
// 
// Irene Ha
// Northwestern University
// CS 211

// Original author: Prof. Joe Hummel
// Solution: Prof. Joe Hummel
// Northwestern University
// 

#include <iostream>
#include <string>

// #include "json.hpp"
#include "curl_util.h"
#include "building.h"
#include "buildings.h"
#include "busstops.h"
#include "node.h"
#include "nodes.h"
#include "osm.h"
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;
// using json = nlohmann::json;


//
// main
//
int main()
{
  XMLDocument xmldoc;
  Nodes nodes;
  Buildings buildings;
  BusStops busStopsObject;
  
  cout << "** NU open street map **" << endl;

  string filename;

  cout << endl;
  cout << "Enter map filename> " << endl;
  getline(cin, filename);

  //
  // 1. load XML-based map file 
  //
  if (!osmLoadMapFile(filename, xmldoc))
  {
    // failed, error message already output
    cout << "**ERROR:" << endl;
    cout << "**ERROR: call to osmLoadMapFile failed, perhaps filename '" << filename << "' does not exist?" << endl;
    cout << "**ERROR:" << endl;
    return 0;
  }
  
  //
  // 2. read the nodes, which are the various known positions on the map:
  //
  nodes.readMapNodes(xmldoc);

  //
  // 3. read the university buildings:
  //
  buildings.readMapBuildings(xmldoc);

  //
  // 4. stats
  //
  cout << "# of nodes: " << nodes.getNumMapNodes() << endl;
  cout << "# of buildings: " << buildings.getNumMapBuildings() << endl;
  cout << "# of bus stops: " << busStopsObject.getNumBusStops() << endl;

  // initialize curl library here this is given in the instructions for step 7
  CURL* curl = curl_easy_init();
  if (curl == nullptr) {
      cout << "**ERROR: " << endl;
      cout << "**ERROR: unable to initialize curl library" << endl;
      cout << "**ERROR:" << endl;
      return 0;
  }

  //
  // now let the user for search for 1 or more buildings:
  //
  while (true)
  {
    string name;

    cout << endl;
    cout << "Enter building name (partial or complete), or * to list, or @ for bus stops, or $ to end> " << endl;

    getline(cin, name);

    if (name == "$") {
      break;
    }
    else if (name == "*") {
      buildings.print(); // call to new print function step 1a
    }
    else if (name == "@") {
      busStopsObject.print(); // print all the bus stops when @ is entered
    }
    else {
      buildings.findAndPrint(name, nodes, busStopsObject, curl);

    }//else
  }//while

  //
  // done: cleanup CURL library
  //
  curl_easy_cleanup(curl);

  cout << endl;
  cout << "** Done **" << endl;

  return 0;


  // //
  // // done:
  // //
  // cout << endl;
  // cout << "** Done  **" << endl;
  // // cout << "# of calls to getID(): " << Node::getCallsToGetID() << endl;
  // // cout << "# of Nodes created: " << Node::getCreated() << endl;
  // // cout << "# of Nodes copied: " << Node::getCopied() << endl;
  // // cout << endl;

  // return 0;
}
