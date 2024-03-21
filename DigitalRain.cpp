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


void Rain::SetSpeeds(const std::vector<int>& sp) {
    int width = ScreenSize(0);
    width = width / 2;
    int sp1, sp2;

    sp1 = (-9 * width) + 1554;
    sp2 = (-6.33 * width) + 1038;


    for (int i = 0; i < width; ++i) {
        speeds.push_back(rand() % sp1 + sp2);
    }
}

std::vector<char> Rain::GenerateRandomChars() {

    int size = rand() % int(ScreenSize(1) * 0.7) + int(ScreenSize(1) * 0.3); //getting the appropriate size for the screen
    std::vector<char> randomChars(size);

    for (int i = 0; i < size; ++i) {
        randomChars[i] = 'a' + rand() % 26;
    }

    return randomChars;
}


int Rain::ScreenSize(int x) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consolesize;
    GetConsoleScreenBufferInfo(hConsole, &consolesize);

    int consoleWidth = consolesize.srWindow.Right - consolesize.srWindow.Left ;
    int consoleHeight = consolesize.srWindow.Bottom - consolesize.srWindow.Top + 1;

    if (x == 0) {
        return consoleWidth;
    }
    else if (x == 1) {
        return consoleHeight;
    }
    return 0;
}

int Rain::ReturnRand(int x) {
    int width = ScreenSize(0);
    width = width / 2;
    int rand=0;
    

    if (x == 0) {
        rand = int(-9 * width) + 1650;
    }
    else if (x == 1) {
        rand = int(-6.33 * width) + 900;
    }
    
    return rand;
}

void Rain::BottomReached(Rain& dr) {
    std::vector<char> drop = dr.GetChars();
    dr.GoToXY(dr.GetX(), (dr.GetY() - size(drop)));
    std::cout << ' ';
    drop.pop_back();
    dr.SetChars(drop);
    if (size(drop) == 0) {
        dr.SetChars(GenerateRandomChars());
        dr.SetY(0);
    }
}

void Rain::Init(std::vector<Rain>& raindrops) {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);

    srand(time(0));
    SetSpeeds(speeds);
    int v = 0;
    int width = ScreenSize(0);
    int height = ScreenSize(1);
    

    for (int x = 1; x <= width; x += 3) {
        if ((x+4) == width) { return; }
        else {
            std::vector<char> drop = GenerateRandomChars(); 
            int s = speeds[v];
            raindrops.push_back(Rain(x, (rand() % height), 0, s, v, drop));
            v++;
        }
    }
}

void Rain::Print(Rain& dr) {
    std::vector<char> drop = dr.GetChars();
    static std::vector<int> SpeedsCopy = GetSpeeds();
    static int SpeedFlag = 0;
    static int height;

    if (SpeedFlag == 0) {
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
                dr.SetSpeed(rand() % ReturnRand(0) + ReturnRand(0));
                SpeedsCopy[dr.GetVectorPos()] = dr.GetSpeed();
            }
        }
        else if (dr.GetSpeed() > 0) {
            dr.SetSpeed((dr.GetSpeed() - 1));
        }
    }
}