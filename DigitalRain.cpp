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



Rain::Rain(Rain& dr) {
    x = dr.x;
    y = dr.y;
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

void Rain::Init() {
    Rain dr2(15, 15, 0, { 'a', 'b', 'c', 'd', 'e' });
    Print(dr2);

    //Here I want to send the drops to a sorting function
    //that will iterate through a vector of objects, sending them 1 by one to the Print algo
}

void Rain::Print(Rain& dr) {
    std::vector<char> drop = dr.GetChars();
    if (arrP == size(drop)) { arrP = 0; }
    dr.GoToXY(15, y);
    std::cout << drop[arrP];
    dr.GoToXY(15, y - size(drop));
    std::cout << ' ';
    Sleep(150);

    y++;
    arrP++;
    Print(dr);
}