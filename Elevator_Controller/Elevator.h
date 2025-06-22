#ifndef ELEVATOR_H
#define ELEVATOR_H
#include <iostream>
#include "Button.h"
#include "Screen.h"
#include <set>

extern set<int> in_calls;
extern int direction;
extern int curr_floor;

class Elevator
{
public:
    int num_of_floors;
    Button *elevator_buttons;
    Screen scr;

    Elevator();
    Elevator(int num_floors);
    int getCurrentFloor();
    int getCurrentDir();
    void updateCurrentFloor(int floor);
    void goToFloor(int floor);
    void elevatorRequests();
    void processRequest(set<int> &requests, int i);
    // Elevator &operator=(const Elevator *obj);
};
#endif
