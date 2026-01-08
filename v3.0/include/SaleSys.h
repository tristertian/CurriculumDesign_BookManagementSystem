#ifndef SALESYS_H
#define SALESYS_H

#include <string>
#include "BookManager.h"

class SaleSys {
private:
    BookManager* bookManager;   // 使用指针，避免从头建立books对象
    bool isSuft(const std::string& isbn, int quantity) const;   // 库存是否充足
    double singleConsume(const std::string& isbn) const;        // 获取图书价格
public:
    explicit SaleSys(BookManager* manager);
    ~SaleSys();
    
    // 购买图书
    bool purchaseBook(const std::string& isbn, int quantity);
    // 计算购买总价
    double totalConsume(const std::string& isbn, int quantity) const;
};

#endif
