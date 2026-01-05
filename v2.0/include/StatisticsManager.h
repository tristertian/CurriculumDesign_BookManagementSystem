#ifndef STATISTICSMANAGER_H
#define STATISTICSMANAGER_H

#include "BookManager.h"
#include "SalesManager.h"
#include <vector>
#include <algorithm>
#include <map>

class StatisticsManager {
private:
    BookManager* bookManager;
    SalesManager* salesManager;

public:
    // 构造函数
    StatisticsManager(BookManager* bm, SalesManager* sm);
    
    // 析构函数
    ~StatisticsManager();
    
    // 统计所有图书信息
    void printAllBooksInfo() const;
    
    // 按价格排序统计（从高到低）
    void printBooksSortedByPrice() const;
    
    // 按库存量排序统计（从多到少）
    void printBooksSortedByStock() const;
    
    // 按作者统计
    void printBooksByAuthor() const;
    
    // 按出版社统计
    void printBooksByPublisher() const;
    
    // 生成综合统计报告
    void generateReport() const;
    
    // 获取价格统计信息
    struct PriceStats {
        double maxPrice;
        double minPrice;
        double avgPrice;
        double totalValue;  // 库存总价值
    };
    PriceStats getPriceStatistics() const;
    
    // 获取库存统计信息
    struct StockStats {
        int totalBooks;     // 总图书种类数
        int totalStock;     // 总库存量
        int maxStock;       // 最大库存量
        int minStock;       // 最小库存量
        double avgStock;    // 平均库存量
    };
    StockStats getStockStatistics() const;
};

#endif // STATISTICSMANAGER_H