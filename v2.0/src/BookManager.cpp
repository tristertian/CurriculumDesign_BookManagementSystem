#include "../include/BookManager.h"
#include <fstream>
#include <iostream>
#include <algorithm>

// 构造函数
BookManager::BookManager() {}

// 析构函数
BookManager::~BookManager() {}

// 检查ISBN是否已存在
bool BookManager::isIsbnExists(const std::string& isbn) const {
    return findBookIndexByIsbn(isbn) != -1;
}

// 根据ISBN查找图书索引
int BookManager::findBookIndexByIsbn(const std::string& isbn) const {
    for (size_t i = 0; i < books.size(); ++i) {
        if (books[i]->getIsbn() == isbn) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

// 添加图书
bool BookManager::addBook(const Book& book) {
    if (isIsbnExists(book.getIsbn())) {
        std::cout << "错误：ISBN号 " << book.getIsbn() << " 已存在！" << std::endl;
        return false;
    }
    
    books.push_back(std::make_shared<Book>(book));
    std::cout << "图书添加成功！" << std::endl;
    return true;
}

// 根据ISBN删除图书
bool BookManager::deleteBook(const std::string& isbn) {
    int index = findBookIndexByIsbn(isbn);
    if (index == -1) {
        std::cout << "错误：该编号 " << isbn << " 不存在！" << std::endl;
        return false;
    }
    
    books.erase(books.begin() + index);
    std::cout << "图书删除成功！" << std::endl;
    return true;
}

// 根据ISBN更新图书信息
bool BookManager::updateBook(const std::string& isbn, const Book& newBook) {
    int index = findBookIndexByIsbn(isbn);
    if (index == -1) {
        std::cout << "错误：该编号 " << isbn << " 不存在！" << std::endl;
        return false;
    }
    
    // 如果新ISBN与旧ISBN不同，检查是否已存在
    if (newBook.getIsbn() != isbn && isIsbnExists(newBook.getIsbn())) {
        std::cout << "错误：新ISBN号 " << newBook.getIsbn() << " 已存在！" << std::endl;
        return false;
    }
    
    *books[index] = newBook;
    std::cout << "图书信息更新成功！" << std::endl;
    return true;
}

// 根据ISBN号查询图书
std::shared_ptr<Book> BookManager::findBookByIsbn(const std::string& isbn) const {
    int index = findBookIndexByIsbn(isbn);
    if (index != -1) {
        return books[index];
    }
    return nullptr;
}

// 根据书名查询图书
std::vector<std::shared_ptr<Book>> BookManager::findBooksByTitle(const std::string& title) const {
    std::vector<std::shared_ptr<Book>> result;
    for (const auto& book : books) {
        if (book->getTitle() == title) {
            result.push_back(book);
        }
    }
    return result;
}

// 根据作者查询图书
std::vector<std::shared_ptr<Book>> BookManager::findBooksByAuthor(const std::string& author) const {
    std::vector<std::shared_ptr<Book>> result;
    for (const auto& book : books) {
        if (book->getAuthor() == author) {
            result.push_back(book);
        }
    }
    return result;
}

// 根据出版社查询图书
std::vector<std::shared_ptr<Book>> BookManager::findBooksByPublisher(const std::string& publisher) const {
    std::vector<std::shared_ptr<Book>> result;
    for (const auto& book : books) {
        if (book->getPublisher() == publisher) {
            result.push_back(book);
        }
    }
    return result;
}

// 更新库存（销售时使用）
bool BookManager::updateStock(const std::string& isbn, int quantity) {
    int index = findBookIndexByIsbn(isbn);
    if (index == -1) {
        return false;
    }
    
    int currentStock = books[index]->getStock();
    if (currentStock + quantity < 0) {
        return false; // 库存不足
    }
    
    books[index]->setStock(currentStock + quantity);
    return true;
}

// 获取库存量
int BookManager::getStock(const std::string& isbn) const {
    int index = findBookIndexByIsbn(isbn);
    if (index != -1) {
        return books[index]->getStock();
    }
    return -1;
}

// 清空所有图书
void BookManager::clear() {
    books.clear();
}

// 显示所有图书
void BookManager::displayAllBooks() const {
    if (books.empty()) {
        std::cout << "书库为空！" << std::endl;
        return;
    }
    
    std::cout << "\n当前书库中的图书总数: " << books.size() << std::endl;
    for (const auto& book : books) {
        book->display();
    }
}

// 从文件加载图书
bool BookManager::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "无法打开文件: " << filename << std::endl;
        return false;
    }
    
    books.clear();
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            Book book;
            if (book.fromString(line)) {
                books.push_back(std::make_shared<Book>(book));
            }
        }
    }
    
    file.close();
    std::cout << "从文件加载了 " << books.size() << " 本图书" << std::endl;
    return true;
}

// 保存图书到文件
bool BookManager::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "无法创建文件: " << filename << std::endl;
        return false;
    }
    
    for (const auto& book : books) {
        file << book->toString() << std::endl;
    }
    
    file.close();
    std::cout << "图书信息已保存到文件: " << filename << std::endl;
    return true;
}