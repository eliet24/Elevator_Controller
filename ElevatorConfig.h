#ifndef ELEVATOR_CONFIG_H
#define ELEVATOR_CONFIG_H

// System Configuration Constants
namespace ElevatorConfig {
    // Building Configuration
    static const int DEFAULT_FLOORS = 8;
    static const int MAX_FLOORS = 50;
    static const int MAX_ELEVATORS = 10;
    
    // Elevator Performance
    static const double DEFAULT_SPEED = 1.0;        // floors per second
    static const double MAX_SPEED = 3.0;            // floors per second
    static const int DOOR_OPERATION_TIME = 2000;    // milliseconds
    static const int FLOOR_TRAVEL_BASE_TIME = 1000; // milliseconds
    
    // Safety and Limits
    static const int MAX_WEIGHT_KG = 1000;           // kg
    static const int MAX_PASSENGERS = 12;
    static const int EMERGENCY_TIMEOUT = 5000;       // milliseconds
    
    // Simulation Settings
    static const int MAX_SIMULATION_CYCLES = 100;
    static const int SIMULATION_DELAY_MS = 100;
    
    // Direction Constants
    enum Direction {
        DOWN = -1,
        STOPPED = 0,
        UP = 1,
        BOTH = 2
    };
    
    // Elevator States
    enum ElevatorState {
        IDLE,
        MOVING_UP,
        MOVING_DOWN,
        DOORS_OPENING,
        DOORS_CLOSING,
        OUT_OF_SERVICE,
        EMERGENCY
    };
    
    // Maintenance Priorities
    enum MaintenancePriority {
        EMERGENCY_PRIORITY = 0,
        HIGH_PRIORITY = 1,
        NORMAL_PRIORITY = 2,
        LOW_PRIORITY = 3
    };
}

#endif 