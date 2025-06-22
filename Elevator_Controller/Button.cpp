
#include <iostream>
#include "Button.h"
using namespace std;

// constructor for Button: initialize pressed = false
Button::Button()
{
    pressed = false;
}


// interrupt function that change pressed to TRUE
void Button::pressButton()
{
    cout << " button pressed" << endl;
    this->pressed = true;
}

// assignment operator
Button &Button::operator=(const Button *obj)
{
    this->pressed = obj->pressed;
    return *this;
}


