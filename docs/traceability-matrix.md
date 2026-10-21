# Requirements Traceability Matrix (RTM)

**Project:** Embedded Motor Controller Test Bench  
**Version:** 1.0  
**Test Framework:** GoogleTest  
**Baseline:** 20 automated unit tests

## 1. Purpose

This document maps software requirements to automated test cases and identifies verification gaps.

Coverage status definitions:

- **Covered:** Existing tests verify the documented behavior.
- **Partial:** Existing tests verify only part of the requirement.
- **Not Covered:** No dedicated automated test verifies the requirement.

## 2. Requirements-to-Test Traceability

| Requirement | GoogleTest Test Cases | Coverage |
|---|---|---|
| REQ-001 — Initial State | Initialization | Covered |
| REQ-002 — Initialization | Initialization | Covered |
| REQ-003 — Valid Startup | ValidVoltage, VoltageLowerBoundary, VoltageUpperBoundary, NormalTemperature | Covered |
| REQ-004 — Invalid Startup State | DoubleStart, StartBeforeInitialization | Partial |
| REQ-005 — Motor Shutdown | StopMotor | Covered |
| REQ-006 — Minimum Voltage | LowVoltage | Covered |
| REQ-007 — Maximum Voltage | HighVoltage | Covered |
| REQ-008 — Non-finite Voltage | InvalidVoltageNaN, InvalidVoltagePositiveInfinity, InvalidVoltageNegativeInfinity | Covered |
| REQ-009 — Normal Temperature | NormalTemperature, TemperatureBelowLimit | Covered |
| REQ-010 — Overtemperature Protection | OverheatAtLimit, OverheatAboveLimit | Covered |
| REQ-011 — Non-finite Temperature | InvalidTemperatureNaN, InvalidTemperaturePositiveInfinity, InvalidTemperatureNegativeInfinity | Covered |
| REQ-012 — Startup Inhibition During Fault | StartDuringFault | Covered |
| REQ-013 — Fault Latching | FaultRemainsAfterCooling | Covered |
| REQ-014 — Reset Temperature | ResetAfterCooling, ResetBelowThreshold, ResetAtThreshold, ResetAboveThreshold | Covered |
| REQ-015 — Successful Fault Reset | ResetAfterCooling | Covered |
| REQ-016 — Invalid Fault Reset | ResetAtThreshold, ResetAboveThreshold | Partial |

## 3. Identified Verification Gaps

**GAP-001 — Initial State**

Verify that a newly constructed controller is in `INIT` before initialization.

**GAP-002 — Startup State Restrictions**

Verify startup rejection in `INIT`, not only in `RUNNING` and `FAULT`.

**GAP-003 — Non-finite Voltage Values**

Add dedicated tests for positive and negative infinity.

**GAP-004 — Non-finite Temperature Values**

Add dedicated tests for positive and negative infinity.

**GAP-005 — Invalid Fault Reset**

Verify that fault reset is rejected when the controller is not in `FAULT` and when the latest temperature reading is invalid.

## 4. Verification Summary

- Requirements: 16
- Automated test cases: 20
- Covered requirements: 11
- Partially covered requirements: 5
- Not covered requirements: 0

**Note:** Coverage is based on the documented test scenarios, not on statement, branch, or MC/DC code coverage. Partial requirements must not be reported as fully verified.

## 5. Next Actions

1. Implement automated tests addressing GAP-001 through GAP-005.
2. Execute the regression test suite.
3. Investigate and document any failures.
4. Update this matrix based on verified test results.
