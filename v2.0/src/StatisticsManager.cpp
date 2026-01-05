#include "StatisticsManager.h"
#include <iostream>
#include <iomanip>
#include <map>
#include <algorithm>

// 构造函数
StatisticsManager::StatisticsManager(BookManager* bm, SalesManager* sm) 
    : bookManager(bm), salesManager(sm) {}

// 析构函数
StatisticsManager::~StatisticsManager() {}

// 统计所有图书信息
void StatisticsManager::printAllBooksInfo() const {
    auto books = bookManager->getAllBooks();
    if (books.empty()) {
        std::cout << "书库为空！" << std::endl;
        return;
    }
    
    std::cout << "\n========== 书库所有图书信息 ==========" << std::endl;
    std::cout << "图书总数: " << books.size() << " 种" << std::endl;
    
    // 计算总库存和总价值
    int totalStock = 0;
    double totalValue = 0.0;
    for (const auto& book : books) {
        totalStock += book->getStock();
        totalValue += book->getStock() * book->getPrice();
    }
    
    std::cout << "总库存量: " << totalStock << " 册" << std::endl;
    std::cout << "库存总价值: ¥" << std::fixed << std::setprecision(2) << totalValue << std::endl;
    std::cout << "======================================" << std::endl;
    
    for (const auto& book : books) {
        book->display();
    }
}

// 按价格排序统计（从高到低）
void StatisticsManager::printBooksSortedByPrice() const {
    auto books = bookManager->getAllBooks();
    if (books.empty()) {
        std::cout << "书库为空！" << std::endl;
        return;
    }
    
    // 按价格降序排序
    std::sort(books.begin(), books.end(), 
              [](const std::shared_ptr<Book>& a, const std::shared_ptr<Book>& b) {
                  return a->getPrice() > b->getPrice();
              });
    
    std::cout << "\n========== 按价格排序（从高到低）==========" << std::endl;
    for (const auto& book : books) {
        std::cout << "书名: " << book->getTitle() 
                  << " | 价格: ¥" << std::fixed << std::setprecision(2) << book->getPrice()
                  << " | ISBN: " << book->getIsbn() << std::endl;
    }
}

// 按库存量排序统计（从多到少）
void StatisticsManager::printBooksSortedByStock() const {
    auto books = bookManager->getAllBooks();
    if (books.empty()) {
        std::cout << "书库为空！" << std::endl;
        return;
    }
    
    // 按库存量降序排序
    std::sort(books.begin(), books.end(), 
              [](const std::shared_ptr<Book>& a, const std::shared_ptr<Book>& b) {
                  return a->getStock() > b->getStock();
              });
    
    std::cout << "\n========== 按库存量排序（从多到少）==========" << std::endl;
    for (const auto& book : books) {
        std::cout << "书名: " << book->getTitle() 
                  << " | 库存: " << book->getStock() << " 册"
                  << " | ISBN: " << book->getIsbn() << std::endl;
    }
}

// 按作者统计
void StatisticsManager::printBooksByAuthor() const {
    auto books = bookManager->getAllBooks();
    if (books.empty()) {
        std::cout << "书库为空！" << std::endl;
        return;
    }
    
    std::map<std::string, std::vector<std::shared_ptr<Book>>> authorBooks;
    
    // 按作者分组
    for (const auto& book : books) {
        authorBooks[book->getAuthor()].push_back(book);
    }
    
    std::cout << "\n========== 按作者统计 ==========" << std::endl;
    for (const auto& pair : authorBooks) {
        std::cout << "\n作者: " << pair.first << std::endl;
        std::cout << "图书数量: " << pair.second.size() << " 种" << std::endl;
        for (const auto& book : pair.second) {
            std::cout << "  - " << book->getTitle() 
                      << " (ISBN: " << book->getIsbn() 
                      << ", 库存: " << book->getStock() << " 册)" << std::endl;
        }
    }
}

// 按出版社统计
void StatisticsManager::printBooksByPublisher() const {
    auto books = bookManager->getAllBooks();
    if (books.empty()) {
        std::cout << "书库为空！" << std::endl;
        return;
    }
    
    std::map<std::string, std::vector<std::shared_ptr<Book>>> publisherBooks;
    
    // 按出版社分组
    for (const auto& book : books) {
        publisherBooks[book->getPublisher()].push_back(book);
    }
    
    std::cout << "\n========== 按出版社统计 ==========" << std::endl;
    for (const auto& pair : publisherBooks) {
        std::cout << "\n出版社: " << pair.first << std::endl;
        std::cout << "图书数量: " << pair.second.size() << " 种" << std::endl;
        for (const auto& book : pair.second) {
            std::cout << "  - " << book->getTitle() 
                      << " (ISBN: " << book->getIsbn() 
                      << ", 作者: " << book->getAuthor() << ")" << std::endl;
        }
    }
}

// 获取价格统计信息
StatisticsManager::PriceStats StatisticsManager::getPriceStatistics() const {
    auto books = bookManager->getAllBooks();
    PriceStats stats = {0.0, 0.0, 0.0, 0.0};
    
    if (books.empty()) {
        return stats;
    }
    
    double sum = 0.0;
    int count = books.size();
    stats.maxPrice = books[0]->getPrice();
    stats.minPrice = books[0]->getPrice();
    
    for (const auto& book : books) {
        double price = book->getPrice();
        sum += price;
        stats.totalValue += price * book->getStock();
        
        if (price > stats.maxPrice) stats.maxPrice = price;
        if (price < stats.minPrice) stats.minPrice = price;
    }
    
    stats.avgPrice = sum / count;
    return stats;
}

// 获取库存统计信息
StatisticsManager::StockStats StatisticsManager::getStockStatistics() const {
    auto books = bookManager->getAllBooks();
    StockStats stats = {0, 0, 0, 0, 0.0};
    
    if (books.empty()) {
        return stats;
    }
    
    stats.totalBooks = books.size();
    stats.maxStock = books[0]->getStock();
    stats.minStock = books[0]->getStock();
    
    for (const auto& book : books) {
        int stock = book->getStock();
        stats.totalStock += stock;
        
        if (stock > stats.maxStock) stats.maxStock = stock;
        if (stock < stats.minStock) stats.minStock = stock;
    }
    
    stats.avgStock = static_cast<double>(stats.totalStock) / stats.totalBooks;
    return stats;
}

// 生成综合统计报告
void StatisticsManager::generateReport() const {
    std::cout << "\n========================================" << std::endl;
    std::cout << "          图书管理系统统计报告          " << std::endl;
    std::cout << "========================================" << std::endl;
    
    // 库存统计
    auto stockStats = getStockStatistics();
    std::cout << "\n【库存统计】" << std::endl;
    std::cout << "图书种类总数: " << stockStats.totalBooks << " 种" << std::endl;
    std::cout << "库存总量: " << stockStats.totalStock << " 册" << std::endl;
    std::cout << "最大库存量: " << stockStats.maxStock << " 册" << std::endl;
    std::cout << "最小库存量: " << stockStats.minStock << " 册" << std::endl;
    std::cout << "平均库存量: " << std::fixed << std::setprecision(1) << stockStats.avgStock << " 册" << std::endl;
    
    // 价格统计
    auto priceStats = getPriceStatistics();
    std::cout << "\n【价格统计】" << std::endl;
    std::cout << "最高价格: ¥" << std::fixed << std::setprecision(2) << priceStats.maxPrice << std::endl;
    std::cout << "最低价格: ¥" << priceStats.minPrice << std::endl;
    std::cout << "平均价格: ¥" << priceStats.avgPrice << std::endl;
    std::cout << "库存总价值: ¥" << priceStats.totalValue << std::endl;
    
    // 销售统计
    std::cout << "\n【销售统计】" << std::endl;
    std::cout << "销售记录总数: " << salesManager->getSaleRecordCount() << " 条" << std::endl;
    std::cout << "总销售额: ¥" << std::fixed << std::setprecision(2) << salesManager->getTotalSales() << std::endl;
    
    std::cout << "\n========================================" << std::endl;
}