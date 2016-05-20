//
//  Warrior.cpp
//  HW #7
//
//  Created by Mandy Kong on 3/25/16.
//  Copyright © 2016 Mandy Kong. All rights reserved.
//

#include "Warrior.hpp"
#include "Noble.hpp"
#include <iostream>
#include <string>
using namespace std;

namespace WarriorCraft {
    Warrior::Warrior(const string& name, float strength): warriorName(name), warriorStrength(strength) {}
    void Warrior::display() const {
        cout << "\t" << warriorName << ": " << warriorStrength << endl;
    }
    Noble* Warrior::getNobleBoss() { return nobleBoss; }
    void Warrior::setNobleBoss(Noble* boss) {
        nobleBoss = boss;
    }
    float Warrior::getStrength() const { return warriorStrength; }
    void Warrior::setNewStrength(const float& newStrength) {
        warriorStrength = newStrength;
    }
    void Warrior::runaway() {
        cout << warriorName << " flees in terror, abandoning his lord, " << nobleBoss->getName() << endl;
        nobleBoss->runawaySoldier(this);
        nobleBoss = nullptr;
    }
}
