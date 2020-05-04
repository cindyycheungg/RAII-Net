#ifndef ability_hpp
#define ability_hpp

#include <iostream>
#include <string>
#include <sstream>

class Ability {
    std::string name;
    bool isUsed;
public:
    Ability(): name{"NONE"}, isUsed{false} {}
    Ability& operator=(Ability &&a) {
        this->name = a.name;
        this->isUsed = a.isUsed;
      	return *this;
    }
    Ability(std::string newname): name{newname}, isUsed{false} {}
    std::string getName() {
        return name;
    }
    bool canUse() {
        return (!isUsed);
    }
    void useSetter() {
	  isUsed = 1;
    }
};

#endif /* ability_hpp */

