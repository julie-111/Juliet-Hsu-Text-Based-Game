#ifndef CAT_H
#define CAT_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Cat class stores all player information and actions
class Cat {
private:
    string name;
    int hunger;
    int trust;
    int score;
    vector<string> inventory;

public:
    // Default cat name is "Mochi" if player does not choose one
    Cat(string catName = "Mochi");

    string getName() const;
    int getHunger() const;
    int getTrust() const;
    int getScore() const;

    // Functions to update player status
    void changeHunger(int amount);
    void changeTrust(int amount);
    void changeScore(int amount);

    // Checks whether player already has an item
    bool hasItem(string item) const;

    // Adds an item to the player's inventory
    void addItem(string item);

    // Displays the player's current status
    void showStatus() const;
};

#endif


