#include "../include/Book.h"

Book::Book() : stock(0), price(0.0) {}

Book::Book(const std::string& t, const std::string& p, const std::string& i, 
           const std::string& a, int s, double pr)
    : title(t), publisher(p), isbn(i), author(a), stock(s), price(pr) {}

void Book::displayInfo(std::ostream& os) const {
    os << "书名: " << title << " | 出版社: " << publisher 
       << " | ISBN: " << isbn << " | 作者: " << author 
       << " | 库存: " << stock << " | 价格: ¥" << price;
}

void Book::printDetails(std::ostream& os) const {
    displayInfo(os);
}

std::ostream& operator<<(std::ostream& os, const Book& book) {
    book.displayInfo(os);
    return os;
}

void Book::updateStock(int quantity) {
    stock += quantity;
}

bool Book::reduceStock(int quantity) {
    if (stock >= quantity) {
        stock -= quantity;
        return true;
    }
    return false;
}

// BookDetails序列化实现
void Book::BookDetails::serialize(std::ostream& os) const {
    book->displayInfo(os);
}

void Book::BookDetails::deserialize(std::istream& is) {
    // 实现反序列化逻辑
}