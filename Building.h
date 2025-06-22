#pragma once
#include <vector>
#include "Elevator.h"
#include "Floor.h"
#include "Controller.h"

class Building {
private:
    std::vector<Elevator*> elevators;
    std::vector<Floor> floors;
    Controller controller;
public:
    Building(int num_elevators, int num_floors);
    ~Building();
    void assignElevator(int floor, int direction);
    void updateElevators();
    void runSimulation();
};