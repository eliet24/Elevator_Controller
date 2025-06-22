#include "Button.h"
#include <iostream>

Button::Button() : pressed(false) {}

void Button::pressButton() {
    std::cout << "Button pressed" << std::endl;
    this->pressed = true;
}

void Button::initialize() {
    pressed = false;
}

void Button::update() {
    // Check for physical button press, e.g., through GPIO
}

Button& Button::operator=(const Button* obj) {
    this->pressed = obj->pressed;
    return *this;
}

