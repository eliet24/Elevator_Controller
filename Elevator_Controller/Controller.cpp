#include <iostream>
#include <set>
#include "Button.h"
#include "Elevator.h"
#include "Controller.h"
#include "Floor.h"
#include <thread>
#include <functional>
using namespace std;

Controller::Controller(int num_floors)
{
    this->num_of_floors = num_floors;
    this->goto_floor = 0;
    this->floors = new Floor[num_of_floors];
    this->elevator = new Elevator(num_floors);
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

    //------------SIMULATION------------:
    // in_calls (elevator calls) = {1,5,8}
    // out_calls (floor calls) = {2,3} --> both asking to go UP
    //------------------------------------//
    in_calls.insert(in_calls.begin(), 1);
    in_calls.insert(in_calls.begin(), 5);
    elevator->elevator_buttons[1].pressButton();
    elevator->elevator_buttons[5].pressButton();
    out_calls.insert(out_calls.begin(), 2);
    out_calls.insert(out_calls.begin(), 3);
    floors[3].up.pressButton();
    floors[3].floor_dir_req = 1;
    floors[2].up.pressButton();
    floors[2].floor_dir_req = 1;
    in_calls.insert(in_calls.begin(), 8);
    elevator->elevator_buttons[8].pressButton();
    int j = 0;
    //------------------------------------//

    // Activate all threads:
    /*
    thread searchInCalls(&Elevator <int,M>::elevatorRequests, ref(elevator));
    for(int i=0; i<M;i++){
        thread searchOutCalls(&Floor::floorRequests, ref(floors[i]));
        thread showScreen(&Floor::showScreen, ref(floors[i]));
    }
    */

    //--- Elevator logic ---//
    while (1)
    {
        while (!in_calls.empty() || !out_calls.empty()) // Enter external loop only while tasks exist
        {
            // both in & out calls exist
            if (!in_calls.empty() && !out_calls.empty())
            {
                request_floor = *in_calls.begin();
                if (request_floor > curr_floor) // elevator direction is up
                {
                    direction = 1;
                    for (int i = curr_floor + 1; i <= request_floor; i++)
                    {
                        if (in_calls.find(i) != in_calls.end())
                        {
                            elevator->processRequest(in_calls, i);
                        }
                        // check if there is floor calls on the way with the same direction the elevator is going.
                        if (out_calls.find(i) != out_calls.end() && (floors[i].floor_dir_req == direction || floors[i].floor_dir_req == 2))
                        {
                            elevator->processRequest(out_calls, i);
                        }
                    }
                }
                else // elevator direction is down
                {
                    direction = -1;
                    for (int i = curr_floor - 1; i >= request_floor; i--)
                    {
                        if (in_calls.find(i) != in_calls.end())
                        {
                            elevator->processRequest(in_calls, i);
                        }
                        // check if there is floor calls on the way with the same direction the elevator is going.
                        if (out_calls.find(i) != out_calls.end() && (floors[i].floor_dir_req == direction || floors[i].floor_dir_req == 2))
                        {
                            elevator->processRequest(out_calls, i);
                        }
                    }
                }
            }

            // only out calls exist
            else if (in_calls.empty())
            {
                request_floor = *out_calls.begin();
                if (request_floor > curr_floor)
                {
                    direction = 1; // elevator direction is up
                    for (int i = curr_floor + 1; i <= request_floor; i++)
                    {
                        // check if there is floor calls on the way with the same direction the elevator is going.
                        if (out_calls.find(i) != out_calls.end() && (floors[i].floor_dir_req == direction || floors[i].floor_dir_req == 2))
                        {
                            elevator->processRequest(out_calls, i);
                        }
                    }
                }
                else
                {
                    direction = -1;
                    for (int i = curr_floor - 1; i >= request_floor; i--)
                    {
                        // check if there is floor calls on the way with the same direction the elevator is going.
                        if (out_calls.find(i) != out_calls.end() && (floors[i].floor_dir_req == direction || floors[i].floor_dir_req == 2))
                        {
                            elevator->processRequest(out_calls, i);
                        }
                    }
                }
            }

            // only in calls exist
            else if (out_calls.empty()) // only in calls exist
            {
                request_floor = *in_calls.begin();
                if (request_floor > curr_floor)
                {
                    direction = 1;
                    for (int i = curr_floor + 1; i <= request_floor; i++)
                    {
                        if (in_calls.find(i) != in_calls.end())
                        {
                            elevator->processRequest(in_calls, i);
                        }
                    }
                }
                else
                {
                    direction = -1;
                    for (int i = curr_floor - 1; i >= request_floor; i--)
                    {
                        if (in_calls.find(i) != in_calls.end())
                        {
                            elevator->processRequest(in_calls, i);
                        }
                    }
                }
            }
        }
    //-----------------------------------------//
    //----SIMULATION for elevator going down---//
    // in_calls (elevator calls) = {2}
    // out_calls (floor calls) = {3} --> both asking to go UP
        while (!j) // Execute 1 time
        {
            in_calls.insert(in_calls.begin(), 2);
            elevator->elevator_buttons[2].pressButton();
            out_calls.insert(out_calls.begin(), 3);
            floors[3].down.pressButton();
            floors[3].floor_dir_req = -1;
            j = 1;
        }
    //-----------------------------------------//
    }
}

int main()
{
    Controller controller(8);
    controller.check();
    while (1)
    {
        controller.runSystem();
    }
    return 0;
}
