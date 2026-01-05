#include "../include/Sales.h"
#include <iostream>

Sales::Sales(BookManager& bm) : bookManager(bm), totalRevenue(0.0) {}

bool Sales::sellBook(const std::string& isbn, int quantity, double& totalPrice) {
    auto results = bookManager.findByISBN(isbn);
    
    if (results.empty()) {
        return false;
    }
    
    Book* book = dynamic_cast<Book*>(results[0]);
    if (!book) {
        return false;
    }
    
    if (book->getStock() >= quantity) {
        book->reduceStock(quantity);
        totalPrice = book->getPrice() * quantity;
        totalRevenue += totalPrice;
        return true;
    }
    
    return false;
}

void printSalesReport(const Sales& sales) {
    std::cout << "\n========== 销售报告 ==========\n";
    std::cout << "总收入: ¥" << sales.totalRevenue << "\n";
    std::cout << "==============================\n";
}