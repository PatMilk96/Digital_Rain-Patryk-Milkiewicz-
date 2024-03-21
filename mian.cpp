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
#include <math.h>


int main() {
    std::cout << "Please adjust the window to your desired size\n" << std::endl;
    system("pause");
    std::system("CLS");
    Rain rain;
    std::vector<Rain> raindrops;
    
    rain.Init(raindrops);
    system("Color 0A");
    while (1) {
        for (auto& drop : raindrops) {
            rain.Print(drop);
        }
    }

    return 0;
}




/*
The original algorithm
Rain dr;
std::vector<char> test = { '1','2','3', '4', '5', '6', '7', '8','9', '1', '2', '3', '4', '5' };
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
