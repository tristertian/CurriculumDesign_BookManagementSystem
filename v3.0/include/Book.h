#ifndef BOOK_H
#define BOOK_H

#include <string>

class Book {
private:
    std::string title;      // 书名
    std::string publisher;  // 出版社
    std::string isbn;       // ISBN号
    std::string author;     // 作者
    int stock;              // 库存量
    double price;           // 价格

public:
    // 默认构造函数
    Book();
    
    // 带参数的构造函数
    Book(const std::string& title, const std::string& publisher, 
         const std::string& isbn, const std::string& author, 
         int stock, double price);
    
    // 拷贝构造函数
    Book(const Book& other);
    
    // 赋值运算符
    Book& operator=(const Book& other);
    
    // 析构函数
    ~Book();
    
    // Getter方法
    std::string getTitle() const;
    std::string getPublisher() const;
    std::string getISBN() const;
    std::string getAuthor() const;
    int getStock() const;
    double getPrice() const;
    
    // Setter方法
    void setTitle(const std::string& title);
    void setPublisher(const std::string& publisher);
    void setISBN(const std::string& isbn);
    void setAuthor(const std::string& author);
    void setStock(int stock);
    void setPrice(double price);
    
    // 转换为字符串表示
    std::string toString() const;
    
    // 友元函数：用于文件读写
    friend std::ostream& operator<<(std::ostream& os, const Book& book);
    friend std::istream& operator>>(std::istream& is, Book& book);
};

#endif // BOOK_H
