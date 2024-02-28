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

#define VERBOSE 1

class Rain {
public:
    Rain();
    ~Rain();
    Rain(const std::vector<char>&);
    Rain(int, int, const std::vector<char>&);
    Rain(Rain&);
    void SetChars(const std::vector<char>&);
    std::vector<char> GetChars() const { return chars; }

    void GoToXY(int, int) const;
    void Print(int, int, const std::vector<char>&);

private:
    std::vector<char> chars;
    int x;
    int y;

    static int count;
};

std::ostream& operator<<(std::ostream& output, const Rain& p);

#endif