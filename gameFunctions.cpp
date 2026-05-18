#include "gameFunctions.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cctype>
using namespace std;

// Introduction screen shown at the beginning of the game
void printIntro() {
    cout << "\n============================================================\n";
    cout << "                 STRAY CAT ADVENTURE: NYC\n";
    cout << "============================================================\n";
    cout << "Your goal is to find your way home through NYC as a lost cat.\n";
    cout << "The choices you make will change your hunger, trust, score,\n";
    cout << "and inventory. Type words like left, right, forward, talk,\n";
    cout << "status, or inventory when the game asks for your choice.\n";
    cout << "============================================================\n";
}

void printCatArt() {
    cout << "\n";
    cout << "/\\-----/\\\n";
    cout << "( o   o )  ,\"\"\n";
    cout << "(  _^_  ) //\n";
}

void printFishArt() {
    cout << "\n";
    cout << "        ><(((('>\n";
    cout << "       Fresh fish!\n";
}

void printDoorArt() {
    cout << "\n";
    cout << "       ___________\n";
    cout << "      |  _______  |\n";
    cout << "      | |       | |\n";
    cout << "      | | HOME  | |\n";
    cout << "      | |_______| |\n";
    cout << "      |        o  |\n";
    cout << "      |___________|\n";
}

// Helper function that reminds player of possible commands
void printHelp() {
    cout << "\nYou can often type: left, right, forward, talk, leave, status, or inventory.\n";
    cout << "If you are stuck, read the scene again and choose one of the action words.\n";
}

// Gets player input and converts it into lowercase
string getChoice() {
    string choice;
    cout << "\n> ";
    getline(cin, choice);

    // Convert every letter into lowercase. This prevents problems with capital letters
    for (int i = 0; i < choice.length(); i++) {
        choice[i] = tolower(choice[i]);
    }

    return choice;
}

// Displays current player status
void statusCheck(Cat& cat) {
    cat.showStatus();
}

// Checks whether the cat starved
bool checkHungerEnding(Cat& cat) {
    if (cat.getHunger() <= 0) {
        hungerEnding(cat);
        return true;
    }
    return false;
}

// Lowers hunger slightly whenever player travels
void lowerHungerForTravel(Cat& cat) {
    // Traveling makes the cat more hungry
    cat.changeHunger(-4);
    // Check if hunger reached zero
    if (cat.getHunger() <= 0) {
        hungerEnding(cat);
    }
}

// First game scene
void alleyScene(Cat& cat) {
    Location alley("Alley", "You wake up in an alley during the evening. You are lost, hungry, and far from your owner. You think to yourself, how can I get home?");
    alley.printLocation();
    printCatArt();

    // Describe choices
    cout << "To your left is a bodega. To your right is a trash can near the park.\n";
    cout << "You can also go forward toward the sidewalk. Where do you go?\n";

    // Loop until valid choice is entered
    while (true) {
        string choice = getChoice();

        // Player goes to bodega
        if (choice == "left" || choice == "bodega") {
            bodegaScene(cat);
            return;
        }
        // Player goes to trash can
        else if (choice == "right" || choice == "trash" || choice == "trash can") {
            trashCanScene(cat);
            return;
        }
        // Player goes to sidewalk
        else if (choice == "forward" || choice == "sidewalk") {
            sidewalkOneScene(cat);
            return;
        }
        // Show status screen
        else if (choice == "status" || choice == "inventory") {
            statusCheck(cat);
        }
        // Invalid command
        else {
            printHelp();
        }
    }
}

// BODEGA SCENE
void bodegaScene(Cat& cat) {
    // Traveling costs hunger
    lowerHungerForTravel(cat);
    // Stop if player starved
    if (checkHungerEnding(cat)) {
        return;
    }

    Location bodega("Bodega", "You slip inside after a customer opens the door. Creeping through the aisles, you smell turkey, cat food, and danger.");
    bodega.printLocation();

    cout << "You see a ripped bag of cat food and a turkey sandwich on the counter.\n";
    cout << "Choose: sandwich, cat food, or leave.\n";

    while (true) {
        string choice = getChoice();

        // Sandwich choice
        if (choice == "sandwich" || choice == "turkey") {
            cout << "You jump on the counter, knock the sandwich down, grab turkey, and escape out the door!\n";

            // Gain points and hunger
            cat.changeScore(5);
            cat.changeHunger(15);
            // Add item to inventory
            cat.addItem("Turkey Bite");
            // Return to sidewalk
            sidewalkOneScene(cat);
            return;
        }

        // Cat food choice
        else if (choice == "cat food" || choice == "food") {
            cout << "SCRATCH! SCRATCH! The bag makes too much noise. Scratch again or leave?\n";
            string secondChoice = getChoice();

            // Ending as a bodega cat if scratching again
            if (secondChoice == "scratch" || secondChoice == "again" || secondChoice == "scratch again") {
                bodegaEnding(cat);
                return;
            }

            // Escape safely
            else {
                cout << "You leave the bag alone and run before the owner sees you.\n";
                cat.changeScore(5);
                sidewalkOneScene(cat);
                return;
            }
        }

        // Leave bodega
        else if (choice == "leave" || choice == "forward") {
            sidewalkOneScene(cat);
            return;
        }

        // Check status or inventory
        else if (choice == "status" || choice == "inventory") {
            statusCheck(cat);
            return;
        }

        // Invalid choice
        else {
            printHelp();
            return;
        }
    }
}

// Trash can scene
void trashCanScene(Cat& cat) {
    // Lower hunger for travel and check if hunger ended
    lowerHungerForTravel(cat);
    if (checkHungerEnding(cat)) {
        return;
    }

    Location trash("Trash Can", "You jump onto the trash can. Sniff! You smell mouse, raccoon, bread, and garbage. Bleh!");
    trash.printLocation();

    cout << "Choose: mouse, raccoon, garbage, or park.\n";

    while (true) {
        string choice = getChoice();

        if (choice == "mouse") {
            mouseScene(cat);
            return;
        }
        else if (choice == "raccoon") {
            raccoonScene(cat);
            return;
        }
        else if (choice == "garbage" || choice == "trash") {
            cout << "You find bread and a ripped paper with colored train lines.\n";
            cat.changeHunger(8);
            cat.changeScore(10);
            cat.addItem("City Guide Piece 1");
            cout << "The raccoon hisses, but you escape toward the park.\n";
            parkScene(cat);
            return;
        }
        else if (choice == "park" || choice == "right" || choice == "forward") {
            parkScene(cat);
            return;
        }
        else if (choice == "status" || choice == "inventory") {
            statusCheck(cat);
        }
        else {
            printHelp();
        }
    }
}

void mouseScene(Cat& cat) {
    Location mouse("Mouse Encounter", "A tiny mouse shakes behind a can and begs you not to hurt him. You feel scared, maybe a little hungry too.");
    mouse.printLocation();

    cout << "Do you eat the mouse or talk to the mouse?\n";

    while (true) {
        string choice = getChoice();

        if (choice == "eat" || choice == "hurt") {
            cout << "You eat the mouse. You feel less hungry, but the alley animals trust you less.\n";
            cat.changeHunger(20);
            cat.changeTrust(-5);
            cat.changeScore(10);
            trashCanScene(cat);
            return;
        }
        else if (choice == "talk") {
            cout << "Mouse: You are too clean to be a real alley cat. You must be lost. For not eating me, take this city guide piece!\n";
            cat.changeTrust(5);
            cat.changeScore(15);
            cat.addItem("City Guide Piece 1");
            parkScene(cat);
            return;
        }
        else if (choice == "status" || choice == "inventory") {
            statusCheck(cat);
        }
        else {
            printHelp();
        }
    }
}

void raccoonScene(Cat& cat) {
    Location raccoon("Raccoon Encounter", "A raccoon pops out of the trash like he owns the whole block.");
    raccoon.printLocation();

    cout << "Raccoon: This is MY trash. Talk more or search garbage?\n";

    while (true) {
        string choice = getChoice();

        if (choice == "talk" || choice == "talk more") {
            cout << "Raccoon: Fine, lost whiskers. Search, but don't steal my good snacks.\n";
            cat.changeScore(5);
            cat.changeTrust(3);
            cat.addItem("City Guide Piece 1");
            parkScene(cat);
            return;
        }
        else if (choice == "search" || choice == "garbage") {
            cout << "The raccoon attacks you! You escape, but now the street animals are suspicious.\n";
            cat.changeTrust(-5);
            cat.changeHunger(-8);
            parkScene(cat);
            return;
        }
        else if (choice == "status" || choice == "inventory") {
            statusCheck(cat);
        }
        else {
            printHelp();
        }
    }
}

void parkScene(Cat& cat) {
    lowerHungerForTravel(cat);
    if (checkHungerEnding(cat)) return;

    Location park("Park", "The park is huge and noisy. You can go left to the dog park, forward to the playground, or right to the fountain.");
    park.printLocation();

    while (true) {
        string choice = getChoice();

        if (choice == "left" || choice == "dog park") {
            dogParkScene(cat);
            return;
        }
        else if (choice == "forward" || choice == "playground") {
            playgroundScene(cat);
            return;
        }
        else if (choice == "right" || choice == "fountain") {
            fountainScene(cat);
            return;
        }
        else if (choice == "leave" || choice == "sidewalk") {
            sidewalkTwoScene(cat);
            return;
        }
        else if (choice == "status" || choice == "inventory") {
            statusCheck(cat);
        }
        else {
            printHelp();
        }
    }
}

void dogParkScene(Cat& cat) {
    Location dogPark("Dog Park", "Barks and squeaky noises overlap from every direction. A dog stares right at you.");
    dogPark.printLocation();

    cout << "Dog: Ball! Ball! Do you have my ball? Answer yes or no.\n";

    while (true) {
        string choice = getChoice();

        if (choice == "no") {
            cout << "Dog: Wait, you are not even a dog! Haha! The dog licks you and runs away.\n";
            cat.changeTrust(5);
            cat.changeScore(10);
            playgroundScene(cat);
            return;
        }
        else if (choice == "yes") {
            cout << "Dog: GRRR!! RUFF! RUFF!\n";
            cout << "You lied. The dog barks loudly and other dogs start chasing you!\n";
            cat.changeTrust(-5);
            cout << "Run to the street or hide?\n";
            string nextChoice = getChoice();

            if (nextChoice == "hide" || nextChoice == "hiding place") {
                hidingPlaceScene(cat);
            }
            else {
                streetScene(cat);
            }
            return;
        }
        else if (choice == "status" || choice == "inventory") {
            statusCheck(cat);
        }
        else {
            printHelp();
        }
    }
}

void hidingPlaceScene(Cat& cat) {
    Location hiding("Hiding Place", "You squeeze behind a rock outside the dog park. Another stray cat is sleeping there.");
    hiding.printLocation();

    cout << "Do you say lost, dogs, or leave?\n";

    while (true) {
        string choice = getChoice();

        if (choice == "lost") {
            cout << "Stray Cat: Try the police station or the train. Take this map piece, be careful crossing streets.\n";
            cat.changeScore(10);
            cat.changeTrust(5);
            cat.addItem("City Guide Piece 2");
            sidewalkOneScene(cat);
            return;
        }
        else if (choice == "dogs") {
            cout << "Stray Cat: You should leave the park before they smell you again.\n";
            sidewalkTwoScene(cat);
            return;
        }
        else if (choice == "leave") {
            sidewalkTwoScene(cat);
            return;
        }
        else if (choice == "status" || choice == "inventory") {
            statusCheck(cat);
        }
        else {
            printHelp();
        }
    }
}

void playgroundScene(Cat& cat) {
    Location playground("Playground", "The playground is full of tiny shoes, lost mittens, and snack crumbs.");
    playground.printLocation();

    cout << "You find cookie crumbs and a shiny keychain. Take crumbs, keychain, or leave?\n";

    while (true) {
        string choice = getChoice();

        if (choice == "crumbs") {
            cout << "You eat the crumbs. Not fancy, but it helps.\n";
            cat.changeHunger(6);
            cat.changeScore(5);
            fountainScene(cat);
            return;
        }
        else if (choice == "keychain") {
            cout << "You carry the shiny keychain. It might be useful to distract someone later.\n";
            cat.addItem("Shiny Keychain");
            cat.changeScore(5);
            fountainScene(cat);
            return;
        }
        else if (choice == "leave") {
            sidewalkTwoScene(cat);
            return;
        }
        else if (choice == "status" || choice == "inventory") {
            statusCheck(cat);
        }
        else {
            printHelp();
        }
    }
}

void fountainScene(Cat& cat) {
    Location fountain("Fountain", "A pigeon walks around the water like he is the mayor of the park.");
    fountain.printLocation();

    cout << "Pigeon: Coo! Have you ever wondered what it’s like to be a pigeon? I can fly anywhere I want.\n";
    cout << "I could really live anywhere if I wanted tooo. Where do you want to go? Say home or another place.\n";
    string choice = getChoice();

    if (choice == "home") {
        cout << "Pigeon: Home? Well im not sure where that is, but people go 'home' by train. Try the train station, kitty.\n";
        cat.changeScore(5);
        cat.addItem("Train Hint");
    }
    else if (choice == "status" || choice == "inventory") {
        statusCheck(cat);
    }
    else {
        cout << "Pigeon: I don't know that place. I only know crumbs and trains.\n";
    }

    sidewalkTwoScene(cat);
}

void sidewalkOneScene(Cat& cat) {
    lowerHungerForTravel(cat);
    if (checkHungerEnding(cat)) return;

    Location sidewalk("Sidewalk Path 1", "Cars rush beside you. Left smells like fish. Forward is a police station. Right crosses to another sidewalk.");
    sidewalk.printLocation();

    while (true) {
        string choice = getChoice();

        if (choice == "left" || choice == "fish" || choice == "fish market") {
            fishMarketScene(cat);
            return;
        }
        else if (choice == "forward" || choice == "police" || choice == "police station") {
            policeStationScene(cat);
            return;
        }
        else if (choice == "right" || choice == "street") {
            streetScene(cat);
            return;
        }
        else if (choice == "status" || choice == "inventory") {
            statusCheck(cat);
        }
        else {
            printHelp();
        }
    }
}

void sidewalkTwoScene(Cat& cat) {
    lowerHungerForTravel(cat);
    if (checkHungerEnding(cat)) return;

    Location sidewalk("Sidewalk Path 2", "This sidewalk has a deli on the left and a train station stairs straight ahead. The park is also behind you.");
    sidewalk.printLocation();

    while (true) {
        string choice = getChoice();

        if (choice == "left" || choice == "deli") {
            deliScene(cat);
            return;
        }
        else if (choice == "forward" || choice == "train" || choice == "train station") {
            trainStationScene(cat);
            return;
        }
        else if (choice == "right" || choice == "street") {
            streetScene(cat);
            return;
        }
        else if (choice == "park") {
            parkScene(cat);
            return;
        }
        else if (choice == "status" || choice == "inventory") {
            statusCheck(cat);
        }
        else {
            printHelp();
        }
    }
}

void streetScene(Cat& cat) {
    Location street("Street", "The road is loud. Yellow taxis move like giant metal tigers.");
    street.printLocation();

    cout << "You must choose quickly: left to Sidewalk 1 or right to Sidewalk 2.\n";

    while (true) {
        string choice = getChoice();

        if (choice == "left") {
            sidewalkOneScene(cat);
            return;
        }
        else if (choice == "right") {
            sidewalkTwoScene(cat);
            return;
        }
        else if (choice == "status" || choice == "inventory") {
            statusCheck(cat);
        }
        else {
            cout << "A taxi honks! Choose left or right!\n";
        }
    }
}

void fishMarketScene(Cat& cat) {
    lowerHungerForTravel(cat);
    if (checkHungerEnding(cat)) return;

    Location market("Fish Market", "The smell of fish is so strong that your whiskers almost dance. You have the chance at nagging a piece!");
    market.printLocation();
    printFishArt();

    cout << "Play the fish catching mini-game? yes or no\n";
    string choice = getChoice();

    if (choice == "yes" || choice == "play") {
        bool won = fishGame(cat);
        if (won) {
            cat.addItem("Fish Snack");
        }
    }

    sidewalkOneScene(cat);
}

bool fishGame(Cat& cat) {
    // rand() mini-game source idea: C++ rand examples from cplusplus.com/reference/cstdlib/rand/
    int fishSpot = rand() % 3 + 1;
    int guess;

    cout << "A fish falls behind box 1, 2, or 3. Guess the box: ";
    cin >> guess;
    cin.ignore(1000, '\n');

    if (guess == fishSpot) {
        cout << "You caught the fish! Hunger increases.\n";
        cat.changeHunger(20);
        cat.changeScore(20);
        return true;
    }
    else {
        cout << "Wrong box! The fish worker shouts and you run away.\n";
        cat.changeHunger(-5);
        cat.changeScore(2);
        return false;
    }
}

void policeStationScene(Cat& cat) {
    Location station("Police Station", "The police station is large, bright, and too clean for a lost cat.");
    station.printLocation();

    cout << "An officer says, 'Poor kitty.' You can meow, hide, or run.\n";

    while (true) {
        string choice = getChoice();

        if (choice == "meow" || choice == "talk") {
            cout << "The officer gives you water but calls a pet shelter van.\n";
            cat.changeTrust(5);
            petShelterVanScene(cat);
            return;
        }
        else if (choice == "hide") {
            cout << "You hide under a bench and find a torn address sticker.\n";
            cat.addItem("Address Sticker");
            cat.changeScore(10);
            trainStationScene(cat);
            return;
        }
        else if (choice == "run") {
            trainStationScene(cat);
            return;
        }
        else if (choice == "status" || choice == "inventory") {
            statusCheck(cat);
        }
        else {
            printHelp();
        }
    }
}

void petShelterVanScene(Cat& cat) {
    Location van("Pet Shelter Van", "Oh no! You are inside a pet shelter van with other animals.");
    van.printLocation();

    cout << "A bird notices the back door is loose. Do you distract, scratch, or wait?\n";

    while (true) {
        string choice = getChoice();

        if (choice == "distract") {
            if (cat.hasItem("Shiny Keychain")) {
                cout << "You shake the shiny keychain. The worker looks away and the bird opens the door!\n";
                cat.changeScore(15);
                trainStationScene(cat);
                return;
            }
            else {
                cout << "You try to distract them, but you have nothing shiny.\n";
                cat.changeHunger(-5);
            }
        }
        else if (choice == "scratch") {
            cout << "You and the bird scratch the loose door until it pops! It opened near the train station!\n";
            cat.changeScore(10);
            trainStationScene(cat);
            return;
        }
        else if (choice == "wait") {
            strayEnding(cat);
            return;
        }
        else if (choice == "status" || choice == "inventory") {
            statusCheck(cat);
        }
        else {
            printHelp();
        }
    }
}

void deliScene(Cat& cat) {
    Location deli("Deli", "This deli smells like bread, cheese, and trouble.");
    deli.printLocation();

    cout << "You see tuna on the counter. Steal, beg, or leave?\n";

    while (true) {
        string choice = getChoice();

        if (choice == "steal") {
            cout << "You steal tuna, but the deli worker catches you!\n";
            bodegaEnding(cat);
            return;
        }
        else if (choice == "beg" || choice == "meow") {
            cout << "You do your saddest meow. Someone gives you a tiny tuna piece.\n";
            cat.changeHunger(12);
            cat.changeTrust(4);
            cat.changeScore(8);
            mailVanScene(cat);
            return;
        }
        else if (choice == "leave" || choice == "forward") {
            trainStationScene(cat);
            return;
        }
        else if (choice == "status" || choice == "inventory") {
            statusCheck(cat);
        }
        else {
            printHelp();
        }
    }
}

void mailVanScene(Cat& cat) {
    Location mail("Mail Delivery Van", "You jump into a mail van. The door shuts and the van starts moving.");
    mail.printLocation();

    cout << "Inside, you find a package label with your apartment building address.\n";
    cat.addItem("Final Map Piece");
    cat.changeScore(15);
    apartmentLobbyScene(cat);
}

void trainStationScene(Cat& cat) {
    lowerHungerForTravel(cat);
    if (checkHungerEnding(cat)) return;

    Location trainStation("Train Station", "You go down the stairs. The smell is powerful and the signs are confusing.");
    trainStation.printLocation();

    cout << "You can enter the train car, check status, or leave to sidewalk.\n";

    while (true) {
        string choice = getChoice();

        if (choice == "train" || choice == "train car" || choice == "enter" || choice == "forward") {
            trainCarScene(cat);
            return;
        }
        else if (choice == "leave") {
            sidewalkTwoScene(cat);
            return;
        }
        else if (choice == "status" || choice == "inventory") {
            statusCheck(cat);
        }
        else {
            printHelp();
        }
    }
}

void trainCarScene(Cat& cat) {
    Location trainCar("Train Car", "The train doors open. People step around you, but nobody understands your mission.");
    trainCar.printLocation();

    cout << "You must play the train mini-game to choose the right train home.\n";
    bool won = trainGame(cat);

    if (won) {
        apartmentLobbyScene(cat);
    }
    else {
        cout << "You ride the wrong train and lose time, but a kind student helps you back.\n";
        cat.changeHunger(-10);
        sidewalkTwoScene(cat);
    }
}

// MINI-GAME FUNCTION
// Train guessing mini-game
bool trainGame(Cat& cat) {
    // Random correct train number
    int correctTrain = rand() % 3 + 1;
    int guess;

    cout << "Three trains arrive: 1, 2, and 3.\n";
    cout << "Use your cat instinct and choose the train number: ";
    cin >> guess;

    // Remove leftover newline
    cin.ignore(1000, '\n');

    // Player wins if guessed correctly or has a train hint
    if (guess == correctTrain || cat.hasItem("Train Hint")) {
        cout << "You chose the right train! The city lights pass by the window.\n";
        cat.changeScore(25);
        return true;
    }
    // Player loses
    else {
        cout << "Wrong train! The correct train was " << correctTrain << ".\n";
        cat.changeScore(5);
        return false;
    }
}

void apartmentLobbyScene(Cat& cat) {
    lowerHungerForTravel(cat);
    if (checkHungerEnding(cat)) return;

    Location lobby("Apartment Lobby", "You enter an apartment lobby. Mailboxes line the wall. This place feels almost familiar.");
    lobby.printLocation();

    if (!cat.hasItem("Final Map Piece")) {
        cout << "You find a package near the mailboxes with a familiar scent.\n";
        cat.addItem("Final Map Piece");
    }

    cout << "Go to the fire escape, check mailboxes, or rest?\n";

    while (true) {
        string choice = getChoice();

        if (choice == "fire escape" || choice == "fire" || choice == "escape") {
            fireEscapeScene(cat);
            return;
        }
        else if (choice == "mailboxes" || choice == "mail") {
            cout << "One mailbox has your owner's last name. Apartment 2 feels correct.\n";
            cat.addItem("Apartment 2 Clue");
            cat.changeScore(10);
        }
        else if (choice == "rest") {
            cout << "You rest for a moment and regain strength.\n";
            cat.changeHunger(8);
            fireEscapeScene(cat);
            return;
        }
        else if (choice == "status" || choice == "inventory") {
            statusCheck(cat);
        }
        else {
            printHelp();
        }
    }
}

void fireEscapeScene(Cat& cat) {
    Location fireEscape("Fire Escape", "The metal stairs feel cold under your paws. You see windows for Apartment 1, 2, and 3. You can also climb to the rooftop.");
    fireEscape.printLocation();

    cout << "Choose apartment 1, apartment 2, apartment 3, or rooftop.\n";

    while (true) {
        string choice = getChoice();

        if (choice == "1" || choice == "apartment 1" || choice == "apt 1") {
            apartmentOneScene(cat);
            return;
        }
        else if (choice == "2" || choice == "apartment 2" || choice == "apt 2") {
            apartmentTwoScene(cat);
            return;
        }
        else if (choice == "3" || choice == "apartment 3" || choice == "apt 3") {
            apartmentThreeScene(cat);
            return;
        }
        else if (choice == "rooftop" || choice == "roof") {
            rooftopScene(cat);
            return;
        }
        else if (choice == "status" || choice == "inventory") {
            statusCheck(cat);
        }
        else {
            printHelp();
        }
    }
}

void apartmentOneScene(Cat& cat) {
    Location apt("Apartment 1", "You enter a quiet apartment. It smells clean, but not like home.");
    apt.printLocation();

    cout << "You see a sleeping person. Leave or meow?\n";
    string choice = getChoice();

    if (choice == "meow") {
        wrongApartmentEnding(cat);
    }
    else {
        fireEscapeScene(cat);
    }
}

void apartmentTwoScene(Cat& cat) {
    Location apt("Apartment 2", "The window view feels comforting. The blanket near the sofa smells like your owner.");
    apt.printLocation();
    printDoorArt();

    if (cat.hasItem("Final Map Piece") || cat.hasItem("Apartment 2 Clue")) {
        trueEnding(cat);
    }
    else {
        cout << "It feels close, but you are unsure. You go back to the fire escape.\n";
        fireEscapeScene(cat);
    }
}

void apartmentThreeScene(Cat& cat) {
    Location apt("Apartment 3", "A child sees you and screams, 'Can we keep it?' before you can run.");
    apt.printLocation();
    wrongApartmentEnding(cat);
}

void rooftopScene(Cat& cat) {
    Location roof("Rooftop", "The skyline shines around you. You are high above the streets, but still not inside your home.");
    roof.printLocation();

    cout << "From here, you see Apartment 2 has the same curtains you remember. Climb down or stay?\n";

    while (true) {
        string choice = getChoice();

        if (choice == "climb down" || choice == "down" || choice == "apartment 2") {
            cat.addItem("Apartment 2 Clue");
            apartmentTwoScene(cat);
            return;
        }
        else if (choice == "stay") {
            strayEnding(cat);
            return;
        }
        else if (choice == "status" || choice == "inventory") {
            statusCheck(cat);
        }
        else {
            printHelp();
        }
    }
}

// ENDINGS
// Best ending in the game
void trueEnding(Cat& cat) {
    cout << "\n================ TRUE ENDING ================\n";
    cout << cat.getName() << " scratches the familiar door.\n";
    cout << "Your owner opens it and gasps, 'You came home!'\n";
    cout << "You are safe, fed, and finally home.\n";
    // Final score bonus
    cat.changeScore(50);
    // Show final stats
    cat.showStatus();
    cout << "============================================\n";
}

// Ending where player becomes stray cat
void strayEnding(Cat& cat) {
    cout << "\n================ STRAY ENDING ================\n";
    cout << cat.getName() << " survives the night, but never finds the right door.\n";
    cout << "You become a street-smart NYC stray cat.\n";
    cat.showStatus();
    cout << "==============================================\n";
}

// Ending caused by starvation
void hungerEnding(Cat& cat) {
    cout << "\n================ HUNGER ENDING ================\n";
    cout << cat.getName() << " becomes too hungry and tired to keep traveling.\n";
    cout << "A kind stranger finds you, but you do not make it home tonight.\n";
    cat.showStatus();
    cout << "==============================================\n";
}

// Wrong apartment ending
void wrongApartmentEnding(Cat& cat) {
    cout << "\n============= WRONG APARTMENT ENDING =============\n";
    cout << "You entered the wrong apartment. The people are nice, but they keep you!\n";
    cout << cat.getName() << " gets a new life, but not the original home.\n";
    cat.showStatus();
    cout << "==================================================\n";
}

// Ending where cat becomes bodega cat
void bodegaEnding(Cat& cat) {
    cout << "\n============= BODEGA / DELI CAT ENDING =============\n";
    cout << "You got caught stealing food. The owner decides you are useful for catching mice.\n";
    cout << cat.getName() << " becomes the neighborhood bodega cat.\n";
    cat.showStatus();
    cout << "====================================================\n";
}
