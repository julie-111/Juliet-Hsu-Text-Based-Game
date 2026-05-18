#include "cat.h"    // Header file for the Cat class
#include "location.h"   // Header file for different game locations/scenes
#include "gameFunctions.h"  // Header file for helper game functions

#include <iostream>
#include <cstdlib>  // Needed for rand() and srand()
#include <ctime>    // Needed for time()
using namespace std;

int main() {
    // srand/time are used so the mini-games with rand() change each time the game runs.
    srand(time(0));

    string catName;

    printIntro();
    cout << "But first, what is your cat's name? ";
    getline(cin, catName);

    // If the player enters nothing, we'll use a default name
    if (catName == "") {
        catName = "Mochi";
    }

    Cat player(catName);

    cout << "\nWelcome, " << player.getName() << ". Your adventure begins now.\n";

    // Start the first game scene
    alleyScene(player);

    // Final message after the game ends
    cout << "\nThank you for playing Stray Cat Adventure: NYC!\n";

    return 0;
}



