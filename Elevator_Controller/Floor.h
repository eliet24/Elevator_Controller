#ifndef FLOOR_H
#define FLOOR_H
#include <iostream>
#include "Button.h"
#include "Screen.h"
#include <set>
#include <thread>

extern set<int> out_calls;

class Floor
{
public:
    int floor_num;
    Button up;
    Button down;
    Screen scr;
    int floor_dir_req;

    Floor();
    Floor(int n_floor);
    void showScreen();
    void addFloorRequest(int dir);
    void floorRequests();
    Floor &operator=(const Floor *level);
};
#endif