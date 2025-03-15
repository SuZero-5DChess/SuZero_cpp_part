cmake_minimum_required(VERSION 3.12)

# Set the project name
project(SuZero VERSION 1.0)

# Specify the C++ standard (C++23 instead of C++14)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# List all source files
set(SOURCES
    suzero_state_5dcengine.cpp
    test.cpp
)

# List all header files
set(HEADERS
    suzero_interface.h
    suzero_state_5dcengine.h
)

# Add executable target with source files
add_executable(suzero_test ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(suzero_test PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Optional: Create a library from your core files
add_library(suzero_lib
    suzero_state_5dcengine.cpp
    ${HEADERS}  # Include headers in the library for IDE visibility
)

# Link the library to the test executable
target_link_libraries(suzero_test PRIVATE suzero_lib)

# Enable testing
enable_testing()
add_test(NAME SuZeroTest COMMAND suzero_test)

# For Xcode: Organize source files into folders
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES} ${HEADERS})

# Set IDE properties for Xcode
set_target_properties(suzero_test PROPERTIES
    XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++2b"  # Xcode-specific C++23 flag
)
