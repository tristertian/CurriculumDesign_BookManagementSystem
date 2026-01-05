#include "../include/Statistics.h"
#include <algorithm>

Statistics::Statistics(BookManager& bm) : bookManager(bm) {}

bool Statistics::compareByPrice(IBookOperations* a, IBookOperations* b) {
    return a->getPrice() > b->getPrice();
}

bool Statistics::compareByStock(IBookOperations* a, IBookOperations* b) {
    return a->getStock() > b->getStock();
}

bool Statistics::compareByTitle(IBookOperations* a, IBookOperations* b) {
    return a->getTitle() < b->getTitle();
}

std::vector<IBookOperations*> Statistics::sortByPrice(bool descending) {
    auto books = bookManager.getAllBooks();
    std::sort(books.begin(), books.end(), compareByPrice);
    return books;
}

std::vector<IBookOperations*> Statistics::sortByStock(bool descending) {
    auto books = bookManager.getAllBooks();
    std::sort(books.begin(), books.end(), compareByStock);
    return books;
}

std::vector<IBookOperations*> Statistics::getBooksByAuthor(const std::string& author) {
    return bookManager.findByAuthor(author);
}

std::vector<IBookOperations*> Statistics::getBooksByPublisher(const std::string& publisher) {
    return bookManager.findByPublisher(publisher);
}

void Statistics::printAllBooks(std::ostream& os) {
    auto books = bookManager.getAllBooks();
    os << "\n========== 所有图书 ==========\n";
    os << "总数: " << books.size() << "\n\n";
    
    for (auto* book : books) {
        book->displayInfo(os);
        os << "\n";
    }
    os << "==============================\n";
}