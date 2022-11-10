cmake_minimum_required(VERSION 3.16.0)
project(DynamicInterface)

set( Boost_USE_STATIC_LIBS ON )
set( Boost_USE_MULTITHREADED ON )
find_package( Boost 1.57.0 COMPONENTS filesystem thread REQUIRED)
link_directories(${Boost_LIBRARY_DIRS})

set(CMAKE_BUILD_TYPE debug)

file(GLOB tickers ${CMAKE_CURRENT_SOURCE_DIR}/Tickers/*.cpp)
file(GLOB gpio ${CMAKE_CURRENT_SOURCE_DIR}/GPIO/*.cpp)
set(sources ${tickers} ${gpio} main.cpp)
add_executable(dynamic ${sources})
target_include_directories(dynamic PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} 
                                            ${CMAKE_CURRENT_SOURCE_DIR}/GPIO
                                            ${CMAKE_CURRENT_SOURCE_DIR}/Tickers
                                            ${Boost_INCLUDE_DIRS})


target_link_libraries(dynamic PRIVATE "boost_system" Boost::thread)
set_property(TARGET dynamic PROPERTY CXX_STANDARD 17)