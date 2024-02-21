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

#ifndef DIGITALRAIN_H
#define DIGITALRAIN_H

#include <iostream>
#include <vector>
#include <string>

#define VERBOSE 1

class DigitalRain {
public:
    DigitalRain();
    ~DigitalRain();
    //DigitalRain(int);
    //DigitalRain(int, int);
    //DigitalRain(int, int, char);

private:
    int x;
    int y;
    char a;

    static int count;
};

std::ostream& operator<<(std::ostream& output, const DigitalRain& p);

#endif