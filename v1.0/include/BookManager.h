#ifndef BOOK_MANAGER_H
#define BOOK_MANAGER_H

#include "Book.h"
#include <vector>
#include <memory>
#include <algorithm>

// 多继承示例
class BookManager : public Book::Serializable {
private:
    std::vector<std::unique_ptr<Book>> books;
    
public:
    BookManager() = default;
    ~BookManager() = default;
    
    // 添加图书
    bool addBook(const Book& book);
    
    // 查询功能 - 多态实现
    std::vector<IBookOperations*> findByTitle(const std::string& title);
    std::vector<IBookOperations*> findByISBN(const std::string& isbn);
    std::vector<IBookOperations*> findByAuthor(const std::string& author);
    std::vector<IBookOperations*> findByPublisher(const std::string& publisher);
    
    // 删除
    bool deleteBook(const std::string& isbn);
    
    // 获取所有图书（多态）
    std::vector<IBookOperations*> getAllBooks();
    
    // 清空
    void clear();
    
    // 数量
    size_t getBookCount() const { return books.size(); }
    
    // 友元函数
    friend class Sales;
    friend class Statistics;
    friend class FileOperations;
    
    // Serializable接口实现
    void serialize(std::ostream& os) const override;
    void deserialize(std::istream& is) override;
    
private:
    bool isISBNExists(const std::string& isbn) const;
};

#endif // BOOK_MANAGER_H