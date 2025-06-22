#ifndef BUTTON_H
#define BUTTON_H
#include <iostream>
#include "ElevatorComponent.h"
using namespace std;


class Button : public ElevatorComponent {
private:
    bool pressed;
public:
    Button();
    void pressButton();
    void initialize() override;
    void update() override;
    Button& operator=(const Button* obj);
};

#endif