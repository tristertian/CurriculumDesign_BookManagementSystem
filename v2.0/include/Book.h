#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <iostream>
#include <fstream>

class Book {
private:
    std::string title;          // 书名
    std::string publisher;      // 出版社
    std::string isbn;           // ISBN号
    std::string author;         // 作者
    int stock;                  // 库存量
    double price;               // 价格

public:
    // 构造函数
    Book();
    Book(const std::string& title, const std::string& publisher, 
         const std::string& isbn, const std::string& author, 
         int stock, double price);
    
    // 拷贝构造函数
    Book(const Book& other);
    
    // 赋值运算符重载
    Book& operator=(const Book& other);
    
    // 析构函数
    ~Book();
    
    // getter方法
    std::string getTitle() const { return title; }
    std::string getPublisher() const { return publisher; }
    std::string getIsbn() const { return isbn; }
    std::string getAuthor() const { return author; }
    int getStock() const { return stock; }
    double getPrice() const { return price; }
    
    // setter方法
    void setTitle(const std::string& t) { title = t; }
    void setPublisher(const std::string& p) { publisher = p; }
    void setIsbn(const std::string& i) { isbn = i; }
    void setAuthor(const std::string& a) { author = a; }
    void setStock(int s) { stock = s; }
    void setPrice(double p) { price = p; }
    
    // 显示图书信息
    void display() const;
    
    // 获取图书信息的字符串表示
    std::string toString() const;
    
    // 从字符串解析图书信息
    bool fromString(const std::string& str);
    
    // 比较运算符重载（用于排序）
    bool operator<(const Book& other) const;
    bool operator==(const Book& other) const;
    
    // 友元函数 - 输出流
    friend std::ostream& operator<<(std::ostream& os, const Book& book);
    friend std::istream& operator>>(std::istream& is, Book& book);
};

#endif // BOOK_H