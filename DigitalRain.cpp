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

Rain::Rain() : x{ 0 }, y{ 0 }, arrP{ 0 }, speed{ 0 },  chars { 'a', 'b', 'c', 'd', 'e' } {
    count++;
}

Rain::Rain(const std::vector<char>& ch) : x{ 0 }, y{ 0 }, arrP{ 0 }, speed{ 0 }, chars { ch } {
    count++;
}

Rain::Rain(int posX, int posY, const std::vector<char>& ch) : x{ posX }, y{ posY }, chars{ ch } {
    count++;
}

Rain::Rain(int posX, int posY, int posA, const std::vector<char>& ch) : x{ posX }, y{ posY }, arrP{ posA }, chars { ch } {
    count++;
}

Rain::Rain(int posX, int posY, int posA, int s, const std::vector<char>& ch) : x{ posX }, y{ posY }, arrP{ posA }, speed{ s }, chars { ch } {
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

Rain::Rain(const Rain& dr) {
    x = dr.x;
    y = dr.y;
    arrP = dr.arrP;
    speed = dr.speed;
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

    for (int x = 0; x <= 209; x += 3) {
        std::vector<char> drop = GenerateRandomChars();
        int s = (rand() % 15);
        raindrops.push_back(Rain(x, (rand() % 48) , 0, s, drop));
        speeds.push_back(s);
    }
}

void Rain::Print(Rain& dr, std::vector<int> speeds) {
    static int i = 0;
    std::vector<char> drop = dr.GetChars();
    static std::vector<int> CurrentSpeed;
    static int SpeedFlag = 0;
    
    if(SpeedFlag == 0){ 
        CurrentSpeed = speeds;
        SpeedFlag = 1;
    }

    
    if (dr.GetArrP() == size(drop)) { dr.SetArrP(0); }
    
    if (dr.GetY() != 49) {
        //if (CurrentSpeed[i] == 0) {
            dr.GoToXY(dr.GetX(), dr.GetY());
            std::cout << drop[dr.GetArrP()];

            dr.GoToXY(dr.GetX(), (dr.GetY() - size(drop)));
            std::cout << ' ';

            dr.SetY(dr.GetY() + 1);
            dr.SetArrP(dr.GetArrP() + 1);
            int x = size(drop);
            CurrentSpeed[i] = dr.GetSpeed();
        //}
        //else if(CurrentSpeed[i] > 0) {
            //CurrentSpeed[i]--;
        //}

    }
    else {
        //if (CurrentSpeed[i] == 0) {
            BottomReached(dr);
            //CurrentSpeed[i] = dr.GetSpeed();
        }
        //else if (CurrentSpeed[i] > 0) { CurrentSpeed[i]--; }
    //}
    
    //i++;
    //if (size(CurrentSpeed) == 51) { i = 0; }
}