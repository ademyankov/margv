# C++ Minimalistic Command Line Arguments parser.

The code is just a header under 100 lines of code.


## Files:

- The header is [here](/include/margv/margv.hpp)
- The hello sample application is [here](/apps/hello_margv/src/hello_margv.cpp)

## Build

The code has been built and tested on Windows and Linux using MS Visual Studio
2019 and gcc 9.4.0 on Ubuntu 20.04

### Microsoft Visual Studio

To create Microsoft Visual Studio solution and project files, and build the
solution from PowerShell or CMD:
```sh
mkdir -p build/msvc
cd build/msvc
cmake ../..
cmake --build .
```
Microsoft Visual Studio solution file will be */build/msvc/margv.sln*

### Linux

To build on Linux using make:
```sh
mkdir -p build/x86_64_linux
cd build/x86_64_linux
cmake ../..
make
```
