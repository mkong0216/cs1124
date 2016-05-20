//
//  Warrior.hpp
//  HW #7
//
//  Created by Mandy Kong on 3/25/16.
//  Copyright © 2016 Mandy Kong. All rights reserved.
//

#ifndef Warrior_hpp
#define Warrior_hpp

#include <iostream>
#include <string>

namespace WarriorCraft {
    class Noble;
    
    class Warrior {
    public:
        Warrior(const std::string& name, float strength);
        void display() const;
        Noble* getNobleBoss();
        void setNobleBoss(Noble* boss);
        float getStrength() const;
        void setNewStrength(const float& newStrength);
        std::string getName() const { return warriorName; }
        void runaway();
    private:
        std::string warriorName;
        float warriorStrength;
        Noble* nobleBoss = nullptr;
    };
}

#endif /* Warrior_hpp */
