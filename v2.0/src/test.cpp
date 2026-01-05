#include <iostream>
#include "Book.h"
#include "BookManager.h"
#include "SalesManager.h"
#include "StatisticsManager.h"
#include "FileManager.h"

void testBookClass() {
    std::cout << "=== 测试 Book 类 ===" << std::endl;
    
    // 测试构造函数
    Book book("C++程序设计", "清华大学出版社", "9787302168979", "谭浩强", 10, 59.90);
    
    // 测试getter方法
    std::cout << "书名: " << book.getTitle() << std::endl;
    std::cout << "ISBN: " << book.getIsbn() << std::endl;
    std::cout << "价格: ¥" << book.getPrice() << std::endl;
    
    // 测试序列化
    std::string serialized = book.toString();
    std::cout << "序列化: " << serialized << std::endl;
    
    Book deserialized;
    if (deserialized.fromString(serialized)) {
        std::cout << "反序列化成功" << std::endl;
        deserialized.display();
    }
    
    std::cout << std::endl;
}

void testBookManager() {
    std::cout << "=== 测试 BookManager 类 ===" << std::endl;
    
    BookManager manager;
    
    // 测试添加图书
    Book book1("C++程序设计", "清华大学出版社", "9787302168979", "谭浩强", 10, 59.90);
    Book book2("数据结构与算法", "人民邮电出版社", "9787115458563", "严蔚敏", 5, 45.00);
    
    if (manager.addBook(book1)) {
        std::cout << "✓ 图书1添加成功" << std::endl;
    } else {
        std::cout << "✗ 图书1添加失败" << std::endl;
    }
    
    if (manager.addBook(book2)) {
        std::cout << "✓ 图书2添加成功" << std::endl;
    } else {
        std::cout << "✗ 图书2添加失败" << std::endl;
    }
    
    // 测试重复添加
    if (!manager.addBook(book1)) {
        std::cout << "✓ 重复添加正确失败" << std::endl;
    }
    
    // 测试查询
    auto found = manager.findBookByIsbn("9787302168979");
    if (found) {
        std::cout << "✓ 查询成功" << std::endl;
        found->display();
    }
    
    // 测试更新库存
    if (manager.updateStock("9787302168979", -2)) {
        std::cout << "✓ 库存更新成功" << std::endl;
        std::cout << "当前库存: " << manager.getStock("9787302168979") << std::endl;
    }
    
    // 测试显示所有图书
    std::cout << "所有图书:" << std::endl;
    manager.displayAllBooks();
    
    std::cout << std::endl;
}

void testSalesManager() {
    std::cout << "=== 测试 SalesManager 类 ===" << std::endl;
    
    BookManager bookManager;
    SalesManager salesManager(&bookManager);
    
    // 先添加图书
    Book book("C++程序设计", "清华大学出版社", "9787302168979", "谭浩强", 10, 59.90);
    bookManager.addBook(book);
    
    // 测试购买
    if (salesManager.purchaseBook("9787302168979", 2)) {
        std::cout << "✓ 购买成功" << std::endl;
    }
    
    // 测试库存不足
    if (!salesManager.purchaseBook("9787302168979", 20)) {
        std::cout << "✓ 库存不足正确失败" << std::endl;
    }
    
    // 测试显示销售记录
    salesManager.displayAllSaleRecords();
    
    std::cout << std::endl;
}

void testStatisticsManager() {
    std::cout << "=== 测试 StatisticsManager 类 ===" << std::endl;
    
    BookManager bookManager;
    SalesManager salesManager(&bookManager);
    StatisticsManager statsManager(&bookManager, &salesManager);
    
    // 添加测试数据
    bookManager.addBook(Book("C++程序设计", "清华大学出版社", "9787302168979", "谭浩强", 10, 59.90));
    bookManager.addBook(Book("数据结构与算法", "人民邮电出版社", "9787115458563", "严蔚敏", 5, 45.00));
    bookManager.addBook(Book("Java核心技术", "机械工业出版社", "9787111604732", "Cay S. Horstmann", 12, 119.00));
    
    // 生成一些销售记录
    salesManager.purchaseBook("9787302168979", 2);
    salesManager.purchaseBook("9787115458563", 1);
    
    // 测试各种统计
    std::cout << "按价格排序:" << std::endl;
    statsManager.printBooksSortedByPrice();
    
    std::cout << "按库存量排序:" << std::endl;
    statsManager.printBooksSortedByStock();
    
    std::cout << "按作者统计:" << std::endl;
    statsManager.printBooksByAuthor();
    
    std::cout << "生成综合报告:" << std::endl;
    statsManager.generateReport();
    
    std::cout << std::endl;
}

void testFileManager() {
    std::cout << "=== 测试 FileManager 类 ===" << std::endl;
    
    BookManager bookManager;
    SalesManager salesManager(&bookManager);
    FileManager fileManager;
    
    // 添加测试数据
    bookManager.addBook(Book("C++程序设计", "清华大学出版社", "9787302168979", "谭浩强", 10, 59.90));
    salesManager.purchaseBook("9787302168979", 2);
    
    // 测试保存
    if (fileManager.saveAllData(&bookManager, &salesManager)) {
        std::cout << "✓ 数据保存成功" << std::endl;
    }
    
    // 清空数据
    bookManager.clear();
    salesManager.clear();
    
    // 测试加载
    if (fileManager.loadAllData(&bookManager, &salesManager)) {
        std::cout << "✓ 数据加载成功" << std::endl;
    }
    
    // 验证数据
    std::cout << "验证加载的数据:" << std::endl;
    bookManager.displayAllBooks();
    salesManager.displayAllSaleRecords();
    
    std::cout << std::endl;
}

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "     图书管理系统功能测试" << std::endl;
    std::cout << "========================================" << std::endl;
    
    try {
        testBookClass();
        testBookManager();
        testSalesManager();
        testStatisticsManager();
        testFileManager();
        
        std::cout << "========================================" << std::endl;
        std::cout << "     所有测试完成！" << std::endl;
        std::cout << "========================================" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "测试过程中发生错误: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}