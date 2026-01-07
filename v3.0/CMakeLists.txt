cmake_minimum_required(VERSION 3.10)
project(BookManagementSystem)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find FLTK
find_package(FLTK REQUIRED)
include_directories(${FLTK_INCLUDE_DIRS})

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Source files
set(SOURCES
    src/Book.cpp
    src/BookManager.cpp
    src/SalesSystem.cpp
    src/StatisticsSystem.cpp
    src/MainWindow.cpp
    src/main.cpp
)

# Create executable
add_executable(BMS ${SOURCES})

# Link libraries
target_link_libraries(BMS ${FLTK_LIBRARIES})

# Set output directory for data files
set_target_properties(BMS PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)

# Create data directory
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/data)
