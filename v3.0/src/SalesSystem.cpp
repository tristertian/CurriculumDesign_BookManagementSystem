#include "../include/SalesSystem.h"
#include <iostream>

// 构造函数
SalesSystem::SalesSystem(BookManager* manager) : bookManager(manager) {
}

// 析构函数
SalesSystem::~SalesSystem() {
}

// 计算总价
double SalesSystem::calculateTotal(double price, int quantity) const {
    return price * quantity;
}

// 购买图书
bool SalesSystem::purchaseBook(const std::string& isbn, int quantity) {
    if (quantity <= 0) {
        return false;  // 购买数量必须大于0
    }
    
    Book* book = bookManager->findByISBN(isbn);
    if (!book) {
        return false;  // 图书不存在
    }
    
    if (book->getStock() < quantity) {
        return false;  // 库存不足
    }
    
    // 减少库存
    book->setStock(book->getStock() - quantity);
    return true;
}

// 检查库存是否充足
bool SalesSystem::checkStock(const std::string& isbn, int quantity) const {
    if (quantity <= 0) {
        return false;
    }
    
    const Book* book = bookManager->findByISBN(isbn);
    if (!book) {
        return false;  // 图书不存在
    }
    
    return book->getStock() >= quantity;
}

// 获取图书价格
double SalesSystem::getBookPrice(const std::string& isbn) const {
    const Book* book = bookManager->findByISBN(isbn);
    if (!book) {
        return 0.0;  // 图书不存在，返回0
    }
    return book->getPrice();
}

// 计算购买总价
double SalesSystem::getTotalPrice(const std::string& isbn, int quantity) const {
    if (quantity <= 0) {
        return 0.0;
    }
    
    double price = getBookPrice(isbn);
    return calculateTotal(price, quantity);
}
