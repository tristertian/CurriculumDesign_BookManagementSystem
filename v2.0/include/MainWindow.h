#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Table.H>
#include <FL/Fl_Message.H>
#include <FL/fl_ask.H>
#include <string>
#include "BookManager.h"
#include "SalesManager.h"
#include "StatisticsManager.h"
#include "FileManager.h"

class MainWindow {
private:
    Fl_Window* window;
    Fl_Menu_Bar* menubar;
    Fl_Text_Display* display;
    Fl_Text_Buffer* buffer;
    
    // 管理器对象
    BookManager* bookManager;
    SalesManager* salesManager;
    StatisticsManager* statisticsManager;
    FileManager* fileManager;
    
    // 回调函数
    static void menu_callback(Fl_Widget* w, void* data);
    static void add_book_callback(Fl_Widget* w, void* data);
    static void search_book_callback(Fl_Widget* w, void* data);
    static void update_book_callback(Fl_Widget* w, void* data);
    static void delete_book_callback(Fl_Widget* w, void* data);
    static void purchase_book_callback(Fl_Widget* w, void* data);
    static void statistics_callback(Fl_Widget* w, void* data);
    static void save_data_callback(Fl_Widget* w, void* data);
    static void load_data_callback(Fl_Widget* w, void* data);
    static void exit_callback(Fl_Widget* w, void* data);
    
    // 辅助函数
    void show_message(const std::string& title, const std::string& message);
    void show_error(const std::string& title, const std::string& message);
    void update_display(const std::string& text);
    
public:
    // 构造函数
    MainWindow(int width, int height, const char* title);
    
    // 析构函数
    ~MainWindow();
    
    // 显示窗口
    void show();
    
    // 获取窗口指针
    Fl_Window* getWindow() { return window; }
};

#endif // MAINWINDOW_H