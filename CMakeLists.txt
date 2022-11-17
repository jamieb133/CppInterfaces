cmake_minimum_required(VERSION 3.16.0)

project(workshop LANGUAGES C CXX ASM)

if(DEFINED TARGET_CMAKE_FILES)
    foreach(f ${TARGET_CMAKE_FILES})
        include("${f}")
    endforeach()
endif()

add_subdirectory(example_app)
