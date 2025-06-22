#include "PowerManagementSystem.h"
#include <iostream>

PowerManagementSystem::PowerManagementSystem() : power_saving_mode(false) {}

void PowerManagementSystem::addElevator(Elevator* elevator) {
    elevators.push_back(elevator);
}

void PowerManagementSystem::enablePowerSavingMode() {
    power_saving_mode = true;
    std::cout << "Power saving mode enabled" << std::endl;
    for (auto elevator : elevators) {
        elevator->setSpeed(elevator->getSpeed() / 2);
    }
}

void PowerManagementSystem::disablePowerSavingMode() {
    power_saving_mode = false;
    std::cout << "Power saving mode disabled" << std::endl;
    for (auto elevator : elevators) {
        elevator->setSpeed(elevator->getSpeed() * 2);
    }
}

void PowerManagementSystem::handlePowerOutage() {
    std::cout << "Power outage detected!" << std::endl;
    for (auto elevator : elevators) {
        elevator->emergencyStop();
    }
}