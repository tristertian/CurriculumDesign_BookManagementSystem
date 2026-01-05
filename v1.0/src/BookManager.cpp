#include "../include/BookManager.h"
#include <fstream>
#include <sstream>

bool BookManager::addBook(const Book& book) {
    if (isISBNExists(book.isbn)) {
        return false;
    }
    
    books.push_back(std::make_unique<Book>(book));
    return true;
}

std::vector<IBookOperations*> BookManager::findByTitle(const std::string& title) {
    std::vector<IBookOperations*> results;
    for (auto& book : books) {
        if (book->title == title) {
            results.push_back(book.get());
        }
    }
    return results;
}

std::vector<IBookOperations*> BookManager::findByISBN(const std::string& isbn) {
    std::vector<IBookOperations*> results;
    for (auto& book : books) {
        if (book->isbn == isbn) {
            results.push_back(book.get());
            break;
        }
    }
    return results;
}

std::vector<IBookOperations*> BookManager::findByAuthor(const std::string& author) {
    std::vector<IBookOperations*> results;
    for (auto& book : books) {
        if (book->author == author) {
            results.push_back(book.get());
        }
    }
    return results;
}

std::vector<IBookOperations*> BookManager::findByPublisher(const std::string& publisher) {
    std::vector<IBookOperations*> results;
    for (auto& book : books) {
        if (book->publisher == publisher) {
            results.push_back(book.get());
        }
    }
    return results;
}

bool BookManager::deleteBook(const std::string& isbn) {
    auto it = std::remove_if(books.begin(), books.end(),
        [&isbn](const std::unique_ptr<Book>& book) {
            return book->isbn == isbn;
        });
    
    if (it != books.end()) {
        books.erase(it, books.end());
        return true;
    }
    return false;
}

std::vector<IBookOperations*> BookManager::getAllBooks() {
    std::vector<IBookOperations*> results;
    for (auto& book : books) {
        results.push_back(book.get());
    }
    return results;
}

void BookManager::clear() {
    books.clear();
}

bool BookManager::isISBNExists(const std::string& isbn) const {
    for (const auto& book : books) {
        if (book->isbn == isbn) {
            return true;
        }
    }
    return false;
}

void BookManager::serialize(std::ostream& os) const {
    os << books.size() << "\n";
    for (const auto& book : books) {
        os << book->title << "\n"
           << book->publisher << "\n"
           << book->isbn << "\n"
           << book->author << "\n"
           << book->stock << "\n"
           << book->price << "\n";
    }
}

void BookManager::deserialize(std::istream& is) {
    size_t count;
    is >> count;
    is.ignore();
    
    books.clear();
    for (size_t i = 0; i < count; ++i) {
        std::string title, publisher, isbn, author;
        int stock;
        double price;
        
        std::getline(is, title);
        std::getline(is, publisher);
        std::getline(is, isbn);
        std::getline(is, author);
        is >> stock;
        is >> price;
        is.ignore();
        
        books.push_back(std::make_unique<Book>(title, publisher, isbn, author, stock, price));
    }
}