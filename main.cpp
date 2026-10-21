
#include <iostream>
#include "MotorController.hpp"

int main() {
    MotorController motor;

    motor.initialize();

    bool started = motor.start(14.0);

    std::cout << "Start accepted: "
              << (started ? "YES" : "NO") << '\n';

    std::cout << "State: "
              << (motor.getState() == MotorState::RUNNING
                      ? "RUNNING"
                      : "NOT RUNNING")
              << '\n';

    return 0;
}
