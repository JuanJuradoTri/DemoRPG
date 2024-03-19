#include <iostream>
#include "allclasses.h"

int main() {
    Cleric cler1;
    Rogue rog1;

    std::cout << "Warrior\n"
        << "-MaxHP: " << warr1.getMaxHP() << '\n'
        << "-Strength: " << warr1.getStrength() << '\n'
        << "-Intellect: " << warr1.getIntellect() << '\n';
    std::cout << "Warrior\n"
        << "-MaxHP: " << wiz1.getMaxHP() << '\n'
        << "-Strength: " << wiz1.getStrength() << '\n'
        << "-Intellect: " << wiz1.getIntellect() << '\n';
    std::cout << "Warrior\n"
        << "-MaxHP: " << cler1.getMaxHP() << '\n'
        << "-Strength: " << cler1.getStrength() << '\n'
        << "-Intellect: " << cler1.getIntellect() << '\n';
    std::cout << "Warrior\n"
        << "-MaxHP: " << rog1.getMaxHP() << '\n'
        << "-Strength: " << rog1.getStrength() << '\n'
        << "-Intellect: " << rog1.getIntellect() << '\n';

    return 0;
}
