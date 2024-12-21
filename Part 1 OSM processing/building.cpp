/*building.cpp*/

//
// A building in the Open Street Map.
// 
// Prof. Joe Hummel
// Northwestern University
// CS 211
// 

#include "building.h"
#include <iostream>

using namespace std;


//
// constructor
//
Building::Building(long long id, string name, string streetAddr)
  : ID(id), Name(name), StreetAddress(streetAddr)
{
  //
  // the proper technique is to use member initialization list above,
  // in the same order as the data members are declared:
  //
  //this->ID = id;
  //this->Name = name;
  //this->StreetAddress = streetAddr;

  // vector is default initialized by its constructor
}

//
// adds the given nodeid to the end of the vector.
//
void Building::add(long long nodeid)
{
  this->NodeIDs.push_back(nodeid);
}









// this is the implementation of the printSimpleBuildingInfo method 
// outputs the building's ID, name, and street address
void Building::printSimpleBuildingInfo()
{
  cout << this->ID << ": " << this->Name << ", " << this->StreetAddress << endl;
}

// this is the implementation of the printSimpleBuildingInfo method 
// outputs the building's ID, name, and street address with a few extra words making it more detailed version
void Building::printDetailedBuildingInfo()
{
  cout << this->Name << endl << "Address: " << this->StreetAddress << endl << "Building ID: " << this->ID << endl << "Nodes:" << endl;
}