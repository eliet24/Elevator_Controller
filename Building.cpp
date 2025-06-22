#include "Building.h"
#include <iostream>
#include <algorithm>

Building::Building(int num_elevators, int num_floors) : controller(num_floors) {
    // Initialize floors
    floors.resize(num_floors);
    for (int i = 0; i < num_floors; i++) {
        floors[i] = Floor(i);
    }
    
    // Initialize elevators
    elevators.resize(num_elevators);
    for (int i = 0; i < num_elevators; i++) {
        elevators[i] = new Elevator(num_floors, i);
    }
}

Building::~Building() {
    // Clean up dynamically allocated elevators
    for (auto elevator : elevators) {
        delete elevator;
    }
}

void Building::assignElevator(int floor, int direction) {
    // Simple assignment algorithm - find closest available elevator
    Elevator* best_elevator = nullptr;
    int min_distance = INT_MAX;
    
    for (auto elevator : elevators) {
        if (!elevator->isOutOfService()) {
            int distance = abs(elevator->getCurrentFloor() - floor);
            if (distance < min_distance) {
                min_distance = distance;
                best_elevator = elevator;
            }
        }
    }
    
    if (best_elevator) {
        controller.addOutCall(floor);
        std::cout << "Assigned elevator " << best_elevator->getId() 
                  << " to floor " << floor << std::endl;
    }
}

void Building::updateElevators() {
    for (auto elevator : elevators) {
        if (!elevator->isOutOfService()) {
            // Update elevator position and process requests
            // This would be called periodically in a real system
        }
    }
}

void Building::runSimulation() {
    std::cout << "Starting building simulation with " 
              << elevators.size() << " elevators and " 
              << floors.size() << " floors" << std::endl;
    
    // Run the controller system
    controller.runSystem();
}