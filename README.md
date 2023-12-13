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
./build/bin/r-type_server [-h/--help | -c/--client | -s/--server] [--ip <ip>] [-p/--port <port>]
```

### Options
    -p, --port    Set the port to listen on (default: 4242)
    --ip          Set the ip to connect to (default: 127.0.0.1) - client only

### Modes
    -h, --help    Display the help menu
    -c, --client  Run as client
    -s, --server  Run as server

## Notes : current state of the project

Right now you need to have SFML and Boost installed on your computer to compile
the project. Windows compatibility has not been tested yet.
The only way to stop the game engine is to kill the process (Ctrl+C).
