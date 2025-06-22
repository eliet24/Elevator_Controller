#ifndef ELEVATORCOMPONENT_H
#define ELEVATORCOMPONENT_H

class ElevatorComponent {
public:
    virtual void initialize() = 0;
    virtual void update() = 0;
    virtual ~ElevatorComponent() = default;
};

#endif