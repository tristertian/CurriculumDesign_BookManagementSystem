#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Table_Row.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Box.H>
#include <string>
#include "BookManager.h"
#include "SaleSys.h"
#include "StatisSys.h"

class MainWindow : public Fl_Window {
private:
    // 系统组件
    BookManager* bookManager;
    SaleSys* SaleSys;
    StatisSys* statsSystem;
    
    // UI组件
    Fl_Button* addButton;
    Fl_Button* searchButton;
    Fl_Button* updateButton;
    Fl_Button* deleteButton;
    Fl_Button* purchaseButton;
    Fl_Button* statsButton;
    Fl_Button* saveButton;
    Fl_Button* loadButton;
    Fl_Button* clearButton;
    
    // 输入框
    Fl_Input* isbnInput;
    Fl_Input* titleInput;
    Fl_Input* authorInput;
    Fl_Input* publisherInput;
    Fl_Input* stockInput;
    Fl_Input* priceInput;
    Fl_Input* searchInput;
    Fl_Input* purchaseIsbnInput;
    Fl_Input* purchaseQuantityInput;
    
    // 显示区域
    Fl_Text_Display* resultDisplay;
    Fl_Text_Buffer* resultBuffer;
    Fl_Table_Row* bookTable;
    
    // 当前选中图书的ISBN
    std::string selectedISBN;
    
public:
    // 获取图书管理器（供表格类使用）
    BookManager* getBookManager() { return bookManager; }
    
private:
    // 私有方法
    void setupUI();  // 设置UI界面
    void setupCallbacks();  // 设置回调函数
    void updateTable();  // 更新表格显示
    void clearInputs();  // 清空输入框
    void showMessage(const std::string& message);  // 显示消息
    void showError(const std::string& message);    // 显示错误
    void selectBook(int row);  // 选择图书
    
    // 回调函数
    static void onAddBook(Fl_Widget* w, void* data);
    static void onSearchBook(Fl_Widget* w, void* data);
    static void onUpdateBook(Fl_Widget* w, void* data);
    static void onDeleteBook(Fl_Widget* w, void* data);
    static void onPurchaseBook(Fl_Widget* w, void* data);
    static void onShowStats(Fl_Widget* w, void* data);
    static void onSaveData(Fl_Widget* w, void* data);
    static void onLoadData(Fl_Widget* w, void* data);
    static void onClearInputs(Fl_Widget* w, void* data);
    static void onTableSelect(Fl_Widget* w, void* data);
    static void onTableContext(Fl_Widget* w, void* data);

public:
    // 构造函数
    MainWindow(int width, int height, const char* title);
    
    // 析构函数
    ~MainWindow();
    
    // 显示窗口
    void show();
    
    // 处理添加图书
    void handleAddBook();
    
    // 处理查询图书
    void handleSearchBook();
    
    // 处理修改图书
    void handleUpdateBook();
    
    // 处理删除图书
    void handleDeleteBook();
    
    // 处理购买图书
    void handlePurchaseBook();
    
    // 处理统计显示
    void handleStatistics();
    
    // 处理保存数据
    void handleSave();
    
    // 处理加载数据
    void handleLoad();
};

#endif // MAINWINDOW_H
