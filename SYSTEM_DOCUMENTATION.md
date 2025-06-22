# 🏢 Elevator Controller System - Technical Documentation

<div align="center">

![Elevator](https://img.shields.io/badge/Elevator-Controller-blue.svg)
![C++](https://img.shields.io/badge/C%2B%2B-11%2B-orange.svg)
![Thread Safe](https://img.shields.io/badge/Thread-Safe-green.svg)
![Status](https://img.shields.io/badge/Status-Production%20Ready-brightgreen.svg)

*A sophisticated, thread-safe elevator control system with advanced scheduling and maintenance features*

</div>

---

## 📋 Table of Contents

- [🏗️ System Architecture](#️-system-architecture)
- [🔄 System Flow](#-system-flow)
- [🚗 Elevator State Machine](#-elevator-state-machine)
- [🏢 Multi-Elevator Building Management](#-multi-elevator-building-management)
- [⚡ Component Interactions](#-component-interactions)
- [🛠️ Maintenance System Flow](#️-maintenance-system-flow)
- [🔌 Power Management](#-power-management)
- [📊 Class Relationships](#-class-relationships)
- [🚀 Getting Started](#-getting-started)
- [🔧 Configuration](#-configuration)

---

## 🏗️ System Architecture

The elevator controller system follows a modular, object-oriented design with clear separation of concerns:

```mermaid
graph TB
    subgraph "Core System"
        Controller["🎮 Controller<br/>Main System Coordinator"]
        Building["🏢 Building<br/>Multi-Elevator Manager"]
        Elevator["🚗 Elevator<br/>Individual Elevator Control"]
        Floor["🏣 Floor<br/>Floor Management"]
    end
    
    subgraph "User Interface"
        Button["🔘 Button<br/>User Input"]
        Screen["📺 Screen<br/>Display System"]
    end
    
    subgraph "Management Systems"
        Maintenance["🔧 MaintenanceSystem<br/>Service Management"]
        Power["⚡ PowerManagementSystem<br/>Energy Control"]
    end
    
    subgraph "Base Classes"
        ElevatorComponent["⚙️ ElevatorComponent<br/>Abstract Base"]
        Config["⚙️ ElevatorConfig<br/>System Constants"]
    end
    
    Controller --> Building
    Building --> Elevator
    Controller --> Floor
    Floor --> Button
    Floor --> Screen
    Elevator --> Button
    Elevator --> Screen
    Button --> ElevatorComponent
    Maintenance --> Elevator
    Power --> Elevator
    
    style Controller fill:#e1f5fe
    style Building fill:#f3e5f5
    style Elevator fill:#e8f5e8
    style Maintenance fill:#fff3e0
    style Power fill:#fce4ec
```

---

## 🔄 System Flow

### Main Operation Flow

```mermaid
flowchart TD
    Start([🚀 System Start]) --> Init[Initialize Controller]
    Init --> CreateElevator[Create Elevator Instance]
    CreateElevator --> CreateFloors[Initialize Floor Objects]
    CreateFloors --> SetupButtons[Setup Button Arrays]
    SetupButtons --> SimStart[📋 Simulation Start]
    
    SimStart --> AddCalls[Add Test Calls<br/>• Internal: 1,5,8<br/>• External: 2,3]
    AddCalls --> MainLoop{📊 Process Calls Loop}
    
    MainLoop --> CheckCalls{Has Calls?}
    CheckCalls -->|No| SimEnd[🏁 Simulation Complete]
    CheckCalls -->|Yes| DetermineType{Call Type?}
    
    DetermineType -->|Both| ProcessBoth[🔄 Process Both Types]
    DetermineType -->|Internal Only| ProcessInternal[📥 Process Internal]
    DetermineType -->|External Only| ProcessExternal[📤 Process External]
    
    ProcessBoth --> CalcDirection[Calculate Direction]
    ProcessInternal --> CalcDirection
    ProcessExternal --> CalcDirection
    
    CalcDirection --> MoveElevator[🚗 Move Elevator]
    MoveElevator --> UpdateFloor[Update Current Floor]
    UpdateFloor --> RemoveCall[Remove Processed Call]
    RemoveCall --> CheckTimeout{Timeout?}
    
    CheckTimeout -->|No| MainLoop
    CheckTimeout -->|Yes| ForceStop[⚠️ Force Stop]
    
    ForceStop --> SimEnd
    SimEnd --> End([🛑 System End])
    
    style Start fill:#4caf50,color:#fff
    style SimEnd fill:#2196f3,color:#fff
    style End fill:#f44336,color:#fff
    style MoveElevator fill:#ff9800,color:#fff
```

---

## 🚗 Elevator State Machine

```mermaid
stateDiagram-v2
    [*] --> IDLE : System Initialize
    
    IDLE --> MOVING_UP : Floor Request Above
    IDLE --> MOVING_DOWN : Floor Request Below
    IDLE --> DOORS_OPENING : Same Floor Request
    IDLE --> OUT_OF_SERVICE : Maintenance Required
    
    MOVING_UP --> DOORS_OPENING : Reach Target Floor
    MOVING_UP --> EMERGENCY : Emergency Stop
    MOVING_UP --> OUT_OF_SERVICE : System Fault
    
    MOVING_DOWN --> DOORS_OPENING : Reach Target Floor
    MOVING_DOWN --> EMERGENCY : Emergency Stop
    MOVING_DOWN --> OUT_OF_SERVICE : System Fault
    
    DOORS_OPENING --> DOORS_CLOSING : Timer Complete
    DOORS_CLOSING --> IDLE : No More Requests
    DOORS_CLOSING --> MOVING_UP : Request Above
    DOORS_CLOSING --> MOVING_DOWN : Request Below
    
    EMERGENCY --> OUT_OF_SERVICE : Manual Override
    OUT_OF_SERVICE --> IDLE : Maintenance Complete
    
    note right of IDLE
        🟢 Ready for requests
        Current floor displayed
        Direction = STOPPED
    end note
    
    note right of MOVING_UP
        🔵 Traveling upward
        Speed controlled
        Checking intermediate floors
    end note
    
    note right of EMERGENCY
        🔴 CRITICAL STATE
        All operations halted
        Maintenance required
    end note
```

---

## 🏢 Multi-Elevator Building Management

```mermaid
graph TB
    subgraph "Building Management System"
        BuildingController["🏢 Building Controller<br/>Manages 3 Elevators"]
        
        subgraph "Elevator Bank"
            E1["🚗 Elevator 1<br/>ID: 0<br/>Current: Floor 0"]
            E2["🚗 Elevator 2<br/>ID: 1<br/>Current: Floor 3"]
            E3["🚗 Elevator 3<br/>ID: 2<br/>Current: Floor 7"]
        end
        
        subgraph "Floor System"
            F0["Floor 0<br/>⬆️ Up Button"]
            F1["Floor 1<br/>⬆️ Up ⬇️ Down"]
            F2["Floor 2<br/>⬆️ Up ⬇️ Down"]
            F3["Floor 3<br/>⬆️ Up ⬇️ Down"]
            Fn["Floor N<br/>⬇️ Down Button"]
        end
    end
    
    BuildingController --> E1
    BuildingController --> E2
    BuildingController --> E3
    
    F0 --> BuildingController
    F1 --> BuildingController
    F2 --> BuildingController
    F3 --> BuildingController
    Fn --> BuildingController
    
    BuildingController -.->|Assigns Closest| E1
    BuildingController -.->|Load Balancing| E2
    BuildingController -.->|Optimal Route| E3
    
    style BuildingController fill:#1976d2,color:#fff
    style E1 fill:#4caf50,color:#fff
    style E2 fill:#ff9800,color:#fff
    style E3 fill:#9c27b0,color:#fff
```

### Elevator Assignment Algorithm

```mermaid
flowchart LR
    FloorCall[📞 Floor Call Received] --> CheckElevators{Check All Elevators}
    CheckElevators --> CalcDistance[📏 Calculate Distance<br/>for Each Elevator]
    CalcDistance --> CheckService{Is Elevator<br/>In Service?}
    CheckService -->|Yes| AddToList[➕ Add to Candidate List]
    CheckService -->|No| NextElevator[➡️ Check Next]
    NextElevator --> CheckService
    
    AddToList --> FindClosest[🎯 Find Closest Available]
    FindClosest --> AssignElevator[✅ Assign Elevator]
    AssignElevator --> UpdateQueue[📋 Update Request Queue]
    UpdateQueue --> NotifyUser[📺 Display Assignment]
    
    style FloorCall fill:#e3f2fd
    style AssignElevator fill:#c8e6c9
    style NotifyUser fill:#fff3e0
```

---

## ⚡ Component Interactions

### Thread-Safe Call Management

```mermaid
sequenceDiagram
    participant U as 👤 User
    participant F as 🏣 Floor
    participant C as 🎮 Controller
    participant E as 🚗 Elevator
    participant M as 🔒 Mutex
    
    U->>F: Press Up Button
    F->>C: addOutCall(floor)
    C->>M: Lock Mutex
    M-->>C: Acquired
    C->>C: out_calls.insert(floor)
    C->>M: Unlock Mutex
    
    par Internal Elevator Request
        E->>C: addInCall(floor)
        C->>M: Lock Mutex
        M-->>C: Acquired
        C->>C: in_calls.insert(floor)
        C->>M: Unlock Mutex
    end
    
    loop Main Processing Loop
        C->>M: Lock Mutex
        C->>C: Check Calls
        C->>E: processRequest()
        E->>E: Move to Floor
        E-->>C: Floor Reached
        C->>C: Remove from Queue
        C->>M: Unlock Mutex
    end
    
    Note over C,M: Thread-safe operations<br/>prevent race conditions
```

---

## 🛠️ Maintenance System Flow

```mermaid
graph TD
    subgraph "Maintenance Workflow"
        Schedule[📅 Schedule Maintenance] --> Priority{Priority Level}
        Priority -->|Emergency| Emergency[🚨 Emergency Priority<br/>Level 0]
        Priority -->|High| High[⚠️ High Priority<br/>Level 1]
        Priority -->|Normal| Normal[✅ Normal Priority<br/>Level 2]
        Priority -->|Low| Low[📋 Low Priority<br/>Level 3]
        
        Emergency --> SetOOS[🔴 Set Out of Service]
        High --> CheckSchedule[📊 Check Schedule]
        Normal --> CheckSchedule
        Low --> CheckSchedule
        
        SetOOS --> NotifySystem[📢 Notify System]
        CheckSchedule --> QueueTask[📝 Queue Task]
        QueueTask --> ProcessTask[🔧 Process Maintenance]
        
        ProcessTask --> TaskComplete{Task Complete?}
        TaskComplete -->|Yes| RestoreService[✅ Restore Service]
        TaskComplete -->|No| ContinueWork[⏳ Continue Work]
        
        ContinueWork --> ProcessTask
        RestoreService --> UpdateStatus[📊 Update Status]
        NotifySystem --> ProcessTask
    end
    
    style Emergency fill:#ffcdd2
    style High fill:#ffe0b2
    style Normal fill:#c8e6c9
    style Low fill:#e1f5fe
    style SetOOS fill:#f44336,color:#fff
    style RestoreService fill:#4caf50,color:#fff
```

---

## 🔌 Power Management

```mermaid
graph TB
    subgraph "Power Management System"
        PowerMonitor[⚡ Power Monitor] --> PowerStatus{Power Status}
        
        PowerStatus -->|Normal| NormalOp[✅ Normal Operation<br/>Full Speed]
        PowerStatus -->|Low| PowerSave[🔋 Power Save Mode<br/>Reduced Speed]
        PowerStatus -->|Outage| Emergency[🚨 Emergency Mode<br/>Safe Stop]
        
        NormalOp --> MonitorUsage[📊 Monitor Usage]
        PowerSave --> ReduceSpeed[⬇️ Reduce Speed by 50%]
        Emergency --> SafeStop[🛑 Emergency Stop All<br/>Elevators]
        
        MonitorUsage --> OptimizeSchedule[⚙️ Optimize Schedule]
        ReduceSpeed --> EnergyReport[📈 Energy Report]
        SafeStop --> BackupPower[🔋 Switch to Backup]
        
        BackupPower --> MinimalOp[📍 Minimal Operation<br/>Emergency Only]
        MinimalOp --> PowerRestored{Power Restored?}
        PowerRestored -->|Yes| NormalOp
        PowerRestored -->|No| MinimalOp
    end
    
    style PowerMonitor fill:#e3f2fd
    style NormalOp fill:#c8e6c9
    style PowerSave fill:#fff3e0
    style Emergency fill:#ffcdd2
    style SafeStop fill:#f44336,color:#fff
```

---

## 📊 Class Relationships

```mermaid
classDiagram
    class ElevatorComponent {
        <<abstract>>
        +initialize()* void
        +update()* void
    }
    
    class Controller {
        -set~int~ in_calls
        -set~int~ out_calls
        -int direction
        -int curr_floor
        -mutex calls_mutex
        +Controller(int floors)
        +~Controller()
        +addInCall(int floor)
        +addOutCall(int floor)
        +runSystem()
    }
    
    class Elevator {
        -int current_floor
        -int current_direction
        -bool out_of_service
        -int elevator_id
        -double speed
        +Elevator(int floors, int id)
        +goToFloor(int floor)
        +emergencyStop()
        +openDoors()
        +closeDoors()
    }
    
    class Building {
        -vector~Elevator*~ elevators
        -vector~Floor~ floors
        -Controller controller
        +Building(int elevators, int floors)
        +assignElevator(int floor, int dir)
        +runSimulation()
    }
    
    class Floor {
        +int floor_num
        +Button up
        +Button down
        +Screen scr
        +int floor_dir_req
        +Floor(int n_floor)
        +addFloorRequest(int dir)
    }
    
    class Button {
        -bool pressed
        +Button()
        +pressButton()
        +initialize()
        +update()
    }
    
    class MaintenanceSystem {
        -vector~Elevator*~ elevators
        -priority_queue~MaintenanceTask~ tasks
        +scheduleMaintenanceCheck()
        +handleEmergency()
        +performMaintenance()
    }
    
    Controller --> Elevator : controls
    Controller --> Floor : manages
    Building --> Controller : contains
    Building --> Elevator : manages multiple
    Floor --> Button : has
    Elevator --> Button : has array
    Button --|> ElevatorComponent : inherits
    MaintenanceSystem --> Elevator : maintains
    
    style ElevatorComponent fill:#f9f9f9
    style Controller fill:#e3f2fd
    style Elevator fill:#e8f5e8
    style Building fill:#f3e5f5
```

---

## 🚀 Getting Started

### Quick Setup

```bash
# Clone the repository
git clone https://github.com/yourusername/elevator-controller.git
cd elevator-controller

# Compile the system
g++ -std=c++11 -pthread -o elevator_controller *.cpp

# Run the simulation
./elevator_controller
```

### Example Output

```
---------------------------
Elevator Controller created
---------------------------
Button pressed
Button pressed
Button pressed
Button pressed
Button pressed
Elevator 0 going to floor: #1
Current elevator floor is: 1
Elevator 0 going to floor: #2
Current elevator floor is: 2
...
Simulation completed: All requests processed
```

---

## 🔧 Configuration

### System Parameters (ElevatorConfig.h)

| Parameter | Default | Description |
|-----------|---------|-------------|
| `DEFAULT_FLOORS` | 8 | Number of floors in building |
| `MAX_ELEVATORS` | 10 | Maximum elevators per building |
| `DEFAULT_SPEED` | 1.0 | Floors per second |
| `MAX_SPEED` | 3.0 | Maximum elevator speed |
| `DOOR_OPERATION_TIME` | 2000ms | Time for door operations |
| `MAX_SIMULATION_CYCLES` | 100 | Safety limit for simulation |

### Customization Example

```cpp
// Create a 20-floor building with 4 elevators
Building skyscraper(4, 20);

// Configure high-speed elevator
Elevator express(20, 1);
express.setSpeed(ElevatorConfig::MAX_SPEED);

// Run custom simulation
skyscraper.runSimulation();
```

---

## 🌟 Features Highlight

<div align="center">

| Feature | Status | Description |
|---------|--------|-------------|
| 🔒 **Thread Safety** | ✅ | Mutex-protected shared resources |
| 🚗 **Multi-Elevator** | ✅ | Support for multiple elevators |
| 🛠️ **Maintenance** | ✅ | Automated maintenance scheduling |
| ⚡ **Power Management** | ✅ | Energy-efficient operation modes |
| 🎯 **Smart Scheduling** | ✅ | Optimized elevator assignment |
| 🛡️ **Safety Features** | ✅ | Emergency stops and failsafes |
| 📊 **Real-time Status** | ✅ | Live system monitoring |
| ⚙️ **Configurable** | ✅ | Customizable system parameters |

</div>

---

<div align="center">

**🏢 Built with precision for modern elevator systems**

[![GitHub stars](https://img.shields.io/github/stars/yourusername/elevator-controller.svg?style=social&label=Star)](https://github.com/yourusername/elevator-controller)
[![GitHub forks](https://img.shields.io/github/forks/yourusername/elevator-controller.svg?style=social&label=Fork)](https://github.com/yourusername/elevator-controller/fork)

*Elevator Controller System - Making vertical transportation intelligent* 🚀

</div> 