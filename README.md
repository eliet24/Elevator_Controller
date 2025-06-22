# Elevator Controller System

## Overview
This is a comprehensive elevator control system implemented in C++ that simulates the operation of single and multi-elevator buildings. The system features advanced scheduling algorithms, maintenance management, power control, and safety features.

## System Architecture

### Core Components
- **Controller**: Main system coordinator with SCAN scheduling algorithm
- **Elevator**: Individual elevator management with state tracking
- **Building**: Multi-elevator building management
- **Floor**: Floor-specific call management
- **Button**: User interface components
- **Screen**: Display system for status information
- **MaintenanceSystem**: Maintenance scheduling and emergency handling
- **PowerManagementSystem**: Power saving and outage management

### Design Patterns Used
- **Inheritance**: ElevatorComponent base class for hardware components
- **Encapsulation**: Private member variables with controlled access
- **Thread Safety**: Mutex protection for shared resources
- **RAII**: Proper resource management with destructors

## Features

### Current Implementation
- ✅ Single elevator control with basic SCAN algorithm
- ✅ Floor call management (up/down buttons)
- ✅ Button press simulation
- ✅ Display system for current floor and direction
- ✅ Basic maintenance system framework
- ✅ Power management system framework
- ✅ Thread-safe call management
- ✅ Memory leak prevention with proper destructors

### Enhanced Features (Implemented)
- ✅ Multi-elevator support through Building class
- ✅ Improved scheduling with closest elevator selection
- ✅ Emergency stop functionality
- ✅ Door operation simulation
- ✅ Speed control and travel time simulation
- ✅ Out-of-service status management
- ✅ Configuration management through ElevatorConfig

## Build Instructions

### Prerequisites
- C++ compiler with C++11 support (g++, clang++, MSVC)
- Windows/Linux/macOS compatible

### Compilation
```bash
# Single file compilation
g++ -std=c++11 -pthread -o elevator_controller *.cpp

# Or using individual files
g++ -std=c++11 -pthread -o elevator_controller \
    Controller.cpp Elevator.cpp Building.cpp Floor.cpp \
    Button.cpp Screen.cpp MaintenanceSystem.cpp \
    PowerManagementSystem.cpp
```

### Running the System
```bash
./elevator_controller
```

## Usage Examples

### Basic Single Elevator Operation
```cpp
// Create controller for 8-floor building
Controller controller(8);
controller.check();        // Initialize system
controller.runSystem();    // Run simulation
```

### Multi-Elevator Building
```cpp
// Create building with 3 elevators and 10 floors
Building building(3, 10);
building.runSimulation();
```

## Configuration

System parameters can be modified in `ElevatorConfig.h`:
- Building dimensions (floors, elevators)
- Performance parameters (speed, timing)
- Safety limits (weight, passengers)
- Simulation settings

## Thread Safety

The system implements thread-safe operations for:
- Call queue management (in_calls, out_calls)
- Elevator state updates  
- Floor request processing

## Error Handling

- Memory leak prevention with RAII
- Boundary checking for floor numbers
- Out-of-service elevator handling
- Simulation timeout protection

## Testing

The system includes built-in simulation scenarios:
- Multiple simultaneous calls
- Up and down requests
- Emergency situations
- Maintenance scenarios

## Future Enhancements

### Planned Features
- [ ] Advanced scheduling algorithms (Look, C-Look)
- [ ] Weight sensor integration
- [ ] Door sensor safety features
- [ ] Fire safety mode
- [ ] VIP/Express elevator support
- [ ] Statistical analysis and reporting
- [ ] GUI interface
- [ ] Network connectivity for remote monitoring
- [ ] Database logging
- [ ] Real-time performance metrics

### Embedded System Integration
The system is designed for embedded deployment with:
- GPIO interrupt handlers (see HandlersAndCallbacks.txt)
- Hardware abstraction layer support
- Real-time constraints handling
- Memory-efficient operations

## API Reference

### Controller Class
```cpp
Controller(int num_floors);          // Constructor
void addInCall(int floor);           // Add internal call
void addOutCall(int floor);          // Add external call
void runSystem();                    // Execute main loop
```

### Elevator Class
```cpp
Elevator(int num_floors, int id);    // Constructor with ID
void goToFloor(int floor);           // Move to specific floor
void emergencyStop();                // Emergency stop
void setOutOfService(bool status);   // Service status
```

### Building Class
```cpp
Building(int elevators, int floors); // Constructor
void assignElevator(int floor, int dir); // Assign closest elevator
void runSimulation();                // Run building simulation
```

## Contributing

1. Follow the existing code style and patterns
2. Add appropriate error handling
3. Include proper documentation
4. Test with multiple scenarios
5. Ensure thread safety for concurrent operations

## License

This project is developed for educational and research purposes.

## Contact

For questions about implementation details or enhancement suggestions, please refer to the code documentation and TODO.txt file. 