//
//  hw05.cpp
//  HW #5 - dynamic memory - reading through file to create nobles and warriors and fight against each other
//
//  Created by Mandy Kong on 2/29/16.
//  Copyright © 2016 Mandy Kong. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class Warrior {
public:
    Warrior(const string& name, const int strength) : warriorName(name), strengthStat(strength) {}
    //accessors to warrior's names
    string getName() const { return warriorName; }
    int getStrength() const { return strengthStat; }
    //when displaying warrior, display name and strength
    void display() const {
        cout << warriorName << ": " << strengthStat << endl;
    }
    //mutator for strength of warrior
    void setStrength(int newStrength) { strengthStat = newStrength; }
private:
    string warriorName;
    int strengthStat;
};
class Noble {
public:
    Noble(const string& name) : nobleName(name), armyStrength(0) {}
    //accessor to noble name
    string getName() const { return nobleName; }
    void hire(Warrior* soldier) {
        //update army strength
        armyStrength += soldier->getStrength();
        //add warrior to army
        army.push_back(soldier);
    }
    Warrior* fire(const string& warrior) {
        Warrior* unemployed = nullptr;
        //check if warrior is in noble's army
        for (size_t i = 0; i < army.size(); ++i) {
            if (army[i]->getName() == warrior) {
                cout << "You don't work for me anymore " << warrior << "! -- " << nobleName << ".\n";
                //if found, remove warrior and subtract strength from armyStrength
                armyStrength -= army[i]->getStrength();
                unemployed = army[i];
                army[i] = army[army.size()-1];
                army.pop_back();
            }
        }
        return unemployed;
    }
    void displayStatus() const {
        cout << nobleName << " has an army of " << army.size() << endl;
        for (Warrior* soldier : army) {
            cout << "\t";
            soldier->display();
        }
    }
    void battle(Noble* enemy) {
        cout << nobleName << " battles " << enemy->nobleName << endl;
        float nobleStrength = armyStrength; //initializing variables to take the noble's army strength
        float enemyStrength = enemy->armyStrength; //and the enemy's army strength
        if (nobleStrength == enemyStrength) {
            if (nobleStrength == 0 && enemyStrength == 0) { //if both the noble's army and the enemy's army already have an army strength of 0, they are both already dead
                cout << "Oh, NO! They're both dead! Yuck!\n";
            }
            else { //if the noble's army strength is the same as the enemy's army strength, they both die
                cout << "Mutual Annihillation: " << nobleName << " and " << enemy->nobleName << " die at each other's hands\n";
                for (size_t i = 0; i < this->army.size(); ++i) {
                    army[i]->setStrength(0); //all warriors of noble's army are dead
                }
                for (size_t i = 0; i < enemy->army.size(); ++i) {
                    enemy->army[i]->setStrength(0); //all warriors of enemy noble's army are dead
                }
                armyStrength = 0;
                enemy->armyStrength = 0;
            }
        }
        else if (nobleStrength > enemyStrength) {
            if (enemyStrength == 0) { //if the enemy strength is 0 that means the enemy is already dead before this battle
                cout << "He's dead " << nobleName << endl;
            }
            else {
                cout << nobleName << " defeats " << enemy->nobleName << endl; //noble army wins against enemy
                for (size_t i = 0; i < enemy->army.size(); ++i) {
                    enemy->army[i]->setStrength(0); //all warriors of enemy noble's army are dead
                }
                enemy->armyStrength = 0;
                armyStrength = 0;
                float damage = enemyStrength / nobleStrength; //calculate the proportion of damage needed to be taken by each warrior of the winner's army
                for (size_t i = 0; i < army.size(); ++i) {
                    float newStrength = army[i]->getStrength() * (1-damage); //going through each warrior and calculating the new strength of the warrior
                    army[i]->setStrength(newStrength); //changing the warrior's strength
                    armyStrength += army[i]->getStrength(); //recalculating new armyStrength
                }
            }
        }
        else if (enemyStrength > nobleStrength) { //same as above but enemy's army wins
            if (nobleStrength == 0) {
                cout << "He's dead, " << enemy->nobleName << endl;
            }
            else {
                cout << enemy->nobleName << " defeats " << nobleName << endl;
                armyStrength = 0;
                enemy->armyStrength = 0;
                for (size_t i = 0; i < army.size(); ++i) {
                    army[i]->setStrength(0); //all warriors of noble's army are dead
                }
                float damage = nobleStrength / enemyStrength;
                for (size_t i = 0; i < enemy->army.size(); ++i) {
                    float newStrength = enemy->army[i]->getStrength() * (1-damage);
                    enemy->army[i]->setStrength(newStrength);
                    enemy->armyStrength += enemy->army[i]->getStrength(); //recalculating enemy's new armyStrength
                }
            }
            
        }
    }
private:
    string nobleName;
    vector<Warrior*> army;
    float armyStrength;
};

//checks if warrior already exist or not
size_t findWarrior(const string& name, vector<Warrior*> warriors) {
    for (size_t i = 0; i < warriors.size(); ++i) {
        if (warriors[i]->getName() == name) { return i; }
    }
    return warriors.size();
}

//checks if noble already exist or not
size_t findNoble(const string& name, vector<Noble*> nobles) {
    for (size_t i = 0; i < nobles.size(); ++i) {
        if (nobles[i]->getName() == name) { return i; }
    }
    return nobles.size();
}

int main() {
    ifstream gameScript;
    gameScript.open("nobleWarriors.txt");
    if (!gameScript) {
        cerr << "File does not exist\n";
        exit(1);
    }
    
    string command, noble, noble2, warrior;
    int strength;
    
    vector<Noble*> nobles;
    vector<Warrior*> unemployedWarriors;
    
    while (gameScript >> command) {
        if (command == "Noble") {
            gameScript >> noble;
            size_t nobleIndex = findNoble(noble, nobles);
            //check if noble is already created on heap
            if (nobleIndex == nobles.size()) { //half open range so if = nobles.size(), didn't exist already
                //create noble on heap
                Noble* player = new Noble(noble);
                //keep track of nobles in vector of pointers to nobles
                nobles.push_back(player);
            }
        }
        else if (command == "Warrior") {
            gameScript >> warrior >> strength;
            //check if warrior is already created on heap
            size_t warriorIndex = findWarrior(warrior, unemployedWarriors);
            if (warriorIndex == unemployedWarriors.size()) {
                //create warrior on heap
                Warrior* soldier = new Warrior(warrior, strength);
                //keep track of "out of work" (able to be hired) warriors in vector of pointers to warriors
                unemployedWarriors.push_back(soldier);
            }
        }
        else if (command == "Hire") {
            gameScript >> noble >> warrior;
            //check if warrior is able to be hired and if noble exists
            size_t nobleIndex = findNoble(noble, nobles);
            size_t warriorIndex = findWarrior(warrior, unemployedWarriors);
            //if noble exists and warrior is unemployed
            if (nobleIndex != nobles.size() && warriorIndex != unemployedWarriors.size()) {
                //hire warrior
                nobles[nobleIndex]->hire(unemployedWarriors[warriorIndex]);
                //remove warrior from unemployed
                unemployedWarriors[warriorIndex] = unemployedWarriors[unemployedWarriors.size()-1];
                unemployedWarriors.pop_back();
            }
        }
        else if (command == "Fire") {
            gameScript >> noble >> warrior;
            size_t nobleIndex = findNoble(noble, nobles);
            if (nobleIndex != nobles.size()) {
                //fire warrior from noble's army
                Warrior* unemployed = nobles[nobleIndex]->fire(warrior);
                //add warrior back to unemployed
                unemployedWarriors.push_back(unemployed);
            }
        }
        else if (command == "Status") {
            cout << "Status\n" << "=====\n" << "Nobles:\n";
            if (nobles.size() == 0) { cout << "NONE\n"; }
            for (Noble* player : nobles) {
                player->displayStatus();
            }
            cout << "Unemployed Warriors:\n";
            if (unemployedWarriors.size() == 0) { cout << "NONE\n"; }
            else {
                for (Warrior* unemployed : unemployedWarriors) {
                    unemployed->display();
                }
            }
        }
        else if (command == "Battle") {
            gameScript >> noble >> noble2;
            size_t nobleIndex = findNoble(noble, nobles);
            size_t nobleIndex2 = findNoble(noble2, nobles);
            //if both nobles exist
            if (nobleIndex != nobles.size() && nobleIndex2 != nobles.size()) {
                nobles[nobleIndex]->battle(nobles[nobleIndex2]);
            }
        }
        else { //command == "Clear"
            for (size_t i = 0; i < nobles.size(); ++i) {
                delete nobles[i];
                nobles[i] = nullptr;
            }
            nobles.clear();
            for (size_t i = 0; i < unemployedWarriors.size(); ++i) {
                delete unemployedWarriors[i];
                unemployedWarriors[i] = nullptr;
            }
            unemployedWarriors.clear();
        }
    }
    
    gameScript.close();
}