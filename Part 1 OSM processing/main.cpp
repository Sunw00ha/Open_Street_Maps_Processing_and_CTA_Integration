/*main.cpp*/

// main file

// Irene Ha
// Northwestern University
// CS 211

// Original author: Prof. Joe Hummel

#include <iostream>
#include <string>

#include "building.h"
#include "node.h"
#include "nodes.h"
#include "osm.h"
#include "tinyxml2.h"
#include "buildings.h"


using namespace std;
using namespace tinyxml2;



int main()
{
    string filename;
    XMLDocument xmldoc;
    Buildings buildings; // declared this buildings object outside of the if statement so that its accessible when we do our * command
    Nodes mapNodes; // similar as above we need to use mapNodes for when users command is partial or complete building name
    
    cout << "** NU open street map **" << endl << endl;

    cout << "input OSM file: ";
    getline(cin, filename); // get file name from user

    // if else statement for reading into xml and if true and error message if false
    if (osmLoadMapFile(filename, xmldoc)) {
        mapNodes.readMapNodes(xmldoc); // call readMapNodes function on mapNodes object, pass xmldoc as argument print number of nodes
        cout << "Number of Nodes: " << mapNodes.getNumMapNodes() << endl;
    
        buildings.readMapBuildings(xmldoc); // read buildings from map, print number of buildings
        cout << "Number of Buildings: " << buildings.getNumMapBuildings() << endl;
    }
    else {
        cout << "Error in reading the content of this file" << endl; // error message if they provide wrong file name
        return 0;
    }
    string command; // variable for what user inputs
    while (true) { // interactive loop for what the user could input as the command
        cout << "Enter building name (partial or complete), or * to list, or $ to end>" << endl;
        getline(cin, command);

        if (command == "$") {// $ means break and stop
            break;
        }
        
        else if (command == "*") { // * means print everything loop thorugh each building in the MapBuilding vector and print out info
            // look at the buildings.h file to see that MapBuildings is a vector of Building objects found in the Buildings class
            //loop through the building objects vector
            for (Building& b : buildings.MapBuildings) { //loop through the building objects vector //Building refers to the type of object stored in the MapBuildings vector // buildings is an object of the Buildings class
                b.printSimpleBuildingInfo(); //output each buildings ID, name, street address by calling the helper function found in building.cpp
            }
        }
        // if its not $ or * then partial or complete building name entered
        else {
            // create found variable to use when we need to print "no such building"
            bool found = false;
            // loop thorugh every building in the MapBuildings vector
            // if the command given is found or "is not string::npos" then print the info
            for (Building& b : buildings.MapBuildings) {
                if (b.Name.find(command) != string::npos) {//string::npos means not found
                    found = true;
                    b.printDetailedBuildingInfo(); // print building information using the helper function found in building.cpp
            
                    //if found do the node id thing
                    // for every node ID in vector of NodeIDs
                    for (long long nodeID : b.NodeIDs){
                        double lat;
                        double lon;
                        bool isEntrance; //defined in the Node class

                        if (mapNodes.find(nodeID, lat, lon, isEntrance)) {//mapNodes is a vetor of Node objects found in Nodes class in node.h
                            cout << "  " << nodeID << ": (" << lat << ", " << lon << ")";

                            // if the isEntrance bool is true then print this
                            if (isEntrance) {// after writing common node information, check if it is an entrance
                                cout << ", is entrance";
                            }
                            // endl needs to go here for formatting reasons
                            cout << endl;
                        } 
                    }
                } 
            }
            // if we never did the stuff in the if statement, which includes turning found to true, then execute below
            if (found == false) {
                cout << "No such building" << endl;
            }
        }
    }

    // print info when done
    cout << "** Done **" << endl;
    cout << "# of calls to getID(): " << Node::getCallsToGetID() << endl;
    cout << "# of Nodes created: " << Node::getCreated() << endl;
    cout << "# of Nodes copied: " << Node::getCopied() << endl;

    return 0;
}