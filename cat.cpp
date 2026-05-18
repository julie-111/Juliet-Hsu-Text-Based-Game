#include "cat.h"

// Default constructor for Cat class
Cat::Cat(string catName) {
    name = catName; // Store the cat's name from user input
    hunger = 55;    // Starting hunger level
    trust = 5;  // Starting trust level
    score = 0;  // Starting score
}

// Getters for Cat class
// const means this function does not change any class data
string Cat::getName() const {
    return name;
}
int Cat::getHunger() const {
    return hunger;
}
int Cat::getTrust() const {
    return trust;
}
int Cat::getScore() const {
    return score;
}

// Function to change hunger level: We'll update hunger and change result between 0 and 100
void Cat::changeHunger(int amount) {
    hunger += amount;   // Add the amount to current hunger

    // Prevent hunger from going above 100
    if (hunger > 100) {
        hunger = 100;
    }
    // Prevent hunger from going below 0
    if (hunger < 0) {
        hunger = 0;
    }
}

// Function to change trust level: We'll update trust and change result between 0 and 100
void Cat::changeTrust(int amount) {
    trust += amount;    // Add amount to current trust

    // Prevent trust from going above 100
    if (trust > 100) {
        trust = 100;
    }
    // Prevent trust from going below 0
    if (trust < 0) {
        trust = 0;
    }
}

// Function to update player score: We'll update score and prevent it from going below 0
void Cat::changeScore(int amount) {
    score += amount;    // Add points to score

    // Prevent negative score
    if (score < 0) {
        score = 0;
    }
}

// We'll check whether a specific item already exists in the inventory
bool Cat::hasItem(string item) const {
    for (int i = 0; i < inventory.size(); i++) {
        if (inventory[i] == item) {
            return true;
        }
    }
    return false;
}

// We'll add an item to the inventory only if player doesn't already have it
void Cat::addItem(string item) {
    if (!hasItem(item)) {
        inventory.push_back(item);
        cout << "\n[Inventory] You got: " << item << "\n";
    }
}

// We'll display the cat's status so the player can track progress
void Cat::showStatus() const {
    cout << "\n========== CAT STATUS ==========\n";
    cout << "Name: " << name << "\n";
    cout << "Hunger: " << hunger << "/100\n";
    cout << "Trust: " << trust << "/100\n";
    cout << "Score: " << score << "\n";

    cout << "Inventory: ";
    if (inventory.size() == 0) {
        cout << "Empty";
    }
    else {
        for (int i = 0; i < inventory.size(); i++) {
            cout << inventory[i];
            if (i + 1 < inventory.size()) {
                cout << ", ";
            }
        }
    }

    cout << "\n================================\n";
}
