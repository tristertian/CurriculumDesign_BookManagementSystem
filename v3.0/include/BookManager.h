#ifndef BOOKMANAGER_H
#define BOOKMANAGER_H

#include <vector>
#include <string>
#include "Book.h"

class BookManager {
private:
    std::vector<Book> books;
    // 查找图书索引
    int findIndex(const std::string& isbn) const;

public:
    BookManager();
    ~BookManager();
    
    // 添加
    bool addBook(const Book& book);
    
    // 根据ISBN查找
    Book* findByISBN(const std::string& isbn);
    const Book* findByISBN(const std::string& isbn) const;  // 只读性重载
    // 根据书名查找
    std::vector<Book*> findByTitle(const std::string& title);
    std::vector<const Book*> findByTitle(const std::string& title) const;
    // 根据作者查找
    std::vector<Book*> findByAuthor(const std::string& author);
    std::vector<const Book*> findByAuthor(const std::string& author) const;
    // 根据出版社查找
    std::vector<Book*> findByPublisher(const std::string& publisher);
    std::vector<const Book*> findByPublisher(const std::string& publisher) const;

    // 更改图书信息(parameter:欲修改的ISBN + 修改后的图书信息)
    bool updateBook(const std::string& isbn, const Book& newBook);
    
    // 删除
    bool deleteBook(const std::string& isbn);
    
    /*全局功能*/
    std::vector<Book>& getAllBooks();   // 获取所有图书
    const std::vector<Book>& getAllBooks() const;
        
    size_t getBookAmount() const;        // 图书总数
    void clear();                       // 清空所有图书
    /*添加ISBN正确性检查功能？*/
    

    // 按价格排序（降序）
    std::vector<Book*> sortByPrice();
    // 按库存量排序（降序）
    std::vector<Book*> sortByStock();
    
    // 保存到文件
    bool saveFile(const std::string& filename);
    // 从文件加载
    bool loadFile(const std::string& filename);
};

#endif // BOOKMANAGER_H
