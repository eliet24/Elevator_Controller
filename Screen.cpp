#include <iostream>
#include "Screen.h"
using namespace std;


// using the global varibles curr_floor & direction for printing
void Screen::print()
{
    if (direction == 1)
        cout << curr_floor << " up";
    else if (direction == -1)
        cout << curr_floor << " down";
    else if (direction == 0)
        cout << curr_floor << " stopped";
}
