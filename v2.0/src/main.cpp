#include <iostream>
#include <FL/Fl.H>
#include "MainWindow.h"

int main(int argc, char* argv[]) {
    std::cout << "========================================" << std::endl;
    std::cout << "     图书管理系统 v1.0" << std::endl;
    std::cout << "     基于C++面向对象编程" << std::endl;
    std::cout << "========================================" << std::endl;
    
    try {
        // 创建主窗口
        MainWindow* mainWindow = new MainWindow(800, 600, "图书管理系统");
        
        // 显示窗口
        mainWindow->show();
        
        // 运行FLTK事件循环
        return Fl::run();
    } catch (const std::exception& e) {
        std::cerr << "程序运行错误: " << e.what() << std::endl;
        return 1;
    }
}