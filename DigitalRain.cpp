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

Rain::Rain() : x{ 0 }, y{ 0 }, arrP{ 0 }, speed{ 0 }, vectorPos{ 0 }, chars{ 'a', 'b', 'c', 'd', 'e' } {
    count++;
}

Rain::Rain(const std::vector<char>& ch) : x{ 0 }, y{ 0 }, arrP{ 0 }, speed{ 0 }, chars{ ch } {
    count++;
}

Rain::Rain(int posX, int posY, const std::vector<char>& ch) : x{ posX }, y{ posY }, chars{ ch } {
    count++;
}

Rain::Rain(int posX, int posY, int posA, const std::vector<char>& ch) : x{ posX }, y{ posY }, arrP{ posA }, chars{ ch } {
    count++;
}

Rain::Rain(int posX, int posY, int posA, int s, const std::vector<char>& ch) : x{ posX }, y{ posY }, arrP{ posA }, speed{ s }, chars{ ch } {
    count++;
}

Rain::Rain(int posX, int posY, int posA, int s, int vectPos, const std::vector<char>& ch) : x{ posX }, y{ posY }, arrP{ posA }, speed{ s }, vectorPos{ vectPos }, chars{ ch } {
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

void Rain::SetChars(const std::vector<char>& ch) {
    chars = ch;
}

Rain::Rain(const Rain& dr) {
    x = dr.x;
    y = dr.y;
    arrP = dr.arrP;
    speed = dr.speed;
    chars = dr.chars;
    vectorPos = dr.vectorPos;
    count++;
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


std::vector<char> Rain::GenerateRandomChars() {
    int size = rand() % 35 + 20; // Random size between 20 and 55
    std::vector<char> randomChars(size);

    for (int i = 0; i < size; ++i) {
        randomChars[i] = 'a' + rand() % 26; // Random lowercase letter
    }

    return randomChars;
}

int Rain::ScreenSize(int x) {
    const HWND hDesktop = GetDesktopWindow();
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    if (x == 0) {
        int baseWidth = r.right - r.left;
        //current config we have 70 objects and the screen size it fits in is width: 1714 height: 1170........meaning........ for width 1714 / 70 = 24.48571428571...... so for every object I need to move by this much 24.48571428571 ~ 25 pixels......... or I have 25 pixels to assign to each object
        int width = ((baseWidth / 23) * 3); //this calculation return the amount of objects that I can have on the screen given the screen size
        return width;
    }
    else if (x == 1) {
        //same as above: 1170/49 = 23.87 ~ 24
        int baseHeight = r.bottom - r.top;
        int height = ((baseHeight / 84) * 5);
        return height;
    }
}


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
    //int Rain::ScreenSize(int)   this function will accept an int, will be either 1 or 0. If 1 then return width, if 0 return length
    int width = ScreenSize(0);
    int height = ScreenSize(1);

    for (int x = 0; x <= width; x += 2) {
        std::vector<char> drop = GenerateRandomChars();
        int s = (rand() % 100 + 75);
        raindrops.push_back(Rain(x, (rand() % height), 0, s, v, drop));
        speeds.push_back(s);
        v++;
    }
}

void Rain::Print(Rain& dr, std::vector<int> speeds) {
    std::vector<char> drop = dr.GetChars();
    static std::vector<int> SpeedsCopy;
    static int SpeedFlag = 0;
    static int height;

    if (SpeedFlag == 0) {
        SpeedsCopy = speeds;
        height = ScreenSize(1);
        SpeedFlag = 1;
    }


    if (dr.GetArrP() == size(drop)) { dr.SetArrP(0); }

    if (dr.GetY() != height) {
        if (dr.GetSpeed() == 0) {
            dr.GoToXY(dr.GetX(), dr.GetY());
            std::cout << drop[dr.GetArrP()];

            dr.GoToXY(dr.GetX(), (dr.GetY() - size(drop)));
            std::cout << ' ';

            dr.SetY(dr.GetY() + 1);
            dr.SetArrP(dr.GetArrP() + 1);
            dr.SetSpeed(SpeedsCopy[dr.GetVectorPos()]);
        }
        else if (dr.GetSpeed() > 0) {
            dr.SetSpeed((dr.GetSpeed() - 1));
        }

    }
    else {
        if (dr.GetSpeed() == 0) {
            BottomReached(dr);
            dr.SetSpeed(SpeedsCopy[dr.GetVectorPos()]);
            if (size(drop) == 1) {
                dr.SetSpeed(rand() % 100 + 75);
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