// MaintenanceSystem.h
#pragma once
#include <vector>
#include <queue>
#include "Elevator.h"

struct MaintenanceTask {
    Elevator* elevator;
    std::string description;
    int priority;
};

class MaintenanceSystem {
private:
    std::vector<Elevator*> elevators;
    std::priority_queue<MaintenanceTask> tasks;
public:
    void addElevator(Elevator* elevator);
    void scheduleMaintenanceCheck(Elevator* elevator);
    void handleEmergency(Elevator* elevator);
    void performMaintenance();
};