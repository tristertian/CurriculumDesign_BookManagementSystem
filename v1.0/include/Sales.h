#ifndef SALES_H
#define SALES_H

#include "BookManager.h"
#include <string>

class Sales {
private:
    BookManager& bookManager;
    double totalRevenue;
    
public:
    explicit Sales(BookManager& bm);
    
    // 销售功能
    bool sellBook(const std::string& isbn, int quantity, double& totalPrice);
    
    // 获取总收入
    double getTotalRevenue() const { return totalRevenue; }
    
    // 重置收入
    void resetRevenue() { totalRevenue = 0.0; }
    
    // 友元函数 - 允许访问私有成员
    friend void printSalesReport(const Sales& sales);
};

// 友元函数实现
void printSalesReport(const Sales& sales);

#endif // SALES_H