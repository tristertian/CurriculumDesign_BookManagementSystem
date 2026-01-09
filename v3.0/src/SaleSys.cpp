#include "../include/SaleSys.h"

SaleSys::SaleSys(BookManager* manager) : bookManager(manager) {}
SaleSys::~SaleSys() {}

// 购买图书
bool SaleSys::purchaseBook(const std::string& isbn, int quantity) {
    Book* book = bookManager->findByISBN(isbn);
    // 猜测可能会有2种找茬的情况，让我来解决一下
    if (!book) {return false; }                 // 图书不存在
    if (isSuft(book, quantity)) {return false;} // 库存不足，或购买数量为负
    
    book->setStock(book->getStock() - quantity);
    return true;
}

// 总消费
double SaleSys::totalConsume(const std::string& isbn, int quantity) const {
    const Book* book = bookManager->findByISBN(isbn);
    if (!book) {return 0.0;}
    if (quantity <= 0) {return 0.0;}
    return book->getPrice() * quantity;
}


// 检查库存是否充足
bool SaleSys::isSuft(const Book* book, int quantity) const {
    if (quantity <= 0) {return false;} 
    return book->getStock() >= quantity;
}
