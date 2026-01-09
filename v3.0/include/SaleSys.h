#ifndef SALESYS_H
#define SALESYS_H

#include <string>
#include "BookManager.h"

class SaleSys {
private:
    BookManager* bookManager;   // 使用指针，避免从头建立books对象
    bool isSuft(const Book* book, int quantity) const;   // 库存是否充足
public:
    SaleSys(BookManager* manager);
    ~SaleSys();
    
    // 购买图书
    bool purchaseBook(const std::string& isbn, int quantity);
    // 计算购买总价
    double totalConsume(const std::string& isbn, int quantity) const;
};

#endif
