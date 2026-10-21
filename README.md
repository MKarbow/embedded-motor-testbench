# Embedded Motor Controller Test Bench

## Overview

A C++17 project focused on automated unit testing of a simulated embedded motor controller.

The project demonstrates requirements-based testing, boundary value analysis, negative testing, regression testing, and defect reporting.

## Technologies

- C++17
- GoogleTest
- CMake
- CTest
- Ninja

## Implemented Features

- Motor state management: INIT, STOPPED, RUNNING, FAULT
- Motor startup and shutdown
- Voltage validation (15–21 V)
- Temperature monitoring
- Overtemperature protection at 90°C
- Fault latching and reset below 85°C
- Validation of non-finite sensor values

## Testing

The project currently contains 25 automated GoogleTest cases covering:

- Normal operation
- Invalid operating conditions
- Boundary values
- State transitions
- Temperature faults
- Invalid sensor measurements (NaN, +Inf, -Inf)

Latest verified result: **25/25 tests passed**.

## Build and Run

Configure:

```powershell
cmake -S . -B build
```

Build:

```powershell
cmake --build build
```

Run unit tests:

```powershell
.\build\motor_tests.exe
```

Run CTest:

```powershell
ctest --test-dir build --output-on-failure
```

## Defects Identified

**BUG-001:** Invalid temperature measurement (NaN) was not detected.

**BUG-002:** Invalid voltage measurement (NaN) was incorrectly accepted.

Both defects were reproduced using automated tests and corrected using `std::isfinite()` validation.

## Documentation

- `docs/requirements.md` — Software requirements
- `docs/traceability-matrix.md` — Requirements-to-test traceability
- `docs/BUG-001.md` — Temperature validation defect
- `docs/BUG-002.md` — Voltage validation defect

## Limitations

The project uses a software simulation and does not interface with physical hardware.

It does not currently include hardware-in-the-loop testing, communication bus testing, or continuous integration.

## Future Improvements

- Additional fault recovery tests
- Sensor timeout simulation
- Continuous integration with GitHub Actions
- Extended state-transition testing
