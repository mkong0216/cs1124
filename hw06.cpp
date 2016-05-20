//
//  main.cpp
//  HW #6 - Using inheritance to expand on nobles and protectors game 
//
//  Created by Mandy Kong on 5/15/16.
//  Copyright © 2016 Mandy Kong. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Nobles {
public:
    Nobles(const string name, float strength = 0) : nobleName(name), strengthStat(strength), isDead(false) {}
    string getName() const { return nobleName; }
    virtual void loseStrength(float strength) = 0;
    virtual void battle(Nobles& enemy) {
        cout << nobleName << " battles " << enemy.nobleName << endl;
        float nobleStrength = strengthStat;
        float enemyStrength = enemy.strengthStat;
        if (strengthStat == enemy.strengthStat) {
            //if they're both already dead
            if (isDead == true && enemy.isDead == true) {
                cout << "Oh, NO! They're both dead! Yuck!\n";
            }
            //else if they have the same strength - mutal destruction
            else {
                this->loseStrength(enemyStrength);
                enemy.loseStrength(nobleStrength);
                isDead = true;
                enemy.isDead = true;
                cout << "Mutual Anniilation: " << nobleName << " and " << enemy.nobleName << " die at each other's hands\n";
            }
        }
        else if (strengthStat > enemy.strengthStat) { //if noble wins against enemy
            //check if enemy is already dead
            if (enemy.isDead == true) {
                cout << "He's dead, " << nobleName << endl;
            }
            else {
                this->loseStrength(enemyStrength);
                enemy.loseStrength(nobleStrength);
                enemy.isDead = true;
                cout << nobleName << " defeats " << enemy.nobleName << endl;
            }
        }
        else if (enemy.strengthStat > strengthStat) { //enemy wins against noble
            if (isDead == true) { //noble already dead
                cout << "He's dead, " << enemy.nobleName << endl;
            }
            else {
                this->loseStrength(enemyStrength);
                enemy.loseStrength(nobleStrength);
                isDead = true;
                cout << enemy.nobleName << " defeats " << nobleName << endl;
            }
        }
    }
protected:
    string nobleName;
    float strengthStat;
    bool isDead;
};

class Protectors {
public:
    Protectors(const string name, float strength) : protectorName(name), protectorStrength(strength), nobleBoss(nullptr) {}
    Nobles* getNobleBoss() const { return nobleBoss; }
    virtual void setStrength(float strength) { protectorStrength = strength; }
    virtual void defend() const = 0;
    float getStrength() const { return protectorStrength; }
    void setNobleBoss(Nobles* boss) { nobleBoss = boss; }
protected:
    string protectorName;
    float protectorStrength;
    Nobles* nobleBoss;
};

class PersonWithStrengthToFight : public Nobles {
public:
    PersonWithStrengthToFight(const string name, const float strength) : Nobles(name, strength) {}
    virtual void loseStrength(float strength) {
        strengthStat -= strength;
        if (strengthStat < 0) { strengthStat = 0; }
    }
};

class Lord : public Nobles {
public:
    Lord(const string& name) : Nobles(name) {}
    void hires(Protectors& soldier) {
        //if noble isn't dead yet and protector isn't hired yet
        if (isDead != true && soldier.getNobleBoss() == nullptr) {
            army.push_back(&soldier); //add soldier to army
            strengthStat += soldier.getStrength(); //update strength of army
            soldier.setNobleBoss(this); //soldier's boss is now noble
        }
    }
    virtual void loseStrength(float strength) {
        for (Protectors* soldier : army) {
            soldier->defend();
        }
        if (strength == strengthStat) { //mutual annihilation
            for (size_t i = 0; i < army.size(); ++i) {
                army[i]->setStrength(0);
                army[i] = nullptr;
            }
            strengthStat = 0; 
        }
        else if (strengthStat > strength) { //noble wins against enemy
            float damage = strength / strengthStat;
            strengthStat = 0; //recalculate new army strength 
            for (size_t i = 0; i < army.size(); ++i) {
                float newStrength = army[i]->getStrength() * (1-damage); //calculating new strength of warrior
                army[i]->setStrength(newStrength);
                //adding new strength;
                strengthStat += army[i]->getStrength();
            }
        }
        else if (strength > strengthStat) { //enemy wins against noble
            for (size_t i = 0; i < army.size(); ++i) {
                army[i]->setStrength(0);
                army[i] = nullptr;
            }
            strengthStat = 0;
        }
    }
private:
    vector<Protectors*> army;
};
    
class Wizard : public Protectors {
public:
    Wizard(const string name, float strength) : Protectors(name, strength) {}
    void defend() const { cout << "POOF!\n"; }
};
    
class Warrior : public Protectors {
public:
    Warrior(const string name, float strength) : Protectors(name, strength) {}
    virtual void defend() const = 0;
};

class Archer : public Warrior {
public:
    Archer(const string name, float strength) : Warrior(name, strength) {}
    void defend() const {
        cout << "TWANG! " << protectorName << " says: Take that in the name of my lord, " << nobleBoss->getName() << endl;
    }
};
    
class Swordsman : public Warrior {
public:
    Swordsman(const string name, float strength) : Warrior(name, strength) {}
    void defend() const {
        cout << "CLANG! " << protectorName << " says: Take that in the name of my lord, " << nobleBoss->getName() << endl;
    }
};

int main() {
    Lord sam("Sam");
    Archer samantha("Samantha", 200);
    sam.hires(samantha);
    Lord joe("Joe");
    PersonWithStrengthToFight randy("Randolf the Elder", 250);
    joe.battle(randy);
    joe.battle(sam);
    Lord janet("Janet");
    Swordsman hardy("TuckTuckTheHardy", 100);
    Swordsman stout("TuckTuckTheStout", 80);
    janet.hires(hardy);
    janet.hires(stout);
    PersonWithStrengthToFight barclay("Barclay the Bold", 300);
    janet.battle(barclay);
    janet.hires(samantha);
    Archer pethora("Pethora", 50);
    Archer thora("Thorapleth", 60);
    Wizard merlin("Merlin", 150);
    janet.hires(pethora);
    janet.hires(thora);
    sam.hires(merlin);
    janet.battle(barclay);
    sam.battle(barclay);
    joe.battle(barclay);
}