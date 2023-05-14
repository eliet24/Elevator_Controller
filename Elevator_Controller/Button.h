#ifndef Button_H
#define Button_H
#include <iostream>
#pragma once
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
