# R-Type

## How to compile the project

Navigate to the root of the project and run the following commands:

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## How to run the project

Navigate to the root of the project and run the following commands:

```bash
./build/bin/r-type_server [-p/--port <port>] [-h/--help]
```
The default port is 4242.

## Notes : current state of the project

Right now you need to have SFML and Boost installed on your computer to compile
the project. Windows compatibility has not been tested yet.
The only way to stop the game engine is to kill the process (Ctrl+C).
