

#pragma once

enum class MotorState {
    INIT,
    STOPPED,
    RUNNING,
    FAULT
};

class MotorController {
public:
    MotorController();

    void initialize();
    bool start(double voltage);
    void stop();

    void updateTemperature(double temperature);
    bool resetFault();

    MotorState getState() const;

private:
    MotorState state;
    double currentTemperature;

    static constexpr double MAX_TEMP = 90.0;
    static constexpr double RESET_TEMP = 85.0;
};
