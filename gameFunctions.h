#ifndef GAMEFUNCTIONS_H
#define GAMEFUNCTIONS_H

#include "cat.h"
#include "location.h"
#include <string>
using namespace std;

void printIntro();
void printCatArt();
void printFishArt();
void printDoorArt();
void printHelp();
string getChoice();
void statusCheck(Cat& cat);
bool checkHungerEnding(Cat& cat);
void lowerHungerForTravel(Cat& cat);

// Main story scenes
void alleyScene(Cat& cat);
void bodegaScene(Cat& cat);
void trashCanScene(Cat& cat);
void mouseScene(Cat& cat);
void raccoonScene(Cat& cat);
void parkScene(Cat& cat);
void dogParkScene(Cat& cat);
void hidingPlaceScene(Cat& cat);
void playgroundScene(Cat& cat);
void fountainScene(Cat& cat);
void sidewalkOneScene(Cat& cat);
void sidewalkTwoScene(Cat& cat);
void streetScene(Cat& cat);
void fishMarketScene(Cat& cat);
void policeStationScene(Cat& cat);
void petShelterVanScene(Cat& cat);
void deliScene(Cat& cat);
void mailVanScene(Cat& cat);
void trainStationScene(Cat& cat);
void trainCarScene(Cat& cat);
void apartmentLobbyScene(Cat& cat);
void fireEscapeScene(Cat& cat);
void apartmentOneScene(Cat& cat);
void apartmentTwoScene(Cat& cat);
void apartmentThreeScene(Cat& cat);
void rooftopScene(Cat& cat);

// Mini-game functions
bool fishGame(Cat& cat);
bool trainGame(Cat& cat);

// Ending functions
void trueEnding(Cat& cat);
void strayEnding(Cat& cat);
void hungerEnding(Cat& cat);
void wrongApartmentEnding(Cat& cat);
void bodegaEnding(Cat& cat);

#endif
