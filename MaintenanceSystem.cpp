// MaintenanceSystem.cpp
#include "MaintenanceSystem.h"
#include <iostream>

void MaintenanceSystem::addElevator(Elevator* elevator) {
    elevators.push_back(elevator);
}

void MaintenanceSystem::scheduleMaintenanceCheck(Elevator* elevator) {
    tasks.push({elevator, "Routine maintenance check", 1});
}

void MaintenanceSystem::handleEmergency(Elevator* elevator) {
    tasks.push({elevator, "Emergency maintenance", 0});
    elevator->setOutOfService(true);
}

void MaintenanceSystem::performMaintenance() {
    if (!tasks.empty()) {
        MaintenanceTask task = tasks.top();
        tasks.pop();
        std::cout << "Performing maintenance on elevator " << task.elevator->getId() 
                  << ": " << task.description << std::endl;
        // Perform maintenance...
        task.elevator->setOutOfService(false);
    }
}