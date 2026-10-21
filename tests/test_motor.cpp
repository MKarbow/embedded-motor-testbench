
#include <gtest/gtest.h>
#include "MotorController.hpp"
#include <limits>

// TEST 1: Po inicjalizacji silnik jest zatrzymany.
TEST(MotorControllerTest, Initialization) {
    MotorController motor;

    motor.initialize();

    EXPECT_EQ(motor.getState(), MotorState::STOPPED);
}

// TEST 2: Poprawne napięcie pozwala uruchomić silnik.
TEST(MotorControllerTest, ValidVoltage) {
    MotorController motor;
    motor.initialize();

    EXPECT_TRUE(motor.start(18.0));
    EXPECT_EQ(motor.getState(), MotorState::RUNNING);
}

// TEST 3: Zbyt niskie napięcie blokuje uruchomienie.
TEST(MotorControllerTest, LowVoltage) {
    MotorController motor;
    motor.initialize();

    EXPECT_FALSE(motor.start(14.0));
    EXPECT_EQ(motor.getState(), MotorState::STOPPED);
}

// TEST 4: Zbyt wysokie napięcie blokuje uruchomienie.
TEST(MotorControllerTest, HighVoltage) {
    MotorController motor;
    motor.initialize();

    EXPECT_FALSE(motor.start(22.0));
    EXPECT_EQ(motor.getState(), MotorState::STOPPED);
}

// TEST 5: Nie można ponownie uruchomić
// już pracującego silnika.
TEST(MotorControllerTest, DoubleStart) {
    MotorController motor;
    motor.initialize();
    motor.start(18.0);

    EXPECT_FALSE(motor.start(18.0));
    EXPECT_EQ(motor.getState(), MotorState::RUNNING);
}

// TEST 6: Polecenie STOP zatrzymuje silnik.
TEST(MotorControllerTest, StopMotor) {
    MotorController motor;
    motor.initialize();
    motor.start(18.0);

    motor.stop();

    EXPECT_EQ(motor.getState(), MotorState::STOPPED);
}


// TEST 7: Normalna temperatura pozwala na pracę.
TEST(MotorControllerTest, NormalTemperature) {
    MotorController motor;
    motor.initialize();

    motor.updateTemperature(89.0);

    EXPECT_TRUE(motor.start(18.0));
    EXPECT_EQ(motor.getState(), MotorState::RUNNING);
}

// TEST 8: Temperatura 90°C wywołuje awarię.
TEST(MotorControllerTest, OverheatAtLimit) {
    MotorController motor;
    motor.initialize();
    motor.start(18.0);

    motor.updateTemperature(90.0);

    EXPECT_EQ(motor.getState(), MotorState::FAULT);
}

// TEST 9: Temperatura powyżej limitu
// wywołuje awarię.
TEST(MotorControllerTest, OverheatAboveLimit) {
    MotorController motor;
    motor.initialize();
    motor.start(18.0);

    motor.updateTemperature(95.0);

    EXPECT_EQ(motor.getState(), MotorState::FAULT);
}

// TEST 10: Nie można uruchomić silnika
// podczas awarii.
TEST(MotorControllerTest, StartDuringFault) {
    MotorController motor;
    motor.initialize();
    motor.updateTemperature(95.0);

    EXPECT_FALSE(motor.start(18.0));
    EXPECT_EQ(motor.getState(), MotorState::FAULT);
}

// TEST 11: Awaria nie znika automatycznie
// po spadku temperatury.
TEST(MotorControllerTest, FaultRemainsAfterCooling) {
    MotorController motor;
    motor.initialize();

    motor.updateTemperature(95.0);
    motor.updateTemperature(80.0);

    EXPECT_EQ(motor.getState(), MotorState::FAULT);
}

// TEST 12: Reset jest możliwy poniżej 85°C.
TEST(MotorControllerTest, ResetAfterCooling) {
    MotorController motor;
    motor.initialize();

    motor.updateTemperature(95.0);
    motor.updateTemperature(80.0);

    EXPECT_TRUE(motor.resetFault());
    EXPECT_EQ(motor.getState(), MotorState::STOPPED);
}

// TEST 13: Reset jest zabroniony
// przy temperaturze 85°C.
TEST(MotorControllerTest, ResetAtThreshold) {
    MotorController motor;
    motor.initialize();

    motor.updateTemperature(95.0);
    motor.updateTemperature(85.0);

    EXPECT_FALSE(motor.resetFault());
    EXPECT_EQ(motor.getState(), MotorState::FAULT);
}

// TEST 14: Reset jest zabroniony
// powyżej progu temperatury.
TEST(MotorControllerTest, ResetAboveThreshold) {
    MotorController motor;
    motor.initialize();

    motor.updateTemperature(95.0);
    motor.updateTemperature(88.0);

    EXPECT_FALSE(motor.resetFault());
    EXPECT_EQ(motor.getState(), MotorState::FAULT);
}


#include <limits>

// TEST 15: Napięcie dokładnie 15 V jest akceptowane.
TEST(MotorControllerTest, VoltageLowerBoundary) {
    MotorController motor;
    motor.initialize();

    EXPECT_TRUE(motor.start(15.0));
    EXPECT_EQ(motor.getState(), MotorState::RUNNING);
}

// TEST 16: Napięcie dokładnie 21 V jest akceptowane.
TEST(MotorControllerTest, VoltageUpperBoundary) {
    MotorController motor;
    motor.initialize();

    EXPECT_TRUE(motor.start(21.0));
    EXPECT_EQ(motor.getState(), MotorState::RUNNING);
}

// TEST 17: Temperatura 89.9°C nie powoduje awarii.
TEST(MotorControllerTest, TemperatureBelowLimit) {
    MotorController motor;
    motor.initialize();
    motor.start(18.0);

    motor.updateTemperature(89.9);

    EXPECT_EQ(motor.getState(), MotorState::RUNNING);
}

// TEST 18: Reset awarii przy 84.9°C jest możliwy.
TEST(MotorControllerTest, ResetBelowThreshold) {
    MotorController motor;
    motor.initialize();

    motor.updateTemperature(95.0);
    motor.updateTemperature(84.9);

    EXPECT_TRUE(motor.resetFault());
    EXPECT_EQ(motor.getState(), MotorState::STOPPED);
}

// TEST 19: Nieprawidłowy odczyt NaN
// powinien spowodować przejście do FAULT.
TEST(MotorControllerTest, InvalidTemperatureNaN) {
    MotorController motor;
    motor.initialize();

    motor.updateTemperature(
        std::numeric_limits<double>::quiet_NaN()
    );

    EXPECT_EQ(motor.getState(), MotorState::FAULT);
}

// TEST 20: Napięcie NaN musi być odrzucone.
TEST(MotorControllerTest, InvalidVoltageNaN) {
    MotorController motor;
    motor.initialize();

    EXPECT_FALSE(motor.start(
        std::numeric_limits<double>::quiet_NaN()
    ));

    EXPECT_EQ(motor.getState(), MotorState::STOPPED);
}

TEST(MotorControllerTest, StartBeforeInitialization) {
    MotorController motor;

    EXPECT_EQ(motor.getState(), MotorState::INIT);
    EXPECT_FALSE(motor.start(18.0));
    EXPECT_EQ(motor.getState(), MotorState::INIT);
}


TEST(MotorControllerTest, InvalidVoltagePositiveInfinity) {
    MotorController motor;
    motor.initialize();

    double voltage = std::numeric_limits<double>::infinity();

    EXPECT_FALSE(motor.start(voltage));
    EXPECT_EQ(motor.getState(), MotorState::STOPPED);
}

TEST(MotorControllerTest, InvalidVoltageNegativeInfinity) {
    MotorController motor;
    motor.initialize();

    double voltage = -std::numeric_limits<double>::infinity();

    EXPECT_FALSE(motor.start(voltage));
    EXPECT_EQ(motor.getState(), MotorState::STOPPED);
}

TEST(MotorControllerTest, InvalidTemperaturePositiveInfinity) {
    MotorController motor;
    motor.initialize();

    double temperature = std::numeric_limits<double>::infinity();

    motor.updateTemperature(temperature);

    EXPECT_EQ(motor.getState(), MotorState::FAULT);
}

TEST(MotorControllerTest, InvalidTemperatureNegativeInfinity) {
    MotorController motor;
    motor.initialize();

    double temperature = -std::numeric_limits<double>::infinity();

    motor.updateTemperature(temperature);

    EXPECT_EQ(motor.getState(), MotorState::FAULT);
}
