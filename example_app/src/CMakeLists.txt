cmake_minimum_required(VERSION 3.19.0)

project(DynamicInterface LANGUAGES C CXX ASM)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_BUILD_TYPE debug)

if(NOT ARDUINO_BUILD)
    set(main_sources ${main_sources} ${CMAKE_CURRENT_SOURCE_DIR}/Tickers/SimpleTicker.cpp)
    set(main_sources ${main_sources} ${CMAKE_CURRENT_SOURCE_DIR}/Platform/DesktopPlatform.cpp)
    set(main_sources ${main_sources} ${CMAKE_CURRENT_SOURCE_DIR}/GPIO/FauxGPIO.cpp)
    set(main_sources ${main_sources} main_pc.cpp)
else()
    set(main_sources ${main_sources} ${CMAKE_CURRENT_SOURCE_DIR}/Tickers/ArduinoTicker.cpp)
    set(main_sources ${main_sources} ${CMAKE_CURRENT_SOURCE_DIR}/Platform/ArduinoPlatform.cpp)
    set(main_sources ${main_sources} ${CMAKE_CURRENT_SOURCE_DIR}/GPIO/ArduinoGPIO.cpp)
    set(main_sources ${main_sources} main_arduino.cpp)
endif()

message(${main_sources})
add_executable(${TARGET_NAME} ${main_sources})
target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} 
                                            ${CMAKE_CURRENT_SOURCE_DIR}/..
                                            ${CMAKE_CURRENT_SOURCE_DIR}/GPIO
                                            ${CMAKE_CURRENT_SOURCE_DIR}/Platform
                                            ${CMAKE_CURRENT_SOURCE_DIR}/Tickers)


if(ARDUINO_BUILD)
    target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/functional)
    add_avr_core(${TARGET_NAME})
    add_avr_stl(${TARGET_NAME})
    avr_post_build(${TARGET_NAME})
endif()

if(UPLOAD)
        flash_target(${TARGET_NAME})
endif()
