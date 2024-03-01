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
#include "DigitalRain.h"
#include <windows.h>

int main() {
    Rain dr;
    Rain dr3(15, 0, 0, { 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l'});
    
    dr.Init();
    
    
    /*
    int i = 0;
    int j = 0;
    int x = size(test);

    while (1) {
        if (j == size(test)) { j = 0; }

        dr.GoToXY(0, i);

        std::cout << test[j];

        dr.GoToXY(0, i - x);

        std::cout << ' ';

        Sleep(75);

        i++;
        j++;
    }
    */

    return 0;
}