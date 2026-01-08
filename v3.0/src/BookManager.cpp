#include "../include/BookManager.h"
#include <algorithm>
#include <fstream>
#include <iostream>

BookManager::BookManager() {}
BookManager::~BookManager() {}

int BookManager::findBookIndex(const std::string& isbn) const {
    for (size_t i = 0; i < books.size(); ++i) {
        if (books[i].getISBN() == isbn) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

bool BookManager::is_ISBNExists(const std::string& isbn) const {
    return findBookIndex(isbn) != -1;
}

// 添加图书
bool BookManager::addBook(const Book& book) {
    // 检查ISBN是否已存在
    if (is_ISBNExists(book.getISBN())) {
        return false;  // ISBN重复，添加失败
    }
    
    books.push_back(book);
    return true;
}

// 根据ISBN查找图书
Book* BookManager::findByISBN(const std::string& isbn) {
    int index = findBookIndex(isbn);
    if (index != -1) {
        return &books[index];
    }
    return nullptr;
}

const Book* BookManager::findByISBN(const std::string& isbn) const {
    int index = findBookIndex(isbn);
    if (index != -1) {
        return &books[index];
    }
    return nullptr;
}

// 根据书名查找图书（支持模糊查询）
std::vector<Book*> BookManager::findByTitle(const std::string& title) {
    std::vector<Book*> result;
    for (auto& book : books) {
        if (book.getTitle().find(title) != std::string::npos) {
            result.push_back(&book);
        }
    }
    return result;
}

std::vector<const Book*> BookManager::findByTitle(const std::string& title) const {
    std::vector<const Book*> result;
    for (const auto& book : books) {
        if (book.getTitle().find(title) != std::string::npos) {
            result.push_back(&book);
        }
    }
    return result;
}

// 根据作者查找图书
std::vector<Book*> BookManager::findByAuthor(const std::string& author) {
    std::vector<Book*> result;
    for (auto& book : books) {
        if (book.getAuthor().find(author) != std::string::npos) {
            result.push_back(&book);
        }
    }
    return result;
}

std::vector<const Book*> BookManager::findByAuthor(const std::string& author) const {
    std::vector<const Book*> result;
    for (const auto& book : books) {
        if (book.getAuthor().find(author) != std::string::npos) {
            result.push_back(&book);
        }
    }
    return result;
}

// 根据出版社查找图书
std::vector<Book*> BookManager::findByPublisher(const std::string& publisher) {
    std::vector<Book*> result;
    for (auto& book : books) {
        if (book.getPublisher().find(publisher) != std::string::npos) {
            result.push_back(&book);
        }
    }
    return result;
}

std::vector<const Book*> BookManager::findByPublisher(const std::string& publisher) const {
    std::vector<const Book*> result;
    for (const auto& book : books) {
        if (book.getPublisher().find(publisher) != std::string::npos) {
            result.push_back(&book);
        }
    }
    return result;
}

// 更新图书信息
bool BookManager::updateBook(const std::string& isbn, const Book& newBook) {
    int index = findBookIndex(isbn);
    if (index == -1) {
        return false;  // 图书不存在
    }
    
    // 如果ISBN改变，检查新的ISBN是否已存在
    if (newBook.getISBN() != isbn && is_ISBNExists(newBook.getISBN())) {
        return false;  // 新的ISBN已存在
    }
    
    books[index] = newBook;
    return true;
}

// 删除图书
bool BookManager::deleteBook(const std::string& isbn) {
    int index = findBookIndex(isbn);
    if (index == -1) {
        return false;  // 图书不存在
    }
    
    books.erase(books.begin() + index);
    return true;
}

// 获取所有图书
std::vector<Book>& BookManager::getAllBooks() {
    return books;
}

const std::vector<Book>& BookManager::getAllBooks() const {
    return books;
}

// 按价格排序（降序）
std::vector<Book*> BookManager::sortByPrice() {
    std::vector<Book*> result;
    for (auto& book : books) {
        result.push_back(&book);
    }
    
    std::sort(result.begin(), result.end(), 
              [](Book* a, Book* b) { return a->getPrice() > b->getPrice(); });
    
    return result;
}

// 按库存量排序（降序）
std::vector<Book*> BookManager::sortByStock() {
    std::vector<Book*> result;
    for (auto& book : books) {
        result.push_back(&book);
    }
    
    std::sort(result.begin(), result.end(), 
              [](Book* a, Book* b) { return a->getStock() > b->getStock(); });
    
    return result;
}

// 获取图书数量
size_t BookManager::getBookCount() const {
    return books.size();
}

// 保存到文件
bool BookManager::saveToFile(const std::string& filename) const {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        return false;
    }
    
    try {
        // 写入文件头
        const char* magic = "BMS\0";
        file.write(magic, 4);
        
        // 写入版本号
        int version = 1;
        file.write(reinterpret_cast<const char*>(&version), sizeof(version));
        
        // 写入图书数量
        int count = static_cast<int>(books.size());
        file.write(reinterpret_cast<const char*>(&count), sizeof(count));
        
        // 写入每本图书
        for (const auto& book : books) {
            file << book;
        }
        
        file.close();
        return true;
    } catch (...) {
        if (file.is_open()) {
            file.close();
        }
        return false;
    }
}

// 从文件加载
bool BookManager::loadFromFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        return false;
    }
    
    try {
        // 读取文件头
        char magic[4];
        file.read(magic, 4);
        if (std::string(magic, 4) != "BMS\0") {
            file.close();
            return false;  // 文件格式错误
        }
        
        // 读取版本号
        int version;
        file.read(reinterpret_cast<char*>(&version), sizeof(version));
        if (version != 1) {
            file.close();
            return false;  // 版本不匹配
        }
        
        // 读取图书数量
        int count;
        file.read(reinterpret_cast<char*>(&count), sizeof(count));
        
        // 清空现有图书
        books.clear();
        
        // 读取每本图书
        for (int i = 0; i < count; ++i) {
            Book book;
            file >> book;
            books.push_back(book);
        }
        
        file.close();
        return true;
    } catch (...) {
        if (file.is_open()) {
            file.close();
        }
        return false;
    }
}

// 清空所有图书
void BookManager::clear() {
    books.clear();
}
