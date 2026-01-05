#include "include/MainWindow.h"
#include <FL/Fl.H>

int main() {
    // 创建主窗口
    MainWindow window(800, 600, "图书管理系统");
    
    // 运行程序
    window.run();
    
    return 0;
}