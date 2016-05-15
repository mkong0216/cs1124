//
//  hw02.cpp
//  HW #2 - reading through text file and obeying the command given by text file to create warrior, battle, and print the status of each warrior
//
//  Created by Mandy Kong on 2/2/16.
//  Copyright © 2016 Mandy Kong. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Warrior {
    string name;
    int strength;
};

void createWarrior(const string& player1, int& strengthStat, vector<Warrior>& warriors);

void battleTime(const string& player1, const string& player2, vector<Warrior>& warriors);

void printStatus(vector<Warrior>& warriors);

int main() {
    ifstream gameScript;
    gameScript.open("warriors.txt");
    if (!gameScript) {
        cerr << "The file cannot be opened\n";
        exit(1);
    }
    
    vector<Warrior> warriorList;
    string Command, player1, player2;
    int strengthStat;
    
    while (gameScript >> Command) { //reading first word of each line to determine command
        if (Command == "Warrior") { //if the command is "warrior", continue reading the line to get the name of the warrior and his strength
            gameScript >> player1;
            gameScript >> strengthStat;
            createWarrior(player1, strengthStat, warriorList);
        }
        else if (Command == "Battle") { //if command is "battle", continue reading line for the two warriors that will battle
            gameScript >> player1;
            gameScript >> player2;
            battleTime(player1, player2, warriorList);
        }
        else if (Command == "Status") { //if command is "status", print the warriors and their changed strengths
            printStatus(warriorList);
        }
    }
    
    gameScript.close();
}

void createWarrior(const string& player1, int& strengthStat, vector<Warrior>& warriors) {
    Warrior player; //creating a new warrior with attributes - string name and int strength
    player.name = player1;
    player.strength = strengthStat;
    warriors.push_back(player); //adding new warrior to vector
}

void battleTime(const string& player1, const string& player2, vector<Warrior>& warriors) {
    cout << player1 << " battles " << player2 << endl; //stating which two warriors are battling
    size_t index1 = 0;
    size_t index2 = 0;
    for (size_t index = 0; index < warriors.size(); ++index) {
        if (warriors[index].name == player1) {
            index1 = index;
        }
    }
    for (size_t index = 0; index < warriors.size(); ++index) {
        if (warriors[index].name == player2) {
            index2 = index;
        }
    }
    //looking for player name in vector of warriors
    //keeping index of each player in variable index1 and index2
    
    int outcome1 = warriors[index1].strength - warriors[index2].strength;
    int outcome2 = warriors[index2].strength - warriors[index1].strength;
    //calculating the new health, or strength, of each warrior
    
    
    if (outcome1 <= 0 && outcome2 > 0) { // meaning if player2 had greater strength than player1
        if (warriors[index1].strength == 0) { //if player1 was already dead
            cout << "He's dead, " << player2 << endl;
        }
        else {
            cout << warriors[index2].name << " defeats " << warriors[index1].name << endl;
        }
        warriors[index2].strength = outcome2;
        // subtract damage taken from player1 to get new player2 strength
        warriors[index1].strength = 0; // negative strength automatically is equal to 0
        
    }
    else if (outcome2 <= 0 && outcome1 > 0) { // player1 survived, and player2 is defeated
        if (warriors[index2].strength == 0) { //if player2 was already dead
            cout << "He's dead, " << player1 << endl;
        }
        else {
            cout << warriors[index1].name << " defeats " << warriors[index2].name << endl;
            warriors[index1].strength = outcome1;
            warriors[index2].strength = 0;
        }
    }
    else if (outcome1 == 0 && outcome2 == 0) { // both players die at each other's hands
        if (warriors[index1].strength == 0 && warriors[index2].strength == 0) { //if both players were already dead
            cout << "OH, NO! They're both dead! Yuck!\n";
        }
        else {
            cout << "Mutual Annihilation: " << warriors[index1].name << " and " << warriors[index2].name << " die at each other's hands\n";
        }
        warriors[index1].strength = 0;
        warriors[index2].strength = 0;
    }
}

void printStatus(vector<Warrior>& warriors) {
    cout << "There are: " << warriors.size() << " warriors\n"; //counting how many warriors are in the vector
    for (Warrior& player : warriors) { //going through each warrior in vector and printing out their name and strength 
        cout << "Warrior: " << player.name << ", strength: " << player.strength << endl;
    }
}

