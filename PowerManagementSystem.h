#pragma once
#include <vector>
#include "Elevator.h"

class PowerManagementSystem {
private:
    std::vector<Elevator*> elevators;
    bool power_saving_mode;
public:
    PowerManagementSystem();
    void addElevator(Elevator* elevator);
    void enablePowerSavingMode();
    void disablePowerSavingMode();
    void handlePowerOutage();
};
