/*building.h*/

//
// A building in the Open Street Map.
// 
// Prof. Joe Hummel
// Northwestern University
// CS 211
// 

#pragma once

#include <string>
#include <vector>

#include "node.h"

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

  // Function: add
  // adds the given nodeid to the end of the vector.
  // Parameters: nodeid
  // returns: none (void function)
  void add(long long nodeid);



/* Function: printSimpleBuildingInfo
Outputs the building's ID, name, and street address in a simple format

returns: none (void)
*/
  void printSimpleBuildingInfo();
  


/* Function: printDetailedBuildingInfo
Outputs the building's name, street address, building ID, and a header for nodes

returns: none (void)
*/
  void printDetailedBuildingInfo();
};
