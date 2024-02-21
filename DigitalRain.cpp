/*
    ______
   /\_____\
  _\ \__/_/_
 /\_\ \_____\
 \ \ \/ / / /
  \ \/ /\/ /
   \/_/\/_/

Patryk Milkiewicz
19/02/2024
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <windows.h>
#include "DigitalRain.h"

int DigitalRain::count = 0;

DigitalRain::DigitalRain() : x{ 0 }, y{ 0 }, a{ 'a' } {
#if VERBOSE
    std::cout << "Default constructor" << std::endl;
#endif
    count++;
}

DigitalRain::~DigitalRain() {
#if VERBOSE
    std::cout << "Destructor\n" << std::endl;
#endif
    count--;
}

/*DigitalRain::GoToXY(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}*/