# Introduction to C++ Interfaces (Developer Workshop 2022-11-17)

This repo is intended for the developer workshop presentation on 17th Nov 2022. 
The following topics are covered:

* Dynamic Interfaces (pure virtual)
* Static CRTP Interfaces
* A novel(ish) implementation via static binding

### Prerequisites
* CMake (minimum version 3.16.0)
* C++17 compatible compiler

### To build the examples
```
mkdir build && cd build
cmake ..
make
```

### TODO
* Embedded Ticker implementation
* Embedded GPIO implementation
* Static checking of interface compliance for static_binding example.
* Remove compiler warnings in BoostTicker.
