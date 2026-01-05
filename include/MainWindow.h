#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Multiline_Output.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/fl_ask.H>
#include "BookManager.h"
#include "Sales.h"
#include "Statistics.h"
#include "FileOperations.h"

class MainWindow : public Fl_Window {
private:
    BookManager bookManager;
    Sales sales;
    Statistics statistics;
    FileOperations fileOps;
    
    // UI组件
    Fl_Menu_Bar* menuBar;
    Fl_Multiline_Output* outputDisplay;
    Fl_Text_Buffer* textBuffer;
    
    // 菜单回调
    static void menuCallback(Fl_Widget* w, void* data);
    
    // 功能函数
    void showAddBookDialog();
    void showSearchDialog();
    void showSellDialog();
    void showStatisticsDialog();
    void showAllBooks();
    void saveToFile();
    void loadFromFile();
    
    // 辅助函数
    void updateDisplay(const std::string& message);
    
public:
    MainWindow(int w, int h, const char* title);
    ~MainWindow();
    
    void run() { show(); Fl::run(); }
};

#endif // MAIN_WINDOW_H