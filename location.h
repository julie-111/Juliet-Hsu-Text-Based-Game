#ifndef LOCATION_H
#define LOCATION_H

#include <iostream>
#include <string>
using namespace std;

class Location {
private:
    string name;
    string description;

public:
    Location(string locationName = "Unknown", string locationDescription = "No description.");

    string getName() const;
    string getDescription() const;
    void printLocation() const;
};

#endif

