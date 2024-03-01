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

Rain::Rain() : x{ 0 }, y{ 0 }, arrP{ 0 }, chars { 'a', 'b', 'c', 'd', 'e' } {
    count++;
}

Rain::Rain(const std::vector<char>& ch) : x{ 0 }, y{ 0 }, arrP{ 0 }, chars { ch } {
    count++;
}

Rain::Rain(int posX, int posY, const std::vector<char>& ch) : x{ posX }, y{ posY }, chars{ ch } {
    count++;
}

Rain::Rain(int posX, int posY, int posA, const std::vector<char>& ch) : x{ posX }, y{ posY }, arrP{ posA }, chars { ch } {
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

Rain::Rain(const Rain& dr) {
    x = dr.x;
    y = dr.y;
    arrP = dr.arrP;
    chars = dr.chars;
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

void Rain::Init(std::vector<Rain>& raindrops) {
    raindrops.push_back(Rain(0, 0, 0, { 'a', 'b', 'c' }));
    raindrops.push_back(Rain(5, 0, 0, { 'h', 'v', 'k', 'q', 'b' }));
    raindrops.push_back(Rain(10, 0, 0, { 'i', 'o', 'm', 'e' }));
    raindrops.push_back(Rain(15, 0, 0, { 'y', 'z', 's', 'x', 'u', 'g', 'a' }));
    raindrops.push_back(Rain(20, 0, 0, { 'a', 'u', 'e', 'k', 'b', 'h' }));
    raindrops.push_back(Rain(25, 0, 0, { 'g', 'b', 'h', 't', 'e', 't', 'x', 'r', 'q', 'l' }));
}

void Rain::Print(Rain& dr) {
    std::vector<char> drop = dr.GetChars();
    if (dr.GetArrP() == size(drop)) { dr.SetArrP(0); }
    dr.GoToXY(dr.GetX() , dr.GetY());
    std::cout << drop[dr.GetArrP()];

    dr.GoToXY(dr.GetX(), (dr.GetY() - size(drop)));
    std::cout << ' ';
    
    Sleep(50);  //Here I will add a GetSpeed() function and add a delay of whatever the speed is

    dr.SetY(dr.GetY() + 1);  
    dr.SetArrP(dr.GetArrP() + 1);
  
}