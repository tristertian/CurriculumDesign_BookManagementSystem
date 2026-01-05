#include <iostream>
#include <string>
#include <limits>
#include "BookManager.h"
#include "SalesManager.h"
#include "StatisticsManager.h"
#include "FileManager.h"

class ConsoleUI {
private:
    BookManager* bookManager;
    SalesManager* salesManager;
    StatisticsManager* statisticsManager;
    FileManager* fileManager;
    
    // 显示主菜单
    void displayMainMenu() {
        std::cout << "\n========================================" << std::endl;
        std::cout << "           图书管理系统主菜单           " << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << "1. 图书管理" << std::endl;
        std::cout << "2. 图书销售" << std::endl;
        std::cout << "3. 统计查询" << std::endl;
        std::cout << "4. 数据存盘" << std::endl;
        std::cout << "5. 读取数据" << std::endl;
        std::cout << "6. 退出系统" << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << "请选择操作: ";
    }
    
    // 显示图书管理菜单
    void displayBookMenu() {
        std::cout << "\n========== 图书管理 ==========" << std::endl;
        std::cout << "1. 添加图书" << std::endl;
        std::cout << "2. 查询图书" << std::endl;
        std::cout << "3. 修改图书" << std::endl;
        std::cout << "4. 删除图书" << std::endl;
        std::cout << "5. 显示所有图书" << std::endl;
        std::cout << "6. 返回主菜单" << std::endl;
        std::cout << "==============================" << std::endl;
        std::cout << "请选择操作: ";
    }
    
    // 显示查询菜单
    void displaySearchMenu() {
        std::cout << "\n========== 图书查询 ==========" << std::endl;
        std::cout << "1. 按ISBN号查询" << std::endl;
        std::cout << "2. 按书名查询" << std::endl;
        std::cout << "3. 按作者查询" << std::endl;
        std::cout << "4. 按出版社查询" << std::endl;
        std::cout << "5. 返回上级菜单" << std::endl;
        std::cout << "==============================" << std::endl;
        std::cout << "请选择操作: ";
    }
    
    // 显示统计菜单
    void displayStatisticsMenu() {
        std::cout << "\n========== 统计查询 ==========" << std::endl;
        std::cout << "1. 显示所有图书" << std::endl;
        std::cout << "2. 按价格排序统计" << std::endl;
        std::cout << "3. 按库存量排序统计" << std::endl;
        std::cout << "4. 按作者统计" << std::endl;
        std::cout << "5. 按出版社统计" << std::endl;
        std::cout << "6. 生成综合统计报告" << std::endl;
        std::cout << "7. 显示销售记录" << std::endl;
        std::cout << "8. 返回主菜单" << std::endl;
        std::cout << "==============================" << std::endl;
        std::cout << "请选择操作: ";
    }
    
    // 添加图书
    void addBook() {
        std::string title, publisher, isbn, author;
        int stock;
        double price;
        
        std::cout << "\n请输入图书信息:" << std::endl;
        std::cout << "书名: ";
        std::cin.ignore();
        std::getline(std::cin, title);
        
        std::cout << "出版社: ";
        std::getline(std::cin, publisher);
        
        std::cout << "ISBN号: ";
        std::getline(std::cin, isbn);
        
        std::cout << "作者: ";
        std::getline(std::cin, author);
        
        std::cout << "库存量: ";
        std::cin >> stock;
        
        std::cout << "价格: ";
        std::cin >> price;
        
        Book newBook(title, publisher, isbn, author, stock, price);
        if (bookManager->addBook(newBook)) {
            std::cout << "图书添加成功！" << std::endl;
        }
    }
    
    // 查询图书
    void searchBook() {
        int choice;
        displaySearchMenu();
        std::cin >> choice;
        
        switch (choice) {
            case 1: { // 按ISBN号查询
                std::string isbn;
                std::cout << "请输入ISBN号: ";
                std::cin.ignore();
                std::getline(std::cin, isbn);
                
                auto book = bookManager->findBookByIsbn(isbn);
                if (book) {
                    std::cout << "\n查询结果:" << std::endl;
                    book->display();
                } else {
                    std::cout << "该编号不存在！" << std::endl;
                }
                break;
            }
            case 2: { // 按书名查询
                std::string title;
                std::cout << "请输入书名: ";
                std::cin.ignore();
                std::getline(std::cin, title);
                
                auto books = bookManager->findBooksByTitle(title);
                if (!books.empty()) {
                    std::cout << "\n查询结果:" << std::endl;
                    for (const auto& book : books) {
                        book->display();
                    }
                } else {
                    std::cout << "该标题不存在！" << std::endl;
                }
                break;
            }
            case 3: { // 按作者查询
                std::string author;
                std::cout << "请输入作者: ";
                std::cin.ignore();
                std::getline(std::cin, author);
                
                auto books = bookManager->findBooksByAuthor(author);
                if (!books.empty()) {
                    std::cout << "\n查询结果:" << std::endl;
                    for (const auto& book : books) {
                        book->display();
                    }
                } else {
                    std::cout << "该作者不存在！" << std::endl;
                }
                break;
            }
            case 4: { // 按出版社查询
                std::string publisher;
                std::cout << "请输入出版社: ";
                std::cin.ignore();
                std::getline(std::cin, publisher);
                
                auto books = bookManager->findBooksByPublisher(publisher);
                if (!books.empty()) {
                    std::cout << "\n查询结果:" << std::endl;
                    for (const auto& book : books) {
                        book->display();
                    }
                } else {
                    std::cout << "该出版社不存在！" << std::endl;
                }
                break;
            }
            case 5:
                return;
            default:
                std::cout << "无效的选择！" << std::endl;
        }
    }
    
    // 修改图书
    void updateBook() {
        std::string isbn;
        std::cout << "请输入要修改的图书ISBN号: ";
        std::cin.ignore();
        std::getline(std::cin, isbn);
        
        auto book = bookManager->findBookByIsbn(isbn);
        if (!book) {
            std::cout << "该编号不存在！" << std::endl;
            return;
        }
        
        std::cout << "\n当前图书信息:" << std::endl;
        book->display();
        
        std::cout << "\n请输入新的图书信息（直接回车保持原值）:" << std::endl;
        std::string title, publisher, author;
        int stock;
        double price;
        
        std::cout << "书名 [" << book->getTitle() << "]: ";
        std::getline(std::cin, title);
        if (title.empty()) title = book->getTitle();
        
        std::cout << "出版社 [" << book->getPublisher() << "]: ";
        std::getline(std::cin, publisher);
        if (publisher.empty()) publisher = book->getPublisher();
        
        std::cout << "作者 [" << book->getAuthor() << "]: ";
        std::getline(std::cin, author);
        if (author.empty()) author = book->getAuthor();
        
        std::cout << "库存量 [" << book->getStock() << "]: ";
        std::string stockStr;
        std::getline(std::cin, stockStr);
        stock = stockStr.empty() ? book->getStock() : std::stoi(stockStr);
        
        std::cout << "价格 [" << book->getPrice() << "]: ";
        std::string priceStr;
        std::getline(std::cin, priceStr);
        price = priceStr.empty() ? book->getPrice() : std::stod(priceStr);
        
        Book updatedBook(title, publisher, isbn, author, stock, price);
        if (bookManager->updateBook(isbn, updatedBook)) {
            std::cout << "图书信息更新成功！" << std::endl;
        }
    }
    
    // 删除图书
    void deleteBook() {
        std::string isbn;
        std::cout << "请输入要删除的图书ISBN号: ";
        std::cin.ignore();
        std::getline(std::cin, isbn);
        
        if (bookManager->deleteBook(isbn)) {
            std::cout << "图书删除成功！" << std::endl;
        }
    }
    
    // 购买图书
    void purchaseBook() {
        std::string isbn;
        int quantity;
        
        std::cout << "请输入要购买的图书ISBN号: ";
        std::cin.ignore();
        std::getline(std::cin, isbn);
        
        auto book = bookManager->findBookByIsbn(isbn);
        if (!book) {
            std::cout << "该编号不存在！" << std::endl;
            return;
        }
        
        std::cout << "图书信息:" << std::endl;
        book->display();
        
        std::cout << "请输入购买数量: ";
        std::cin >> quantity;
        
        if (salesManager->purchaseBook(isbn, quantity)) {
            std::cout << "购买成功！" << std::endl;
        }
    }
    
    // 显示统计信息
    void showStatistics() {
        int choice;
        
        while (true) {
            displayStatisticsMenu();
            std::cin >> choice;
            
            switch (choice) {
                case 1:
                    statisticsManager->printAllBooksInfo();
                    break;
                case 2:
                    statisticsManager->printBooksSortedByPrice();
                    break;
                case 3:
                    statisticsManager->printBooksSortedByStock();
                    break;
                case 4:
                    statisticsManager->printBooksByAuthor();
                    break;
                case 5:
                    statisticsManager->printBooksByPublisher();
                    break;
                case 6:
                    statisticsManager->generateReport();
                    break;
                case 7:
                    salesManager->displayAllSaleRecords();
                    break;
                case 8:
                    return;
                default:
                    std::cout << "无效的选择！" << std::endl;
            }
        }
    }
    
    // 保存数据
    void saveData() {
        if (fileManager->saveAllData(bookManager, salesManager)) {
            std::cout << "数据保存成功！" << std::endl;
        }
    }
    
    // 加载数据
    void loadData() {
        if (fileManager->loadAllData(bookManager, salesManager)) {
            std::cout << "数据加载成功！" << std::endl;
        }
    }
    
public:
    // 构造函数
    ConsoleUI() {
        bookManager = new BookManager();
        salesManager = new SalesManager(bookManager);
        statisticsManager = new StatisticsManager(bookManager, salesManager);
        fileManager = new FileManager();
    }
    
    // 析构函数
    ~ConsoleUI() {
        delete bookManager;
        delete salesManager;
        delete statisticsManager;
        delete fileManager;
    }
    
    // 运行控制台界面
    void run() {
        int choice;
        
        std::cout << "欢迎使用图书管理系统！" << std::endl;
        
        // 尝试自动加载数据
        std::cout << "正在加载数据..." << std::endl;
        fileManager->loadAllData(bookManager, salesManager);
        
        while (true) {
            displayMainMenu();
            std::cin >> choice;
            
            switch (choice) {
                case 1: { // 图书管理
                    while (true) {
                        displayBookMenu();
                        std::cin >> choice;
                        
                        switch (choice) {
                            case 1:
                                addBook();
                                break;
                            case 2:
                                searchBook();
                                break;
                            case 3:
                                updateBook();
                                break;
                            case 4:
                                deleteBook();
                                break;
                            case 5:
                                bookManager->displayAllBooks();
                                break;
                            case 6:
                                goto main_menu;
                            default:
                                std::cout << "无效的选择！" << std::endl;
                        }
                    }
                    break;
                }
                case 2:
                    purchaseBook();
                    break;
                case 3:
                    showStatistics();
                    break;
                case 4:
                    saveData();
                    break;
                case 5:
                    loadData();
                    break;
                case 6:
                    std::cout << "正在保存数据..." << std::endl;
                    fileManager->saveAllData(bookManager, salesManager);
                    std::cout << "感谢使用图书管理系统！再见！" << std::endl;
                    return;
                default:
                    std::cout << "无效的选择！" << std::endl;
            }
            
            main_menu:
            continue;
        }
    }
};

// 控制台版本的主函数
int console_main() {
    ConsoleUI console;
    console.run();
    return 0;
}