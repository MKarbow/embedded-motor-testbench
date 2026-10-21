
cmake_minimum_required(VERSION 3.16)

project(EmbeddedMotorTestBench LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_MakeAvailable(googletest)

add_executable(motor_sim
    main.cpp
    MotorController.cpp
)

enable_testing()

add_executable(motor_tests
    tests/test_motor.cpp
    MotorController.cpp
)

target_include_directories(motor_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(motor_tests PRIVATE
    GTest::gtest_main
)

add_test(
    NAME MotorControllerTests
    COMMAND motor_tests
)