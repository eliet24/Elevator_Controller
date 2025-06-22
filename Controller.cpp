#include <iostream>
#include <set>
#include "Button.h"
#include "Elevator.h"
#include "Controller.h"
#include "Floor.h"
#include <thread>
#include <functional>
#include <mutex>
using namespace std;

Controller::Controller(int num_floors) : direction(0), curr_floor(0)
{
    this->num_of_floors = num_floors;
    this->goto_floor = 0;
    this->floors = new Floor[num_floors];
    this->elevator = new Elevator(num_floors);
}

Controller::~Controller() {
    delete[] floors;
    delete elevator;
}

// Thread-safe methods for call management
void Controller::addInCall(int floor) {
    std::lock_guard<std::mutex> lock(calls_mutex);
    in_calls.insert(floor);
}

void Controller::addOutCall(int floor) {
    std::lock_guard<std::mutex> lock(calls_mutex);
    out_calls.insert(floor);
}

void Controller::removeInCall(int floor) {
    std::lock_guard<std::mutex> lock(calls_mutex);
    in_calls.erase(floor);
}

void Controller::removeOutCall(int floor) {
    std::lock_guard<std::mutex> lock(calls_mutex);
    out_calls.erase(floor);
}

bool Controller::hasInCalls() const {
    std::lock_guard<std::mutex> lock(calls_mutex);
    return !in_calls.empty();
}

bool Controller::hasOutCalls() const {
    std::lock_guard<std::mutex> lock(calls_mutex);
    return !out_calls.empty();
}

int Controller::getNextInCall() const {
    std::lock_guard<std::mutex> lock(calls_mutex);
    return in_calls.empty() ? -1 : *in_calls.begin();
}

int Controller::getNextOutCall() const {
    std::lock_guard<std::mutex> lock(calls_mutex);
    return out_calls.empty() ? -1 : *out_calls.begin();
}

void Controller::check()
{
    cout << "---------------------------" << endl;
    cout << "Elevator Controller created" << endl;
    cout << "---------------------------" << endl;
}

void Controller::runSystem()
{
    int request_floor;
    bool simulation_complete = false;

    //------------SIMULATION------------:
    // in_calls (elevator calls) = {1,5,8}
    // out_calls (floor calls) = {2,3} --> both asking to go UP
    //------------------------------------//
    addInCall(1);
    addInCall(5);
    elevator->elevator_buttons[1].pressButton();
    elevator->elevator_buttons[5].pressButton();
    addOutCall(2);
    addOutCall(3);
    floors[3].up.pressButton();
    floors[3].floor_dir_req = 1;
    floors[2].up.pressButton();
    floors[2].floor_dir_req = 1;
    addInCall(8);
    elevator->elevator_buttons[8].pressButton();
    //------------------------------------//

    //--- Improved Elevator logic ---//
    int simulation_cycles = 0;
    const int MAX_SIMULATION_CYCLES = 100; // Prevent infinite loops
    
    while ((hasInCalls() || hasOutCalls()) && simulation_cycles < MAX_SIMULATION_CYCLES)
    {
        simulation_cycles++;
        
        // both in & out calls exist
        if (hasInCalls() && hasOutCalls())
        {
            request_floor = getNextInCall();
            if (request_floor > curr_floor) // elevator direction is up
            {
                direction = 1;
                for (int i = curr_floor + 1; i <= request_floor; i++)
                {
                    std::lock_guard<std::mutex> lock(calls_mutex);
                    if (in_calls.find(i) != in_calls.end())
                    {
                        elevator->processRequest(in_calls, i);
                        curr_floor = i;
                    }
                    // check if there is floor calls on the way with the same direction
                    if (out_calls.find(i) != out_calls.end() && 
                        (floors[i].floor_dir_req == direction || floors[i].floor_dir_req == 2))
                    {
                        elevator->processRequest(out_calls, i);
                        curr_floor = i;
                    }
                }
            }
            else // elevator direction is down
            {
                direction = -1;
                for (int i = curr_floor - 1; i >= request_floor; i--)
                {
                    std::lock_guard<std::mutex> lock(calls_mutex);
                    if (in_calls.find(i) != in_calls.end())
                    {
                        elevator->processRequest(in_calls, i);
                        curr_floor = i;
                    }
                    // check if there is floor calls on the way with the same direction
                    if (out_calls.find(i) != out_calls.end() && 
                        (floors[i].floor_dir_req == direction || floors[i].floor_dir_req == 2))
                    {
                        elevator->processRequest(out_calls, i);
                        curr_floor = i;
                    }
                }
            }
        }
        // only out calls exist
        else if (hasOutCalls())
        {
            request_floor = getNextOutCall();
            direction = (request_floor > curr_floor) ? 1 : -1;
            
            if (direction == 1) {
                for (int i = curr_floor + 1; i <= request_floor; i++)
                {
                    std::lock_guard<std::mutex> lock(calls_mutex);
                    if (out_calls.find(i) != out_calls.end() && 
                        (floors[i].floor_dir_req == direction || floors[i].floor_dir_req == 2))
                    {
                        elevator->processRequest(out_calls, i);
                        curr_floor = i;
                    }
                }
            } else {
                for (int i = curr_floor - 1; i >= request_floor; i--)
                {
                    std::lock_guard<std::mutex> lock(calls_mutex);
                    if (out_calls.find(i) != out_calls.end() && 
                        (floors[i].floor_dir_req == direction || floors[i].floor_dir_req == 2))
                    {
                        elevator->processRequest(out_calls, i);
                        curr_floor = i;
                    }
                }
            }
        }
        // only in calls exist
        else if (hasInCalls())
        {
            request_floor = getNextInCall();
            direction = (request_floor > curr_floor) ? 1 : -1;
            
            if (direction == 1) {
                for (int i = curr_floor + 1; i <= request_floor; i++)
                {
                    std::lock_guard<std::mutex> lock(calls_mutex);
                    if (in_calls.find(i) != in_calls.end())
                    {
                        elevator->processRequest(in_calls, i);
                        curr_floor = i;
                    }
                }
            } else {
                for (int i = curr_floor - 1; i >= request_floor; i--)
                {
                    std::lock_guard<std::mutex> lock(calls_mutex);
                    if (in_calls.find(i) != in_calls.end())
                    {
                        elevator->processRequest(in_calls, i);
                        curr_floor = i;
                    }
                }
            }
        }
        
        // Add a small delay to prevent excessive CPU usage
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    
    if (simulation_cycles >= MAX_SIMULATION_CYCLES) {
        cout << "Simulation terminated: Maximum cycles reached" << endl;
    } else {
        cout << "Simulation completed: All requests processed" << endl;
    }
    
    direction = 0; // Stop elevator
}

int main()
{
    Controller controller(8);
    controller.check();
    controller.runSystem(); // Run once instead of infinite loop
    return 0;
}
