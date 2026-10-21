# Embedded Motor Controller — Software Requirements

**Project:** Embedded Motor Controller Test Bench  
**Document Version:** 1.0  
**Status:** Draft  
**Verification Method:** Automated unit testing with GoogleTest

## 1. Purpose

This document defines the functional and safety-related requirements for a simulated embedded motor controller.

The controller manages motor initialization, startup, shutdown, voltage validation, temperature monitoring, and fault recovery.

The requirements provide a basis for automated verification and traceability between expected behavior and test cases.

## 2. Motor State Management

**REQ-001 — Initial State**

The motor controller shall enter the `INIT` state upon object creation.

**REQ-002 — Initialization**

Calling `initialize()` from the `INIT` state shall transition the controller to `STOPPED`.

**REQ-003 — Valid Startup**

The controller shall allow startup from `STOPPED` when the supplied voltage is within the inclusive range of 15.0 V to 21.0 V and the temperature is below 90°C.

**REQ-004 — Invalid Startup State**

The controller shall reject startup attempts when its state is not `STOPPED`.

**REQ-005 — Motor Shutdown**

Calling `stop()` while the motor is `RUNNING` shall transition the controller to `STOPPED`.

## 3. Voltage Validation

**REQ-006 — Minimum Operating Voltage**

The controller shall reject startup when the voltage is below 15.0 V.

**REQ-007 — Maximum Operating Voltage**

The controller shall reject startup when the voltage exceeds 21.0 V.

**REQ-008 — Invalid Voltage Measurements**

The controller shall reject non-finite voltage values, including `NaN`, positive infinity, and negative infinity.

Rejected startup attempts caused by invalid voltage shall not transition the controller to `RUNNING`.

## 4. Temperature Monitoring

**REQ-009 — Normal Operating Temperature**

A valid temperature measurement below 90°C shall not independently trigger an overtemperature fault.

**REQ-010 — Overtemperature Protection**

When a temperature measurement reaches or exceeds 90°C, the controller shall transition to `FAULT`.

**REQ-011 — Invalid Temperature Measurements**

The controller shall transition to `FAULT` when a temperature measurement is non-finite, including `NaN`, positive infinity, or negative infinity.

## 5. Fault Handling and Recovery

**REQ-012 — Startup Inhibition During Fault**

The controller shall reject startup attempts while in the `FAULT` state.

**REQ-013 — Fault Latching**

The controller shall remain in `FAULT` after the temperature falls below the overtemperature threshold until an explicit successful fault reset is performed.

**REQ-014 — Fault Reset Temperature**

The controller shall allow a fault reset only when the latest valid temperature measurement is strictly below 85°C.

**REQ-015 — Fault Reset Behavior**

A successful fault reset shall transition the controller from `FAULT` to `STOPPED`.

**REQ-016 — Fault Reset Rejection**

A fault reset shall be rejected if the controller is not in `FAULT` or the latest temperature measurement is invalid or greater than or equal to 85°C.

## 6. Verification

Each requirement shall be associated with one or more automated test cases.

Test results shall be classified as:

- **PASS:** Observed behavior matches the requirement.
- **FAIL:** Observed behavior violates the requirement.
- **NOT TESTED:** No verification has been executed.

A separate traceability matrix will map requirements to GoogleTest test cases.

## 7. Scope and Limitations

This project simulates the software behavior of an embedded motor controller.

It does not currently interact with physical motor hardware, real sensors, PWM peripherals, or communication buses.

The defined operating thresholds are project assumptions and are not intended to represent certified hardware safety limits.
