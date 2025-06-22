#include <iostream>
#include "Elevator.h"
#include "Button.h"
#include <set>
#include <thread>
#include <chrono>
using namespace std;

Elevator::Elevator() : current_floor(0), current_direction(0), out_of_service(false), 
                       elevator_id(0), speed(1.0), max_speed(2.0)
{
    num_of_floors = 0;
    elevator_buttons = nullptr;
}

Elevator::Elevator(int num_floors) : current_floor(0), current_direction(0), 
                                    out_of_service(false), elevator_id(0), 
                                    speed(1.0), max_speed(2.0)
{
    this->num_of_floors = num_floors;
    elevator_buttons = new Button[num_floors];
}

Elevator::Elevator(int num_floors, int id) : current_floor(0), current_direction(0), 
                                            out_of_service(false), elevator_id(id), 
                                            speed(1.0), max_speed(2.0)
{
    this->num_of_floors = num_floors;
    elevator_buttons = new Button[num_floors];
}

Elevator::~Elevator() {
    delete[] elevator_buttons;
}

// hardware function that should update the elevator floor when she get signal from a sensor for example.
void Elevator::updateCurrentFloor(int floor)
{
    if (floor >= 0 && floor < num_of_floors) {
        current_floor = floor;
    }
}

int Elevator::getCurrentFloor() const
{
    cout << "Current elevator floor is: " << current_floor << endl;
    return current_floor;
}

int Elevator::getCurrentDir() const
{ // returns current elevator direction
    return current_direction;
}

// functions that command the elevator to go to specific floor
void Elevator::goToFloor(int floor)
{
    if (out_of_service) {
        cout << "Elevator " << elevator_id << " is out of service!" << endl;
        return;
    }
    
    cout << "Elevator " << elevator_id << " going to floor: #" << floor << endl;
    current_direction = (floor > current_floor) ? 1 : (floor < current_floor) ? -1 : 0;
    moveToFloor(floor);
}

void Elevator::moveToFloor(int target_floor) {
    // Simulate movement time based on distance and speed
    int distance = abs(target_floor - current_floor);
    int travel_time = static_cast<int>(distance / speed * 1000); // Convert to milliseconds
    
    std::this_thread::sleep_for(std::chrono::milliseconds(travel_time));
    current_floor = target_floor;
    current_direction = 0; // Stop when reached
}

void Elevator::processRequest(set<int> &requests, int i)
{
    this->goToFloor(i);
    this->getCurrentFloor();
    requests.erase(requests.find(i));
}

// function that checks which floor buttons pressed from inside the elevator and add them to calls_queue
// should run in a thread activated in controller
void Elevator::elevatorRequests(std::set<int>& in_calls)
{
    for (int i = 0; i < num_of_floors; i++)
    {
        if (elevator_buttons[i].pressed)
            in_calls.insert(i);
    }
}

void Elevator::openDoors() {
    if (!out_of_service) {
        cout << "Elevator " << elevator_id << " doors opening..." << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(2000)); // 2 second door operation
        cout << "Elevator " << elevator_id << " doors open." << endl;
    }
}

void Elevator::closeDoors() {
    if (!out_of_service) {
        cout << "Elevator " << elevator_id << " doors closing..." << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(2000)); // 2 second door operation
        cout << "Elevator " << elevator_id << " doors closed." << endl;
    }
}

void Elevator::emergencyStop() {
    current_direction = 0;
    out_of_service = true;
    cout << "EMERGENCY STOP - Elevator " << elevator_id << " stopped at floor " 
         << current_floor << endl;
}
