#include "SalesManager.h"
#include <iostream>
#include <fstream>

// 构造函数
SalesManager::SalesManager(BookManager* bm) : bookManager(bm) {}

// 析构函数
SalesManager::~SalesManager() {}

// 购买图书
bool SalesManager::purchaseBook(const std::string& isbn, int quantity) {
    if (quantity <= 0) {
        std::cout << "错误：购买数量必须大于0！" << std::endl;
        return false;
    }
    
    // 查找图书
    auto book = bookManager->findBookByIsbn(isbn);
    if (!book) {
        std::cout << "错误：该编号 " << isbn << " 不存在！" << std::endl;
        return false;
    }
    
    // 检查库存
    int currentStock = book->getStock();
    if (currentStock < quantity) {
        std::cout << "错误：库存不足！当前库存：" << currentStock 
                  << "，购买数量：" << quantity << std::endl;
        return false;
    }
    
    // 更新库存
    if (!bookManager->updateStock(isbn, -quantity)) {
        std::cout << "错误：库存更新失败！" << std::endl;
        return false;
    }
    
    // 创建销售记录
    auto saleRecord = std::make_shared<SaleRecord>(
        isbn, book->getTitle(), quantity, book->getPrice()
    );
    
    saleRecords.push_back(saleRecord);
    
    std::cout << "购买成功！" << std::endl;
    std::cout << "图书: " << book->getTitle() << std::endl;
    std::cout << "数量: " << quantity << std::endl;
    std::cout << "总价: ¥" << saleRecord->getTotalPrice() << std::endl;
    
    return true;
}

// 根据ISBN获取销售记录
std::vector<std::shared_ptr<SaleRecord>> SalesManager::getSaleRecordsByIsbn(const std::string& isbn) const {
    std::vector<std::shared_ptr<SaleRecord>> result;
    for (const auto& record : saleRecords) {
        if (record->getIsbn() == isbn) {
            result.push_back(record);
        }
    }
    return result;
}

// 计算总销售额
double SalesManager::getTotalSales() const {
    double total = 0.0;
    for (const auto& record : saleRecords) {
        total += record->getTotalPrice();
    }
    return total;
}

// 显示所有销售记录
void SalesManager::displayAllSaleRecords() const {
    if (saleRecords.empty()) {
        std::cout << "没有销售记录！" << std::endl;
        return;
    }
    
    std::cout << "\n销售记录总数: " << saleRecords.size() << std::endl;
    std::cout << "总销售额: ¥" << getTotalSales() << std::endl;
    std::cout << "====================================" << std::endl;
    
    for (const auto& record : saleRecords) {
        record->display();
    }
}

// 清空所有销售记录
void SalesManager::clear() {
    saleRecords.clear();
}

// 从文件加载销售记录
bool SalesManager::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "无法打开文件: " << filename << std::endl;
        return false;
    }
    
    saleRecords.clear();
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            SaleRecord record;
            if (record.fromString(line)) {
                saleRecords.push_back(std::make_shared<SaleRecord>(record));
            }
        }
    }
    
    file.close();
    std::cout << "从文件加载了 " << saleRecords.size() << " 条销售记录" << std::endl;
    return true;
}

// 保存销售记录到文件
bool SalesManager::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "无法创建文件: " << filename << std::endl;
        return false;
    }
    
    for (const auto& record : saleRecords) {
        file << record->toString() << std::endl;
    }
    
    file.close();
    std::cout << "销售记录已保存到文件: " << filename << std::endl;
    return true;
}