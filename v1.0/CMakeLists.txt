cmake_minimum_required(VERSION 3.10)
project(BMS)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find FLTK
find_package(FLTK CONFIG REQUIRED)

# Include directories
include_directories(${FLTK_INCLUDE_DIRS})
include_directories(include)

# Source files
set(SOURCES
    src/Book.cpp
    src/BookManager.cpp
    src/Sales.cpp
    src/Statistics.cpp
    src/FileOperations.cpp
    src/MainWindow.cpp
    main.cpp
)

# Create executable
add_executable(book_management ${SOURCES})

# Link libraries
target_link_libraries(book_management ${FLTK_LIBRARIES})