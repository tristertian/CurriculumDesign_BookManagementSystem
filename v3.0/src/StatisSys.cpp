#include "../include/StatisSys.h"

StatisSys::StatisSys(BookManager* manager) : bookManager(manager) {}
StatisSys::~StatisSys() {}

// 获取图书总数
size_t StatisSys::getTotalBooks() const {
    return bookManager->getBookAmount();
}

// 获取总库存量
int StatisSys::getTotalStock() const {
    int totalStock = 0;
    const auto& books = bookManager->getAllBooks();
    for (const auto& book : books) {
        totalStock += book.getStock();
    }
    return totalStock;
}

// 获取特定作者的所有图书
std::vector<Book*> StatisSys::getBooksByAuthor(const std::string& author) {
    return bookManager->findByAuthor(author);
}
// 获取特定出版社的所有图书
std::vector<Book*> StatisSys::getBooksByPublisher(const std::string& publisher) {
    return bookManager->findByPublisher(publisher);
}

// 按价格统计（从大到小）
std::vector<Book*> StatisSys::getBooksSortedByPrice() {
    return bookManager->sortByPrice();
}
// 按库存量统计（从大到小）
std::vector<Book*> StatisSys::getBooksSortedByStock() {
    return bookManager->sortByStock();
}
