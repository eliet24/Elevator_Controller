#ifndef Controller_H
#define Controller_H
#pragma once
#include <iostream>
#include <set>
#include <vector>
#include "Button.h"
#include "Elevator.h"
#include "Floor.h"
#include <thread>
#include <functional>
using namespace std;

// global sets which holds all the calls for elevator from within the elevator and from the floors.
// holds the number of floor for every request
set<int> in_calls;
set<int> out_calls;
extern int direction;
extern int curr_floor;

class Controller
{
public: 
    Elevator *elevator;
    int num_of_floors;
    Floor *floors;
    int goto_floor;

    Controller(int num_of_floors);
    void check();
    void runSystem();
};
#endif
