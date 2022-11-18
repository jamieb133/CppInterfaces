# Introduction to C++ Interfaces (Developer Workshop 2022-11-17)

This repo is intended for the developer workshop presentation on 17th Nov 2022. 
The following topics are covered:

* Dynamic Interfaces (pure virtual)
* Static CRTP Interfaces
* A novel(ish) implementation via static binding

### Prerequisites
* CMake (minimum version 3.16.0)
* C++14 compatible compiler 
* Avr-gcc compiler (to build the Arduino example)

### To build the examples
Modify config.json to point to your local toolchain paths if using the Arduino Uno.
The "clang" config just picks up the default compiler so it might actually detect gcc.
You can add additional cmake variables (e.g. CMAKE_CXX_COMPILER etc) to the relevant bits in the json.
```
# Build for all configs.
python build.py

# Build the Arduino example and upload it.
python build.py --config arduino --upload
```

### Known Issues
* BoostTicker currently needs refactored so isn't integrated into the example apps.
* My implementations of std::function and std::shared_ptr (not supported by ArduinoSTL) are not robust (at the moment...).
* My std::function uses a very inefficient allocation based implementation (see Tom Poole's talk for more info re how to do it properly https://www.youtube.com/watch?v=VY83afAJUIg&t=806s).
