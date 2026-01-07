#include "../include/SaleRecord.h"
#include <chrono>

// 获取当前时间字符串
std::string SaleRecord::getCurrentTime() const {
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    auto tm = *std::localtime(&time_t);
    
    std::stringstream ss;
    ss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

// 默认构造函数
SaleRecord::SaleRecord() : isbn(""), bookTitle(""), quantity(0), totalPrice(0.0) {
    saleTime = getCurrentTime();
}

// 带参数的构造函数
SaleRecord::SaleRecord(const std::string& isbn, const std::string& bookTitle, 
                       int quantity, double price)
    : isbn(isbn), bookTitle(bookTitle), quantity(quantity) {
    totalPrice = quantity * price;
    saleTime = getCurrentTime();
}

// 拷贝构造函数
SaleRecord::SaleRecord(const SaleRecord& other)
    : isbn(other.isbn), bookTitle(other.bookTitle), quantity(other.quantity),
      totalPrice(other.totalPrice), saleTime(other.saleTime) {}

// 赋值运算符重载
SaleRecord& SaleRecord::operator=(const SaleRecord& other) {
    if (this != &other) {
        isbn = other.isbn;
        bookTitle = other.bookTitle;
        quantity = other.quantity;
        totalPrice = other.totalPrice;
        saleTime = other.saleTime;
    }
    return *this;
}

// 析构函数
SaleRecord::~SaleRecord() {}

// 显示销售记录
void SaleRecord::display() const {
    std::cout << "====================================" << std::endl;
    std::cout << "ISBN: " << isbn << std::endl;
    std::cout << "书名: " << bookTitle << std::endl;
    std::cout << "销售数量: " << quantity << std::endl;
    std::cout << "总价格: ¥" << std::fixed << std::setprecision(2) << totalPrice << std::endl;
    std::cout << "销售时间: " << saleTime << std::endl;
    std::cout << "====================================" << std::endl;
}

// 获取销售记录的字符串表示
std::string SaleRecord::toString() const {
    std::stringstream ss;
    ss << isbn << "|" << bookTitle << "|" << quantity << "|" 
       << std::fixed << std::setprecision(2) << totalPrice << "|" << saleTime;
    return ss.str();
}

// 从字符串解析销售记录
bool SaleRecord::fromString(const std::string& str) {
    std::stringstream ss(str);
    std::string temp;
    
    if (!std::getline(ss, isbn, '|')) return false;
    if (!std::getline(ss, bookTitle, '|')) return false;
    if (!std::getline(ss, temp, '|')) return false;
    quantity = std::stoi(temp);
    if (!std::getline(ss, temp, '|')) return false;
    totalPrice = std::stod(temp);
    if (!std::getline(ss, saleTime)) return false;
    
    return true;
}

// 输出流重载
std::ostream& operator<<(std::ostream& os, const SaleRecord& record) {
    os << record.toString();
    return os;
}

// 输入流重载
std::istream& operator>>(std::istream& is, SaleRecord& record) {
    std::string line;
    if (std::getline(is, line)) {
        record.fromString(line);
    }
    return is;
}