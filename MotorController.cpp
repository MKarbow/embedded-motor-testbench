

#include "MotorController.hpp"
#include <cmath>

MotorController::MotorController()
    : state(MotorState::INIT),
      currentTemperature(25.0) {}

void MotorController::initialize() {
    state = MotorState::STOPPED;
}

bool MotorController::start(double voltage) {
    if (state != MotorState::STOPPED) {
        return false;
    }

    if (!std::isfinite(voltage) ||
    voltage < 15.0 ||
    voltage > 21.0) {
    return false;
    }

    if (currentTemperature >= MAX_TEMP) {
        state = MotorState::FAULT;
        return false;
    }

    state = MotorState::RUNNING;
    return true;
}

void MotorController::stop() {
    if (state == MotorState::RUNNING) {
        state = MotorState::STOPPED;
    }
}

void MotorController::updateTemperature(double temperature) {
    currentTemperature = temperature;

    if (!std::isfinite(currentTemperature) ||
        currentTemperature >= MAX_TEMP) {
        state = MotorState::FAULT;
    }
}

bool MotorController::resetFault() {
    if (state != MotorState::FAULT) {
        return false;
    }

    if (currentTemperature >= RESET_TEMP) {
        return false;
    }

    state = MotorState::STOPPED;
    return true;
}

MotorState MotorController::getState() const {
    return state;
}
