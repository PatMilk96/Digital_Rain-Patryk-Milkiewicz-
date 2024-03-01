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
    Rain(const std::vector<char>&);
    Rain(int, int, const std::vector<char>&);
    Rain(int, int, int, const std::vector<char>&);
    Rain(const Rain&);
    
    void SetChars(const std::vector<char>&);
    void SetY(int);
    void SetX(int);
    void SetArrP(int);
    
    std::vector<char> GetChars() const { return chars; }
    int GetX() const { return x; }
    int GetY() const { return y; }
    int GetArrP() const { return arrP; }

    void GoToXY(int, int) const;
    void Init(std::vector<Rain>&);
    void Print(Rain&);

    std::vector<char> GenerateRandomChars() {
        int size = rand() % 15 + 9; // Random size between 9 and 24
        std::vector<char> randomChars(size);

        for (int i = 0; i < size; ++i) {
            randomChars[i] = 'a' + rand() % 26; // Random lowercase letter
        }

        return randomChars;
    }

private:
    std::vector<char> chars;
    int arrP;
    int x;
    int y;

    static int count;
};

std::ostream& operator<<(std::ostream& output, const Rain& p);

#endif