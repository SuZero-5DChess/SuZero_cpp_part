cmake_minimum_required(VERSION 3.20)
project(SuZeroCpp VERSION 1.0.0 LANGUAGES CXX)

# Set C++23 standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add the 5dchess_engine subdirectory
add_subdirectory(extern/5dchess_engine)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(SOURCES
    suzero_state_5dcengine.cpp
    test.cpp
)

# List all header files
set(HEADERS
    suzero_interface.h
    suzero_state_5dcengine.h
)

# Create your consumer executable
add_executable(test ${SOURCES})

target_sources(test PRIVATE ${HEADERS})

# Link against the 5dchess_engine library
target_link_libraries(test PRIVATE 5dchess_engine_core)
