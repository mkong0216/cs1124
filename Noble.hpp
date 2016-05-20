//
//  Noble.hpp
//  HW #7
//
//  Created by Mandy Kong on 3/25/16.
//  Copyright © 2016 Mandy Kong. All rights reserved.
//

#ifndef Noble_hpp
#define Noble_hpp

#include <iostream>
#include <string>
#include <vector>

namespace WarriorCraft {
    class Warrior;
    
    class Noble {
        friend std::ostream& operator<<(std::ostream& os, const Noble& noble);
    public:
        Noble(const std::string& name);
        void display() const;
        std::string getName() const;
        bool alreadyHiredWarrior(Warrior& soldier);
        bool deadNoble(Noble& noble);
        void recalculateArmyStrength();
        void hire(Warrior& soldier);
        void battle(Noble& nobleEnemy);
        void fire(Warrior& soldier);
        void runawaySoldier(Warrior* soldier);
    private:
        std::string nobleName;
        std::vector<Warrior*> army;
        float armyStrength = 0;
    };
}

#endif /* Noble_hpp */
