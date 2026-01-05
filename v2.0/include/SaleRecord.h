#ifndef SALERECORD_H
#define SALERECORD_H

#include <string>
#include <ctime>
#include <iostream>
#include <sstream>
#include <iomanip>

class SaleRecord {
private:
    std::string isbn;           // 图书ISBN号
    std::string bookTitle;      // 图书标题
    int quantity;               // 销售数量
    double totalPrice;          // 总价格
    std::string saleTime;       // 销售时间
    
    // 获取当前时间字符串
    std::string getCurrentTime() const;

public:
    // 构造函数
    SaleRecord();
    SaleRecord(const std::string& isbn, const std::string& bookTitle, 
               int quantity, double price);
    
    // 拷贝构造函数
    SaleRecord(const SaleRecord& other);
    
    // 赋值运算符重载
    SaleRecord& operator=(const SaleRecord& other);
    
    // 析构函数
    ~SaleRecord();
    
    // getter方法
    std::string getIsbn() const { return isbn; }
    std::string getBookTitle() const { return bookTitle; }
    int getQuantity() const { return quantity; }
    double getTotalPrice() const { return totalPrice; }
    std::string getSaleTime() const { return saleTime; }
    
    // setter方法
    void setIsbn(const std::string& i) { isbn = i; }
    void setBookTitle(const std::string& t) { bookTitle = t; }
    void setQuantity(int q) { quantity = q; }
    void setTotalPrice(double p) { totalPrice = p; }
    void setSaleTime(const std::string& t) { saleTime = t; }
    
    // 显示销售记录
    void display() const;
    
    // 获取销售记录的字符串表示
    std::string toString() const;
    
    // 从字符串解析销售记录
    bool fromString(const std::string& str);
    
    // 友元函数
    friend std::ostream& operator<<(std::ostream& os, const SaleRecord& record);
    friend std::istream& operator>>(std::istream& is, SaleRecord& record);
};

#endif // SALERECORD_H