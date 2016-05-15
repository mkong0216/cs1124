//
//  hw04.cpp
//  HW #4 - nobles fight against each other using their own army of warriors
//
//  Created by Mandy Kong on 2/23/16.
//  Copyright © 2016 Mandy Kong. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
using namespace std;


class Warrior {
public:
    Warrior(const string& Name, float strength) : warriorName(Name), warriorStrength(strength) {}
    //initializes the name and strength of warrior
    string getName () const { //accessor the name of warrior
        return warriorName;
    }
    float getStrength() const { //strength might end up a float so accessor is strength of warrior is type float
        return warriorStrength;
    }
    
    void changeStrength(float strength) { //mutator to change strength of each warrior when battling
        warriorStrength = strength;
    }
private:
    string warriorName;
    float warriorStrength;
};

class Noble {
public:
    Noble (const string& Name, float totalStrength = 0) : nobleName(Name), armyStrength(totalStrength) {}
    //initializes name of noble, and the strength of the army as 0 -> will add up strengths later
    
    void hire(Warrior& soldier) {
        armyStrength += soldier.getStrength(); //adding strength of each warrior going into vector to get total army strength
        army.push_back(&soldier);
    }
    
    float getArmyStrength() const { return armyStrength; }
    
    void changeArmyStrength() {
        armyStrength = 0;
        for (Warrior* armyPointer : army) {
            armyStrength += armyPointer->getStrength(); //recalculating army strength after each warrior's strength is changed
            //there might be a better way to do this - not sure how yet
        }
    }
    
    void display() const { //display() needs to state how many warriors noble has in his army and list warriors' names and strengths
        cout << nobleName << " has an army of " << army.size() << endl;
        for (Warrior* armyPointer : army) {
            cout << "\t" << armyPointer->getName() << ": " << armyPointer->getStrength() << endl;
        }
    }
    
    void fire(Warrior& soldier) { //firing a warrior means the warrior needs to be removed from the vector and the army strength needs to be recalculated by subtracting the fired warrior's strength
        for (size_t i = 0; i < army.size(); ++i) {
            if (army[i]->getName() == soldier.getName()) {
                armyStrength -= army[i]->getStrength();
                army[i] = army[army.size()-1]; //warrior being fired replaced by copy of last warrior in vector
                army.pop_back(); //remove last warrior
            }
        }
        cout << soldier.getName() << ", you're fired! -- " << nobleName << endl;
    }
    
    void battle(Noble& enemy) {
        cout << nobleName << " battles " << enemy.nobleName << endl;
        float nobleStrength = armyStrength; //initializing variables to take the noble's army strength
        float enemyStrength = enemy.armyStrength; //and the enemy's army strength
        if (nobleStrength == enemyStrength) {
            if (nobleStrength == 0 && enemyStrength == 0) { //if both the noble's army and the enemy's army already have an army strength of 0, they are both already dead
                cout << "Oh, NO! They're both dead! Yuck!\n";
            }
            else { //if the noble's army strength is the same as the enemy's army strength, they both die
                cout << "Mutual Annihillation: " << nobleName << " and " << enemy.nobleName << " die at each other's hands\n";
                for (size_t i = 0; i < this->army.size(); ++i) {
                    this->army[i]->changeStrength(0); //all warriors of noble's army are dead
                }
                for (size_t i = 0; i < enemy.army.size(); ++i) {
                    enemy.army[i]->changeStrength(0); //all warriors of enemy noble's army are dead
                }
                this->changeArmyStrength();
                enemy.changeArmyStrength();
            }
        }
        else if (nobleStrength > enemyStrength) {
            if (enemyStrength == 0) { //if the enemy strength is 0 that means the enemy is already dead before this battle
                cout << "He's dead " << nobleName << endl;
            }
            else {
                cout << nobleName << " defeats " << enemy.nobleName << endl; //noble army wins against enemy
                for (size_t i = 0; i < enemy.army.size(); ++i) {
                    enemy.army[i]->changeStrength(0); //all warriors of enemy noble's army are dead
                }
                enemy.changeArmyStrength();
                float damage = enemyStrength / nobleStrength; //calculate the proportion of damage needed to be taken by each warrior of the winner's army
                for (size_t i = 0; i < this->army.size(); ++i) {
                    float newStrength = this->army[i]->getStrength() * (1-damage); //going through each warrior and calculating the new strength of the warrior
                    this->army[i]->changeStrength(newStrength); //changing the warrior's strength
                }
                this->changeArmyStrength(); //recalculating the army's strength
            }
        }
        else if (enemyStrength > nobleStrength) { //same as above but enemy's army wins
            if (nobleStrength == 0) {
                cout << "He's dead " << enemy.nobleName << endl;
            }
            else {
                cout << enemy.nobleName << " defeats " << nobleName << endl;
                this->armyStrength = 0;
                for (size_t i = 0; i < this->army.size(); ++i) {
                    this->army[i]->changeStrength(0); //all warriors of noble's army are dead
                }
                float damage = nobleStrength / enemyStrength;
                for (size_t i = 0; i < enemy.army.size(); ++i) {
                    float newStrength = enemy.army[i]->getStrength() * (1-damage);
                    enemy.army[i]->changeStrength(newStrength);
                    enemy.changeArmyStrength();
                }
            }
            
        }
    }
private:
    string nobleName;
    vector<Warrior*> army;
    float armyStrength;
};

int main() {
    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");
    
    Warrior cheetah("Tarzan", 10);
    Warrior wizard("Merlin", 15);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);
    
    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(wizard);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(cheetah);
    
    jim.display();
    lance.display();
    art.display();
    linus.display();
    billie.display();
    
    art.fire(cheetah);
    art.display();
    
    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);
}
