#include <FL/Fl.H>
#include "../include/MainWindow.h"

int main(int argc, char** argv) {
    // 创建主窗口
    MainWindow* window = new MainWindow(800, 600, "图书管理系统");
    
    // 显示窗口
    window->show();
    
    // 运行FLTK事件循环
    return Fl::run();
}
