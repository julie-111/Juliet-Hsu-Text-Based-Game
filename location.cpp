#include "location.h"

Location::Location(string locationName, string locationDescription) {
    name = locationName;
    description = locationDescription;
}

string Location::getName() const {
    return name;
}

string Location::getDescription() const {
    return description;
}

void Location::printLocation() const {
    cout << "\n---------- " << name << " ----------\n";
    cout << description << "\n";
}
