#include <FL/Fl.H>
#include "../include/MainWindow.h"

int main(int argc, char** argv) {
    MainWindow* window = new MainWindow(800, 600, "图书管理系统");
    window->show();
    return Fl::run();// 运行FLTK事件循环
}
