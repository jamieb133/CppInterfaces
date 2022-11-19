cmake_minimum_required(VERSION 3.19.0)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_BUILD_TYPE debug)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

if(NOT ARDUINO_BUILD)
    add_compile_definitions(LED_PIN=0)
    set(main_sources ${main_sources} ${CMAKE_CURRENT_SOURCE_DIR}/Tickers/SimpleTicker.cpp)
    set(main_sources ${main_sources} ${CMAKE_CURRENT_SOURCE_DIR}/Platform/DesktopPlatform.cpp)
    set(main_sources ${main_sources} ${CMAKE_CURRENT_SOURCE_DIR}/GPIO/FauxGPIO.cpp)
    set(main ${CMAKE_CURRENT_SOURCE_DIR}/Entrypoint/Generic/main.cpp)
    set(test_sources ${test_sources} ${CMAKE_CURRENT_SOURCE_DIR}/unit_test.cpp)
    set(test_sources ${test_sources} ${CMAKE_CURRENT_SOURCE_DIR}/GPIO/test/unit_test.cpp)
else()
    add_compile_definitions(LED_PIN=7)
    set(main_sources ${main_sources} ${CMAKE_CURRENT_SOURCE_DIR}/Tickers/ArduinoTicker.cpp)
    set(main_sources ${main_sources} ${CMAKE_CURRENT_SOURCE_DIR}/Platform/ArduinoPlatform.cpp)
    set(main_sources ${main_sources} ${CMAKE_CURRENT_SOURCE_DIR}/GPIO/ArduinoGPIO.cpp)
    set(main_sources ${main_sources} ${CMAKE_CURRENT_SOURCE_DIR}/Entrypoint/Arduino/main.cpp)
    set(main_sources ${main_sources} ${CMAKE_CURRENT_SOURCE_DIR}/GPIO/FauxGPIO.cpp)
    endif()

message(${main_sources})
add_executable(${TARGET_NAME} ${main_sources} ${main})
set(targets ${targets} ${TARGET_NAME})
target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} 
                                            ${CMAKE_CURRENT_SOURCE_DIR}/src
                                            ${CMAKE_CURRENT_SOURCE_DIR}/..
                                            ${CMAKE_CURRENT_SOURCE_DIR}/GPIO
                                            ${CMAKE_CURRENT_SOURCE_DIR}/Platform
                                            ${CMAKE_CURRENT_SOURCE_DIR}/ExampleApp
                                            ${CMAKE_CURRENT_SOURCE_DIR}/Tickers)


if(ARDUINO_BUILD)
    target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/functional)
    add_avr_core(${TARGET_NAME})
    add_avr_stl(${TARGET_NAME})
    avr_post_build(${TARGET_NAME})
else()
    set(test_sources ${test_sources} ${main_sources})
    add_executable(unit_tests ${test_sources})
    set(targets ${targets} unit_tests)
    target_include_directories(unit_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/GPIO)
    target_include_directories(unit_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Tickers)
    find_package(GTest CONFIG REQUIRED)
    target_link_libraries(unit_tests PRIVATE GTest::gtest)
    target_include_directories(unit_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} 
                                            ${CMAKE_CURRENT_SOURCE_DIR}/src
                                            ${CMAKE_CURRENT_SOURCE_DIR}/..
                                            ${CMAKE_CURRENT_SOURCE_DIR}/GPIO
                                            ${CMAKE_CURRENT_SOURCE_DIR}/Platform
                                            ${CMAKE_CURRENT_SOURCE_DIR}/ExampleApp
                                            ${CMAKE_CURRENT_SOURCE_DIR}/Tickers)
endif()

if(UPLOAD)
        flash_target(${TARGET_NAME})
endif()

set_target_properties(${targets} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
