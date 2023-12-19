# R-Type

This is an Epitech project made by students of the 2026 promotion.
This project aims at creating a network game engine and a game using this engine.

## How to compile the project

Navigate to the root of the project and run the following commands:

```bash
mkdir build
cd build
cmake ..
make
```

## How to run the project

Navigate to the root of the project and run the following commands:

```bash
./build/bin/r-type [-h/--help]
```

### Options
    -h, --help    Display the help menu

## Notes : current state of the project

Right now you need to have SFML installed on your computer to compile
the project. Windows compatibility has not been tested yet.

### License

See the [LICENSE](LICENSE) file for license rights.

### Troubleshooting

## Compilation errors

## Textures not loading, or not loading properly (white squares)

If you have a problem with the textures, make sure you are running CMake from the
build directory under the root of the project. If you are running CMake from the
root of the project or elsewhere, the textures will not be loaded properly.

### Contributors
