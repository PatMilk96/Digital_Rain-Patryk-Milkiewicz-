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
#include <chrono>
#include <thread>

#define VERBOSE 1

class Rain {
public:
    Rain();
    ~Rain();
    Rain(int, int, int, int, int, const std::vector<char>&);
    Rain(const Rain&);
    
    void SetChars(const std::vector<char>&);
    void SetSpeeds(const std::vector<int>&);
    void SetY(int);
    void SetX(int);
    void SetArrP(int);
    void SetSpeed(int);
    void SetVectorPos(int);
    
    std::vector<char> GetChars() const { return chars; }
    std::vector<int> GetSpeeds() const { return speeds; }
    int GetX() const { return x; }
    int GetY() const { return y; }
    int GetArrP() const { return arrP; }
    int GetSpeed() const { return speed; }
    int GetVectorPos() const { return vectorPos; }

    void GoToXY(int, int) const;
    void Init(std::vector<Rain>&);
    void Print(Rain&);
    void BottomReached(Rain&);

    std::vector<char> GenerateRandomChars();
    int ScreenSize(int);
    int ReturnRand(int);

private:
    std::vector<char> chars;
    std::vector<int> speeds;
    int arrP;
    int x;
    int y;
    int speed;
    int vectorPos;


    static int count;
};

std::ostream& operator<<(std::ostream& output, const Rain& p);

#endif