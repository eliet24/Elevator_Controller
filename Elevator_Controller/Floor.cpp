#include <iostream>
#include "Floor.h"
#include "Button.h"
#include "Screen.h"
#include "Elevator.h"
#include <utility>

#include <thread>
using namespace std;

Floor::Floor()
{
    floor_num = -1;
}
Floor::Floor(int n_floor)
{
    floor_num = n_floor;
}

// assignment operator for floors (used in Controoler:line 25) to create all the floors
Floor &Floor::operator=(const Floor *level)
{
    this->floor_num = level->floor_num;
    return *this;
}

// set request direction and add it to out_calls set
void Floor::addFloorRequest(int dir)
{
    floor_dir_req = dir;
    if (out_calls.find(this->floor_num) != out_calls.end())
        out_calls.insert(out_calls.begin(), this->floor_num);
}

// func that checks which button pressed for current floor and initalize floor_dir_req pair accordingly
//  up: dir = 1, down: dir = -1, up & down: dir = 2, no request: dir = 0

// should run in a thread active it in controller for each floor
void Floor::floorRequests()
{
    if (this->up.pressed && this->down.pressed) // up and down requests
    {
        this->addFloorRequest(2);
    }
    else if (this->up.pressed && !this->down.pressed) // up request
    {
        this->addFloorRequest(1);
    }
    else if (!this->up.pressed && this->down.pressed) // down request
    {
        this->addFloorRequest(-1);
    }
    else if (!this->up.pressed && this->down.pressed) // No requests
    {
        floor_dir_req = 0;
    }
}

////should run in a thread + active it in controller for each floor
/*void Floor::showScreen()
{
    scr.print();
}*/

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    out_calls.insert(GPIO_Pin);
}
