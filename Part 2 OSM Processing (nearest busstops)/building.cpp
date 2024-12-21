/*building.cpp*/

//
// A building in the Open Street Map.
// 
// Irene Ha
// Northwestern University
// CS 211

// Original author: Prof. Joe Hummel

#include "building.h"
#include "json.hpp"
#include "dist.h"
#include "busstops.h"
#include "curl_util.h"
#include <stdexcept>

#include <iostream>
#include <utility>

using namespace std;
using json = nlohmann::json;


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

// step 1b: declaration of print variable 
/* 
Function: print
printing building information
parameters: nodes, busStopsObject, curl
return: none
*/
void Building::print(const Nodes& nodes, const BusStops& busStopsObject, CURL* curl){

  cout << Name << endl;
  cout << "Address: " << StreetAddress << endl;
  cout << "Building ID: " << ID << endl;

  // instead of printing individual nodes, just print the num of perimeter nodes
  cout << "# perimeter nodes: " << NodeIDs.size() << endl;

  // prints the location
  pair<double, double> location = getLocation(nodes);
  // print the location using P.first (latitude) and P.second (longitude)
  cout << "Location: (" << location.first << ", " << location.second << ")" << endl;

  //call printClosestStops and pass BusStops object
  printClosestStops(nodes, busStopsObject, curl);




  //print closest sb stop

  //print closest nb stop

  // cout << "Nodes:" << endl;
  // for (long long nodeid : NodeIDs)
  // {
  //   cout << "  " << nodeid << ": ";

  //   double lat = 0.0;
  //   double lon = 0.0;
  //   bool entrance = false;

  //   bool found = nodes.find(nodeid, lat, lon, entrance);

  //   if (found) {
  //     cout << "(" << lat << ", " << lon << ")";

  //     if (entrance)
  //       cout << ", is entrance";

  //     cout << endl;
  //   }
  //   else {
  //     cout << "**NOT FOUND**" << endl;
  //   }
  // }//for
  
}

// step 3: building locations
/* 
Function: getLocation
get the location pair with its average lat and lon
parameters: nodes
return: pair <double, double>
*/
pair<double, double> Building::getLocation(const Nodes& nodes) const{
  //define variables used for average
  double LatSum = 0.0;
  double LonSum = 0.0;
  int count = 0.0;

  for (long long id : NodeIDs) {
    double lat = 0.0;
    double lon = 0.0;
    bool isentrance = false;

    // create found variable with find function
    bool found = nodes.find(id, lat, lon, isentrance);


    // if found add up lats, lons, and increment counter
    if (found == true) {
      LatSum += lat;
      LonSum += lon;
      count += 1;
    }
  }

  //if no nodes are found return a pair of zeros
  if (count == 0) {
    return make_pair(0.0, 0.0);
  }

  // we looped through all node IDs, summed the latitudes and longitudes, and now calculate the average
  double avgLat = LatSum / count;
  double avgLon = LonSum / count;

  return make_pair(avgLat, avgLon);

}


/*
Function: printClosestStops
This function prints the closest bus stops' details and distances

parameters: nodes, busStopObject, curl
returns: none
*/
void Building::printClosestStops(const Nodes& nodes, const BusStops& busStopObject, CURL* curl){
  //get the buildings location
  pair<double, double> location = getLocation(nodes);
  double buildingLat = location.first;
  double buildingLon = location.second;
  
  //find the closest stops
  pair<BusStop, BusStop> closestStops = busStopObject.findClosestStops(buildingLat, buildingLon);
  
  //calculate the distances again just for printing
  double closestSBDistance = distBetween2Points(buildingLat, buildingLon, closestStops.first.lat, closestStops.first.lon);
  double closestNBDistance = distBetween2Points(buildingLat, buildingLon, closestStops.second.lat, closestStops.second.lon);

  //print the south stop
  cout << "Closest southbound bus stop:" << endl;
  closestStops.first.print(closestSBDistance);

  getBusPredictions(curl, "6ijbyeSXxnSKQPLV5inis3NUn", closestStops.first.busRoute, closestStops.first.id);


  //print the north stop
  cout << "Closest northbound bus stop:" << endl;
  closestStops.second.print(closestNBDistance);
  getBusPredictions(curl, "6ijbyeSXxnSKQPLV5inis3NUn", closestStops.second.busRoute, closestStops.second.id);


}



/* 
getBusPredictions
This function calls the CTA API to retrieve bus predictions for a given bus route and stop ID.
Parameters: curl, apiKey, busRoute, stopID
returns: none
*/
void Building::getBusPredictions(CURL* curl, const string& apiKey, int busRoute, int stopId) {
    string response;

    // Build the URL using the helper function you wrote earlier
    string url = "http://ctabustracker.com/bustime/api/v2/getpredictions?key=" + apiKey +
           "&rt=" + to_string(busRoute) + "&stpid=" + to_string(stopId) + "&format=json";


    // Call the CTA API
    if (callWebServer(curl, url, response) == false) {
        cout << "  <<bus predictions unavailable, call failed>>" << endl; // not sure if i did indentation of 2 spaces correctly
        return;
    }


    // parse the returned data and build a JSON object this is given to us
    auto jsondata = json::parse(response);

    //there is one key value pair under the key "bustime-response" extract that value this is given to us
    auto bus_response = jsondata["bustime-response"];

    //next step
    auto predictions = bus_response["prd"];

    // //debugging
    // cout << "Full predictions list: " << predictions.dump(4) << endl;
    // cout << "Number of predictions: " << predictions.size() << endl;

    if (predictions.empty()) {
      cout << "  <<no predictions available>>" << endl;
      return;
    }

    //for each loop in step 8
    for (auto& M : predictions) {
      try { // using the try and catch for step 8
        cout << "  vehicle #" << stoi(M["vid"].get_ref<std::string&>())  // convert "vid" to an integer
            << " on route " << M["rt"].get_ref<std::string&>()         // print the route number (string)
            << " travelling " << M["rtdir"].get_ref<std::string&>()    // Print the direction (string)
            << " to arrive in " << M["prdctdn"].get_ref<std::string&>()  // Predicted arrival time (string)
            << " mins" << endl;
          } catch (exception& e) {
            cout << "  error" << endl;
            cout << "  malformed CTA response, prediction unavailable"
                  << " (error: " << e.what() << ")" << endl;
          }
} }











  /*
  getClosestStops
  This function finds the closest bus stops to the building's location
  extracts the closest stops to be used in main for step 7
  i want to leave it separate from the getClosestStops to avoid changing the return from void to pair

  parameters: nodes, busStopObject
  returns: pair<BusStop, BusStop>
  */
  pair<BusStop, BusStop> Building::getClosestStops(const Nodes& nodes, const BusStops& busStopObject) const {
    pair<double, double> location = getLocation(nodes);
    double buildingLat = location.first;
    double buildingLon = location.second;

    //find the closest stops
    pair<BusStop, BusStop> closestStops = busStopObject.findClosestStops(buildingLat, buildingLon);

    return closestStops;
  }