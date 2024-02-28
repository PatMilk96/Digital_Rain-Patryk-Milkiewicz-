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

Rain::Rain() : x{ 0 }, y{ 0 }, chars{ 'a', 'b', 'c', 'd', 'e' } {
    count++;
}

Rain::Rain(const std::vector<char>& ch) : x{ 0 }, y{ 0 }, chars{ ch } {
    count++;
}

Rain::Rain(int posX, int posY, const std::vector<char>& ch) : x{ posX }, y{ posY }, chars{ ch } {
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

void Print(Rain& dr) {
    int i;
    dr.GoToXY(0, i);
    std::cout << dr.GetChars();
    /*if (j == size(test)) { j = 0; }

    dr.GoToXY(0, i);

    std::cout << test[j];

    dr.GoToXY(0, i - x);

    std::cout << ' ';

    Sleep(75);*/
}