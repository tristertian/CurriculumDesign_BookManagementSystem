#ifndef SALESMANAGER_H
#define SALESMANAGER_H

#include "SaleRecord.h"
#include "BookManager.h"
#include <vector>
#include <memory>

class SalesManager {
private:
    std::vector<std::shared_ptr<SaleRecord>> saleRecords;
    BookManager* bookManager;  // 指向图书管理器的指针

public:
    // 构造函数
    SalesManager(BookManager* bm);
    
    // 析构函数
    ~SalesManager();
    
    // 购买图书
    bool purchaseBook(const std::string& isbn, int quantity);
    
    // 获取所有销售记录
    std::vector<std::shared_ptr<SaleRecord>> getAllSaleRecords() const { return saleRecords; }
    
    // 根据ISBN获取销售记录
    std::vector<std::shared_ptr<SaleRecord>> getSaleRecordsByIsbn(const std::string& isbn) const;
    
    // 获取销售记录数量
    int getSaleRecordCount() const { return saleRecords.size(); }
    
    // 计算总销售额
    double getTotalSales() const;
    
    // 显示所有销售记录
    void displayAllSaleRecords() const;
    
    // 清空所有销售记录
    void clear();
    
    // 从文件加载销售记录
    bool loadFromFile(const std::string& filename);
    
    // 保存销售记录到文件
    bool saveToFile(const std::string& filename) const;
};

#endif // SALESMANAGER_H