#pragma once
#include <iostream>
#include <set>
#include <vector>
#include "Button.h"
#include "Elevator.h"
#include "Floor.h"
#include <thread>
#include <functional>
#include <mutex>
using namespace std;

// global sets which holds all the calls for elevator from within the elevator and from the floors.
// holds the number of floor for every request
set<int> in_calls;
set<int> out_calls;
extern int direction;
extern int curr_floor;

class Controller
{
private:
    // Move global variables to class members for better encapsulation
    set<int> in_calls;
    set<int> out_calls;
    int direction;
    int curr_floor;
    mutable std::mutex calls_mutex; // Thread safety

public: 
    Elevator *elevator;
    int num_of_floors;
    Floor *floors;
    int goto_floor;

    Controller(int num_of_floors);
    ~Controller(); // Add destructor
    void check();
    void runSystem();
    
    // Getter methods for encapsulated variables
    int getCurrentFloor() const { return curr_floor; }
    int getDirection() const { return direction; }
    void setCurrentFloor(int floor) { curr_floor = floor; }
    void setDirection(int dir) { direction = dir; }
    
    // Thread-safe methods for call management
    void addInCall(int floor);
    void addOutCall(int floor);
    void removeInCall(int floor);
    void removeOutCall(int floor);
    bool hasInCalls() const;
    bool hasOutCalls() const;
    int getNextInCall() const;
    int getNextOutCall() const;
};

