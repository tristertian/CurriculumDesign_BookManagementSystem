#ifndef BOOKMANAGER_H
#define BOOKMANAGER_H

#include "Book.h"
#include <vector>
#include <algorithm>
#include <string>
#include <memory>

class BookManager {
private:
    std::vector<std::shared_ptr<Book>> books;
    
    // 检查ISBN是否已存在
    bool isIsbnExists(const std::string& isbn) const;
    
    // 根据ISBN查找图书索引
    int findBookIndexByIsbn(const std::string& isbn) const;

public:
    // 构造函数
    BookManager();
    
    // 析构函数
    ~BookManager();
    
    // 添加图书
    bool addBook(const Book& book);
    
    // 根据ISBN删除图书
    bool deleteBook(const std::string& isbn);
    
    // 根据ISBN更新图书信息
    bool updateBook(const std::string& isbn, const Book& newBook);
    
    // 根据ISBN号查询图书
    std::shared_ptr<Book> findBookByIsbn(const std::string& isbn) const;
    
    // 根据书名查询图书
    std::vector<std::shared_ptr<Book>> findBooksByTitle(const std::string& title) const;
    
    // 根据作者查询图书
    std::vector<std::shared_ptr<Book>> findBooksByAuthor(const std::string& author) const;
    
    // 根据出版社查询图书
    std::vector<std::shared_ptr<Book>> findBooksByPublisher(const std::string& publisher) const;
    
    // 获取所有图书
    std::vector<std::shared_ptr<Book>> getAllBooks() const { return books; }
    
    // 获取图书数量
    int getBookCount() const { return books.size(); }
    
    // 更新库存（销售时使用）
    bool updateStock(const std::string& isbn, int quantity);
    
    // 获取库存量
    int getStock(const std::string& isbn) const;
    
    // 清空所有图书
    void clear();
    
    // 显示所有图书
    void displayAllBooks() const;
    
    // 从文件加载图书
    bool loadFromFile(const std::string& filename);
    
    // 保存图书到文件
    bool saveToFile(const std::string& filename) const;
};

#endif // BOOKMANAGER_H