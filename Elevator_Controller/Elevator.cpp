#include <iostream>
#include "Elevator.h"
#include "Button.h"
#include <set>
#include <thread>
#include <chrono>
using namespace std;
//using namespace std::chrono;

Elevator::Elevator()
{
    direction = 0;
    curr_floor = 0;
    *elevator_buttons = new Button[num_of_floors];
}
Elevator::Elevator(int num_of_floors)
{
    direction = 0;
    curr_floor = 0;
    elevator_buttons = new Button[num_of_floors];
}

// hardware function that should update the elevator floor when she get signal from a sensor for example.
void Elevator::updateCurrentFloor(int floor)
{
    curr_floor = floor;
}

int Elevator::getCurrentFloor()
{
    cout << "Current elevator floor is: " << curr_floor << endl;
    return curr_floor;
}

int Elevator::getCurrentDir()
{ // returns current elevator direction
    return direction;
}

// functions that command the elevator to go to specific floor
void Elevator::goToFloor(int floor)
{
    cout << "Elevator going to floor: #" << floor << endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    curr_floor = floor;
}

void Elevator::processRequest(set<int> &requests, int i)
{
    this->goToFloor(i);
    this->getCurrentFloor();
    requests.erase(requests.find(i));
}

// function that checks which floor buttons pressed from inside the elevator and add them to calls_queue
// should run in a thread activated in controller
void Elevator::elevatorRequests()
{
    for (int i = 0; i <= num_of_floors; i++)
    {
        if (elevator_buttons[i].pressed)
            in_calls.insert(i);
    }
}
