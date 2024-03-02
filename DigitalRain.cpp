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
    srand(time(0));

    for (int x = 0; x <= 200; x += 4) {
        std::vector<char> drop = GenerateRandomChars();
        raindrops.push_back(Rain(x, (rand() % 35), 0, drop));
    }
}

void Rain::Print(Rain& dr) {
    std::vector<char> drop = dr.GetChars();
    if (dr.GetArrP() == size(drop)) { dr.SetArrP(0); }

    if (dr.GetY() != 48) {
        dr.GoToXY(dr.GetX(), dr.GetY());
        std::cout << drop[dr.GetArrP()];

        dr.GoToXY(dr.GetX(), (dr.GetY() - size(drop)));
        std::cout << ' ';

        dr.SetY(dr.GetY() + 1);
        dr.SetArrP(dr.GetArrP() + 1);
        int x = size(drop);
    }
    else {
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
  
}