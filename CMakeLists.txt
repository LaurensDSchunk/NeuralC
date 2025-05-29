cmake_minimum_required(VERSION 3.10)

# Set the project and specify the C language
project(neuralc C)

# Export compile commands for tools like clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# C standards
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Recursively find all .c source files in src/
file(GLOB_RECURSE SRC_FILES src/*.c)

# Define the executable
add_executable(${PROJECT_NAME} ${SRC_FILES})

# Add include directories
target_include_directories(${PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Link libraries here if needed
target_link_libraries(${PROJECT_NAME})
