#ifndef ELEVATOR_H
#define ELEVATOR_H
#include <iostream>
#include "Button.h"
#include "Screen.h"
#include <set>

class Elevator
{
private:
    int current_floor;
    int current_direction; // -1: down, 0: stopped, 1: up
    bool out_of_service;
    int elevator_id;
    double speed; // floors per second
    double max_speed;
    
public:
    int num_of_floors;
    Button *elevator_buttons;
    Screen scr;

    Elevator();
    Elevator(int num_floors);
    Elevator(int num_floors, int id);
    ~Elevator(); // Add destructor
    
    // Core functionality
    int getCurrentFloor() const;
    int getCurrentDir() const;
    void updateCurrentFloor(int floor);
    void goToFloor(int floor);
    void elevatorRequests(std::set<int>& in_calls);
    void processRequest(std::set<int> &requests, int i);
    
    // New methods for maintenance and power management
    void setOutOfService(bool status) { out_of_service = status; }
    bool isOutOfService() const { return out_of_service; }
    int getId() const { return elevator_id; }
    void setSpeed(double new_speed) { speed = (new_speed <= max_speed) ? new_speed : max_speed; }
    double getSpeed() const { return speed; }
    void emergencyStop();
    
    // Movement control
    void openDoors();
    void closeDoors();
    
private:
    void moveToFloor(int target_floor);
};
#endif
