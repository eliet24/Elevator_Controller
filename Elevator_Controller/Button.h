#ifndef BUTTON_H
#define BUTTON_H
#include <iostream>
using namespace std;

class Button
{
public:
    bool pressed;

    Button();
    void pressButton();
    // assignment operator
    Button &operator=(const Button *obj);
};
#endif
