#!/bin/sh

# Go to the build directory
cd build || exit 1

# Build the project
cmake ..
make

# Return to the project root
cd ..

# Run the program
./build/neuralc
