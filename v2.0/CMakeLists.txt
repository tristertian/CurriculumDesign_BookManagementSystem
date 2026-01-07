cmake_minimum_required(VERSION 3.10)
project(BookManagementSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 头文件目录
include_directories(include)

# 源文件
set(SOURCES
    src/Book.cpp
    src/SaleRecord.cpp
    src/BookManager.cpp
    src/SalesManager.cpp
    src/StatisticsManager.cpp
    src/FileManager.cpp
)

# # 控制台版本
# add_executable(book_console ${SOURCES} src/ConsoleUI.cpp)

# GUI版本
find_package(FLTK)
if(FLTK_FOUND)
    add_executable(${PROJECT_NAME} ${SOURCES} src/main.cpp)
    target_link_libraries(${PROJECT_NAME} ${FLTK_LIBRARIES})
endif()