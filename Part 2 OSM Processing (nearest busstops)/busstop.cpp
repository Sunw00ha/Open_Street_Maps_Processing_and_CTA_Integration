/*busstop.cpp*/

// This class includes functionality for printing bus stop details

// Irene Ha
// Northwestern University
// CS 211

// Original author: Prof. Joe Hummel


#include "busstop.h"

/* 
function: print
Prints the details of a bus stop including its ID, name, route, location, 
and the calculated distance from a reference point.

parameters: distance
returns: none
*/
void BusStop::print(double distance) const {
    cout << "  " << id << ": " << stopName << ", bus #" << busRoute 
         << ", " << stopLocation
         << ", " << distance << " miles" << endl;
}