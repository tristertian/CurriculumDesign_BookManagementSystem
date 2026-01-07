#include "../include/Book.h"
#include <sstream>
#include <iomanip>

// 默认构造函数
Book::Book() : title(""), publisher(""), isbn(""), author(""), stock(0), price(0.0) {}

// 带参数的构造函数
Book::Book(const std::string& title, const std::string& publisher, 
           const std::string& isbn, const std::string& author, 
           int stock, double price)
    : title(title), publisher(publisher), isbn(isbn), author(author), 
      stock(stock), price(price) {}

// 拷贝构造函数
Book::Book(const Book& other)
    : title(other.title), publisher(other.publisher), isbn(other.isbn),
      author(other.author), stock(other.stock), price(other.price) {}

// 赋值运算符重载
Book& Book::operator=(const Book& other) {
    if (this != &other) {
        title = other.title;
        publisher = other.publisher;
        isbn = other.isbn;
        author = other.author;
        stock = other.stock;
        price = other.price;
    }
    return *this;
}

// 析构函数
Book::~Book() {}

// 显示图书信息
void Book::display() const {
    std::cout << "====================================" << std::endl;
    std::cout << "书名: " << title << std::endl;
    std::cout << "出版社: " << publisher << std::endl;
    std::cout << "ISBN号: " << isbn << std::endl;
    std::cout << "作者: " << author << std::endl;
    std::cout << "库存量: " << stock << std::endl;
    std::cout << "价格: ¥" << std::fixed << std::setprecision(2) << price << std::endl;
    std::cout << "====================================" << std::endl;
}

// 获取图书信息的字符串表示
std::string Book::toString() const {
    std::stringstream ss;
    ss << title << "|" << publisher << "|" << isbn << "|" 
       << author << "|" << stock << "|" << std::fixed << std::setprecision(2) << price;
    return ss.str();
}

// 从字符串解析图书信息
bool Book::fromString(const std::string& str) {
    std::stringstream ss(str);
    std::string temp;
    
    if (!std::getline(ss, title, '|')) return false;
    if (!std::getline(ss, publisher, '|')) return false;
    if (!std::getline(ss, isbn, '|')) return false;
    if (!std::getline(ss, author, '|')) return false;
    if (!std::getline(ss, temp, '|')) return false;
    stock = std::stoi(temp);
    if (!(ss >> price)) return false;
    
    return true;
}

// 比较运算符重载（按ISBN号比较）
bool Book::operator<(const Book& other) const {
    return isbn < other.isbn;
}

bool Book::operator==(const Book& other) const {
    return isbn == other.isbn;
}

// 输出流重载
std::ostream& operator<<(std::ostream& os, const Book& book) {
    os << book.toString();
    return os;
}

// 输入流重载
std::istream& operator>>(std::istream& is, Book& book) {
    std::string line;
    if (std::getline(is, line)) {
        book.fromString(line);
    }
    return is;
}