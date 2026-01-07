#ifndef SALESSYSTEM_H
#define SALESSYSTEM_H

#include <string>
#include "BookManager.h"

class SalesSystem {
private:
    BookManager* bookManager;  // 图书管理器指针
    
    // 计算总价
    double calculateTotal(double price, int quantity) const;

public:
    // 构造函数
    explicit SalesSystem(BookManager* manager);
    
    // 析构函数
    ~SalesSystem();
    
    // 购买图书
    bool purchaseBook(const std::string& isbn, int quantity);
    
    // 检查库存是否充足
    bool checkStock(const std::string& isbn, int quantity) const;
    
    // 获取图书价格
    double getBookPrice(const std::string& isbn) const;
    
    // 计算购买总价
    double getTotalPrice(const std::string& isbn, int quantity) const;
};

#endif // SALESSYSTEM_H
