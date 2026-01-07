#ifndef BOOKMANAGER_H
#define BOOKMANAGER_H

#include <vector>
#include <string>
#include "Book.h"

class BookManager {
private:
    std::vector<Book> books;  // 图书容器
    
    // 检查ISBN是否已存在
    bool isISBNExists(const std::string& isbn) const;
    
    // 查找图书索引
    int findBookIndex(const std::string& isbn) const;

public:
    // 构造函数
    BookManager();
    
    // 析构函数
    ~BookManager();
    
    // 添加图书
    bool addBook(const Book& book);
    
    // 根据ISBN查找图书
    Book* findByISBN(const std::string& isbn);
    const Book* findByISBN(const std::string& isbn) const;
    
    // 根据书名查找图书（支持模糊查询）
    std::vector<Book*> findByTitle(const std::string& title);
    std::vector<const Book*> findByTitle(const std::string& title) const;
    
    // 根据作者查找图书
    std::vector<Book*> findByAuthor(const std::string& author);
    std::vector<const Book*> findByAuthor(const std::string& author) const;
    
    // 根据出版社查找图书
    std::vector<Book*> findByPublisher(const std::string& publisher);
    std::vector<const Book*> findByPublisher(const std::string& publisher) const;
    
    // 更新图书信息
    bool updateBook(const std::string& isbn, const Book& newBook);
    
    // 删除图书
    bool deleteBook(const std::string& isbn);
    
    // 获取所有图书
    std::vector<Book>& getAllBooks();
    const std::vector<Book>& getAllBooks() const;
    
    // 按价格排序（降序）
    std::vector<Book*> sortByPrice();
    
    // 按库存量排序（降序）
    std::vector<Book*> sortByStock();
    
    // 获取图书数量
    size_t getBookCount() const;
    
    // 保存到文件
    bool saveToFile(const std::string& filename) const;
    
    // 从文件加载
    bool loadFromFile(const std::string& filename);
    
    // 清空所有图书
    void clear();
};

#endif // BOOKMANAGER_H
