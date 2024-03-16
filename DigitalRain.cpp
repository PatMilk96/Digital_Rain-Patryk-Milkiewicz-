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


int Rain::count = 0;

Rain::Rain() : x{ 0 }, y{ 0 }, arrP{ 0 }, speed{ 0 }, vectorPos{ 0 },  chars { 'a', 'b', 'c', 'd', 'e' } {
    count++;
}

Rain::Rain(int posX, int posY, int posA, int s, int vectPos, const std::vector<char>& ch) : x{ posX }, y{ posY }, arrP{ posA }, speed{ s }, vectorPos{ vectPos }, chars { ch } {
    count++;
}

Rain::~Rain() {
    count--;
}


void Rain::SetY(int posY) {
    y = posY;
}

void Rain::SetX(int posX) {
    x = posX;
}

void Rain::SetArrP(int posA) {
    arrP = posA;
}

void Rain::SetSpeed(int s) {
    speed = s;
}

void Rain::SetVectorPos(int v) {
    vectorPos = v;
}

Rain::Rain(const Rain& dr) {
    x = dr.x;
    y = dr.y;
    arrP = dr.arrP;
    speed = dr.speed;
    chars = dr.chars;
    vectorPos = dr.vectorPos;
}

void Rain::SetChars(const std::vector<char>& ch) {
    chars = ch;
}

void Rain::GoToXY(int x, int y) const {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

std::ostream& operator<<(std::ostream& output, const Rain& dr) {

    for (auto& r : dr.GetChars())
        output << r << std::endl;
    return output;
}


/*##############################################################################*/


void Rain::BottomReached(Rain& dr) {
    std::vector<char> drop = dr.GetChars();
    int x = size(drop);
    dr.GoToXY(dr.GetX(), (dr.GetY() - size(drop)));
    std::cout << ' ';
    drop.pop_back();
    dr.SetChars(drop);
    if (size(drop) == 0) {
        dr.SetChars(GenerateRandomChars());
        dr.SetY(0);

    }
}

void Rain::Init(std::vector<Rain>& raindrops, std::vector<int>& speeds) {
    srand(time(0));
    int v = 0;
    for (int x = 0; x <= 209; x += 3) {
        std::vector<char> drop = GenerateRandomChars();
        int s = (rand() % 500 + 200);
        raindrops.push_back(Rain(x, (rand() % 48) , 0, s, v, drop));
        speeds.push_back(s);
        v++;
    }
}

void Rain::Print(Rain& dr, std::vector<int> speeds) {
    static int i = 0;
    std::vector<char> drop = dr.GetChars();
    static std::vector<int> SpeedsCopy;
    static int SpeedFlag = 0;
    
    if(SpeedFlag == 0){ 
        SpeedsCopy = speeds;
        SpeedFlag = 1;
    }

    
    if (dr.GetArrP() == size(drop)) { dr.SetArrP(0); }
    
    if (dr.GetY() != 49) {
        if (dr.GetSpeed() == 0) {
            dr.GoToXY(dr.GetX(), dr.GetY());
            std::cout << drop[dr.GetArrP()];

            dr.GoToXY(dr.GetX(), (dr.GetY() - size(drop)));
            std::cout << ' ';

            dr.SetY(dr.GetY() + 1);
            dr.SetArrP(dr.GetArrP() + 1);
            dr.SetSpeed(SpeedsCopy[dr.GetVectorPos()]);
        }
        else if(dr.GetSpeed() > 0) {
            dr.SetSpeed((dr.GetSpeed()-1));
        }

    }
    else {
        if (dr.GetSpeed() == 0) {
            BottomReached(dr);
            dr.SetSpeed(SpeedsCopy[dr.GetVectorPos()]);
            if (size(drop) == 1) {
                dr.SetSpeed(rand() % 500 + 200);
                SpeedsCopy[dr.GetVectorPos()] = dr.GetSpeed();
            }
        }
        else if (dr.GetSpeed() > 0) {
            dr.SetSpeed((dr.GetSpeed() - 1));
        }
    }
}


//copy speeds in another vector and do not change them, this vector will only be used to copy the speed into the droplet object, I will decrement the droplets speed in order to avoid my previous
//problem where droplets were out of sync because I was decrementing the copy vector of speeds. I need to know the position of the droplet in the vector and then just copy the speed from my copy
//speeds vector into my droplet object

//create a speed vector in my print class, when my vector reaches the end then just skip to the next vector if that vector the goes back to pos == 0 then don't skip it ?.... so if(pos(Y) == 49) skip