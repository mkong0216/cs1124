//
//  hw03.cpp
//  HW #3 - use classes and methods to create a warrior with his weapon, battle other warriors, and print the status of the warriors
//
//  Created by Mandy Kong on 2/17/16.
//  Copyright © 2016 Mandy Kong. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class Weapon {
public:
    Weapon(const string& name, const int strengthStat) : weaponName(name), weaponStrength(strengthStat) {}
    string getName() const { return weaponName; }
    //need accessors to weapon's strength and mutators to change weapon's strength in order for warrior to battle
    int getStrength() const { return weaponStrength; }
    void setStrength(int newStrength) { weaponStrength = newStrength; }
private:
    string weaponName;
    int weaponStrength;
};

class Warrior {
public:
    Warrior(const string& name, const Weapon& weapon): warriorName(name), weapon(weapon) {}
    string getName() const { return warriorName; }
    void displayStatus() {
        cout << "Warrior: " << warriorName << ", weapon: " << weapon.getName() << ", " << weapon.getStrength() << endl;
    }
    void battle(Warrior& player2) {
        if (weapon.getStrength() == player2.weapon.getStrength()) { //if same strength
            if (weapon.getStrength() == 0) { //but both dead
                cout << "Oh, NO! They're both dead! Yuck!\n";
            }
            else { //both players lose
                cout << "Mutual Annihilation: " << warriorName << " and " << player2.warriorName << " die at each other's hands\n";
                weapon.setStrength(0);
                player2.weapon.setStrength(0);
            }
        }
        else if (weapon.getStrength() > player2.weapon.getStrength()) { //player1 will win
            if (player2.weapon.getStrength() == 0) { //if player2 is already dead
                cout << "He's dead, " << warriorName << endl;
            }
            else {
                cout << warriorName << " defeats " << player2.warriorName << endl;
                //player1 loses strength equal to player2's strength
                int newStrength = weapon.getStrength() - player2.weapon.getStrength();
                weapon.setStrength(newStrength);
                //player2 is now dead
                player2.weapon.setStrength(0);
            }
        }
        else { //player2 wins
            if (weapon.getStrength() == 0) { //if player2 already dead
                cout << "He's dead, " << player2.warriorName << endl;
            }
            else {
                cout << player2.warriorName << " defeats " << warriorName << endl;
                //player2 loses strength equal to player1's strength
                int newStrength = player2.weapon.getStrength() - weapon.getStrength();
                player2.weapon.setStrength(newStrength);
                //player1 is dead
                weapon.setStrength(0);
            }
        }
    }
private:
    string warriorName;
    Weapon weapon;
};

//returns index at which warrior is in the vector
//if warrior doesn't exist will return the vector size (half open range)
size_t findWarrior(const string& playerName, vector<Warrior> warriors) {
    for (size_t i = 0; i < warriors.size(); ++i) {
        if (warriors[i].getName() == playerName) {
            return i;
        }
    }
    return warriors.size(); //if can't find it return size of vector
}

int main() {
    ifstream gameScript;
    gameScript.open("warriors.txt");
    if (!gameScript) {
        cerr << "File does not exist\n";
        exit(1);
    }
    
    string command, player1, player2, weaponName;
    int strength;
    vector<Warrior> warriors;
    
    while (gameScript >> command) {
        if (command == "Warrior") {
            gameScript >> player1 >> weaponName >> strength;
            //creates the weapon first and then the warrior
            Weapon weapon(weaponName, strength);
            Warrior player(player1, weapon);
            //adds the warrior into the vector
            warriors.push_back(player);
        }
        else if (command == "Status") {
            cout << "There are " << warriors.size() << " warriors\n";
            for (Warrior players : warriors) {
                players.displayStatus();
            }
        }
        else { //command == "Battle"
            gameScript >> player1 >> player2;
            cout << player1 << " battles " << player2 << endl;
            //find indices of players in vector - check if warriors exist;
            size_t index1 = findWarrior(player1, warriors);
            size_t index2 = findWarrior(player2, warriors);
            if (index1 != warriors.size() && index2 != warriors.size()) {
                warriors[index1].battle(warriors[index2]);
            }
            else { cout << "Warrior does not exist\n"; }
        }
    }
}
