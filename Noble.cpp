//
//  Noble.cpp
//  HW #7
//
//  Created by Mandy Kong on 3/25/16.
//  Copyright © 2016 Mandy Kong. All rights reserved.
//

#include "Noble.hpp"
#include "Warrior.hpp"

#include <iostream>
#include <string>
#include <vector>
using namespace std;

namespace WarriorCraft {
    Noble::Noble(const string& name) : nobleName(name) {}
    void Noble::display() const {
        cout << nobleName << " has an army of " << army.size() << endl;
        for (Warrior* soldier : army) {
            soldier->display();
        }
    }
    
    string Noble::getName() const { return nobleName; }

    bool Noble::alreadyHiredWarrior(Warrior& soldier) {
        return soldier.getNobleBoss() != nullptr; //returns TRUE if nobleBoss != nullptr (meaning already hired)
    }
    
    bool Noble::deadNoble(Noble& noble) {
        return noble.army.size() > 0 && noble.armyStrength == 0; //returns TRUE if noble's army strength = 0 (meaning noble and his soldiers are dead)
    }
    
    void Noble::recalculateArmyStrength() {
        armyStrength = 0;
        for (Warrior* soldier : army) {
            armyStrength += soldier->getStrength();
        }
    }
    
    void Noble::hire(Warrior& soldier) {
        if (alreadyHiredWarrior(soldier) == false){
            soldier.setNobleBoss(this);
            armyStrength += soldier.getStrength();
            army.push_back(&soldier);
        }
    }
    void Noble::battle(Noble& nobleEnemy){
        cout << nobleName << " battles " << nobleEnemy.nobleName << endl;
        float nobleStrength = armyStrength;
        float enemyStrength = nobleEnemy.armyStrength;
        if (nobleStrength == enemyStrength) {
            if (deadNoble(*this) == true) {
                cout << "Oh, NO! They're both dead! Yuck! \n";
            }
            else {
                cout << "Mutual Annihilation: " << nobleName << " and " << nobleEnemy.nobleName << " die at each other's hands\n";
                for (size_t i = 0; i < army.size(); ++i) {
                    army[i]->setNewStrength(0);
                }
                recalculateArmyStrength();
                for (size_t j = 0; j < nobleEnemy.army.size(); ++j) {
                    nobleEnemy.army[j]->setNewStrength(0);
                }
                nobleEnemy.recalculateArmyStrength();
            }
        }
        else if (nobleStrength > enemyStrength) { //noble wins against enemy
            if (deadNoble(nobleEnemy) == true) { //if noble wins because enemy is already dead
                cout << "He's dead, " << nobleName << endl;
            }
            else {
                cout << nobleName << " defeats " << nobleEnemy.nobleName << endl;
                for (size_t i = 0; i < nobleEnemy.army.size(); ++i) {
                    nobleEnemy.army[i]->setNewStrength(0);
                }
                nobleEnemy.recalculateArmyStrength();
                float damage = enemyStrength / nobleStrength;
                for (size_t j = 0; j < army.size(); ++j) {
                    float newStrength = army[j]->getStrength() * (1 - damage);
                    army[j]->setNewStrength(newStrength);
                }
                recalculateArmyStrength();
            }
        }
        else if (nobleStrength < enemyStrength) { //enemy wins against noble
            if (deadNoble(*this)==true) { //if enemy wins because noble is already dead
                cout << "He's dead, " << nobleEnemy.nobleName << endl;
            }
            else {
                cout << nobleEnemy.nobleName << " defeats " << nobleName << endl;
                for (size_t i = 0; i < army.size(); ++i) {
                    army[i]->setNewStrength(0);
                }
                recalculateArmyStrength();
                float damage = nobleStrength / enemyStrength;
                for (size_t j = 0; j < nobleEnemy.army.size(); ++j) {
                    float newStrength = nobleEnemy.army[j]->getStrength() * (1-damage);
                    nobleEnemy.army[j]->setNewStrength(newStrength);
                }
                nobleEnemy.recalculateArmyStrength();
            }
        }
        
    }
    
    void Noble::fire(Warrior& soldier) {
        for (size_t i = 0; i < army.size(); ++i) {
            if (army[i] == &soldier) {
                cout << army[i]->getName() << ", you're fired! -- " << nobleName << endl;
                army[i]->setNobleBoss(nullptr);
                army[i] = army[army.size() - 1];
                army.pop_back();
            }
        }
    }
    
    void Noble::runawaySoldier(Warrior* soldier) {
        for (size_t i = 0; i < army.size(); ++i) {
            if (army[i] == soldier) {
                army[i] = army[army.size()-1];
                army.pop_back();
            }
        }
        recalculateArmyStrength();
    }
    
    ostream& operator<<(ostream& os, const Noble& noble) {
        noble.display();
        return os;
    }
    
}