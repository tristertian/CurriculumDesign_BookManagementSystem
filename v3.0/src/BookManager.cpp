#include "../include/BookManager.h"
#include <algorithm>
#include <fstream>
#include <iostream>

BookManager::BookManager() {}
BookManager::~BookManager() {}
// 查找图书索引
int BookManager::findIndex(const std::string& isbn) const {
    for (size_t i=0; i<books.size(); ++i) {
        if (books[i].getISBN() == isbn) {
            return static_cast<int>(i); // 'i' is 'index'
        }
    }
    return -1;
}

// 添加图书
bool BookManager::addBook(const Book& book) {
    if (findIndex(book.getISBN()) != -1) {return false;}  // ISBN重复
    
    books.push_back(book);
    return true;    // 为什么要写成布尔函数？方便执行失败时返回错误
}

// 根据ISBN查找图书(Note：已经确保ISBN具有唯一性)
Book* BookManager::findByISBN(const std::string& isbn) {
    int index = findIndex(isbn);
    if (index != -1) {return &books[index];}
    return nullptr;
}

const Book* BookManager::findByISBN(const std::string& isbn) const {
    int index = findIndex(isbn);
    if (index != -1) {return &books[index];}
    return nullptr;
}

// 根据书名查找图书
std::vector<Book*> BookManager::findByTitle(const std::string& title) {
    std::vector<Book*> result;
    for (auto& book : books) {
        if (book.getTitle().find(title) != std::string::npos) {
            result.push_back(&book);
        }   // STAR：模糊查询，如果有字符串片段即查询成功
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
    int index = findIndex(isbn);
    if (index == -1) {return false;}
    
    // 如果ISBN改变，要检查新的ISBN是否已存在
    if (newBook.getISBN() != isbn  &&  findIndex(newBook.getISBN()) != -1) {
        return false;  // 新的ISBN已存在
    }
    
    books[index] = newBook;
    return true;
}

// 删除图书
bool BookManager::deleteBook(const std::string& isbn) {
    int index = findIndex(isbn);
    if (index == -1) {return false;} // 图书不存在
    
    books.erase(books.begin() + index); // vector库函数
    return true;
}


// 获取所有图书
std::vector<Book>& BookManager::getAllBooks()             {return books;}
const std::vector<Book>& BookManager::getAllBooks() const {return books;}
// 图书总数
size_t BookManager::getBookAmount() const {return books.size();}
// 清空所有图书
void BookManager::clear() {books.clear();}


// 按价格排序（decreasing）
std::vector<Book*> BookManager::sortByPrice() {
    std::vector<Book*> result;
    for (auto& book : books) {
        result.push_back(&book);
    }   // 复制一个临时数组
    
    std::sort(result.begin(), result.end(), 
    [](Book* a, Book* b)->bool{return a->getPrice() > b->getPrice();});    // STAR: lambda表达式
    
    return result;
}

// 按库存量排序（decreasing）
std::vector<Book*> BookManager::sortByStock() {
    std::vector<Book*> result;
    for (auto& book : books) {
        result.push_back(&book);
    }
    
    std::sort(result.begin(), result.end(), 
    [](Book* a, Book* b)->bool{return a->getStock() > b->getStock();});
    
    return result;
}

// 保存到文件
bool BookManager::saveFile(const std::string& filename){
    std::ofstream file(filename, std::ios::binary);

    if (!file) {return false;}  // 失败1
    try {
        int amount = static_cast<int>(books.size());    // 图书总数
        file.write(reinterpret_cast<const char*>(&amount), sizeof(amount));
        
        // 写入每本图书
        for (const auto& book : books) {
            file << book;
        }
        
        file.close();

        return true;
    }catch (...) {  // ...代指多种类型的异常
        if (file.is_open()) {
            file.close();
        }
        return false;           // 失败2
    }
}

// 从文件加载
bool BookManager::loadFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);

    if (!file) {return false;}
    try {
        // 读取图书数量
        int amount;
        file.read(reinterpret_cast<char*>(&amount), sizeof(amount));
        
        // 清空现有图书
        books.clear();
        
        // 读取每本图书
        for (int i = 0; i < amount; ++i) {
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
