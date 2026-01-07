#include "../include/Book.h"
#include <sstream>

// 默认构造函数
Book::Book() : stock(0), price(0.0) {
}

// 带参数的构造函数
Book::Book(const std::string& title, const std::string& publisher, 
           const std::string& isbn, const std::string& author, 
           int stock, double price) 
    : title(title), publisher(publisher), isbn(isbn), author(author), 
      stock(stock), price(price) {
}

// 拷贝构造函数
Book::Book(const Book& other) 
    : title(other.title), publisher(other.publisher), isbn(other.isbn), 
      author(other.author), stock(other.stock), price(other.price) {
}

// 赋值运算符
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
Book::~Book() {
}

// Getter方法
std::string Book::getTitle() const {
    return title;
}

std::string Book::getPublisher() const {
    return publisher;
}

std::string Book::getISBN() const {
    return isbn;
}

std::string Book::getAuthor() const {
    return author;
}

int Book::getStock() const {
    return stock;
}

double Book::getPrice() const {
    return price;
}

// Setter方法
void Book::setTitle(const std::string& title) {
    this->title = title;
}

void Book::setPublisher(const std::string& publisher) {
    this->publisher = publisher;
}

void Book::setISBN(const std::string& isbn) {
    this->isbn = isbn;
}

void Book::setAuthor(const std::string& author) {
    this->author = author;
}

void Book::setStock(int stock) {
    this->stock = stock;
}

void Book::setPrice(double price) {
    this->price = price;
}

// 转换为字符串表示
std::string Book::toString() const {
    std::stringstream ss;
    ss << "ISBN: " << isbn << ", 书名: " << title 
       << ", 作者: " << author << ", 出版社: " << publisher
       << ", 库存: " << stock << ", 价格: ¥" << price;
    return ss.str();
}

// 友元函数：用于文件读写
std::ostream& operator<<(std::ostream& os, const Book& book) {
    // 写入ISBN长度和字符串
    size_t isbnLength = book.isbn.length();
    os.write(reinterpret_cast<const char*>(&isbnLength), sizeof(isbnLength));
    os.write(book.isbn.c_str(), isbnLength);
    
    // 写入书名长度和字符串
    size_t titleLength = book.title.length();
    os.write(reinterpret_cast<const char*>(&titleLength), sizeof(titleLength));
    os.write(book.title.c_str(), titleLength);
    
    // 写入作者长度和字符串
    size_t authorLength = book.author.length();
    os.write(reinterpret_cast<const char*>(&authorLength), sizeof(authorLength));
    os.write(book.author.c_str(), authorLength);
    
    // 写入出版社长度和字符串
    size_t publisherLength = book.publisher.length();
    os.write(reinterpret_cast<const char*>(&publisherLength), sizeof(publisherLength));
    os.write(book.publisher.c_str(), publisherLength);
    
    // 写入库存和价格
    os.write(reinterpret_cast<const char*>(&book.stock), sizeof(book.stock));
    os.write(reinterpret_cast<const char*>(&book.price), sizeof(book.price));
    
    return os;
}

std::istream& operator>>(std::istream& is, Book& book) {
    // 读取ISBN
    size_t isbnLength;
    is.read(reinterpret_cast<char*>(&isbnLength), sizeof(isbnLength));
    if (isbnLength > 0) {
        char* isbnBuffer = new char[isbnLength + 1];
        is.read(isbnBuffer, isbnLength);
        isbnBuffer[isbnLength] = '\0';
        book.isbn = isbnBuffer;
        delete[] isbnBuffer;
    }
    
    // 读取书名
    size_t titleLength;
    is.read(reinterpret_cast<char*>(&titleLength), sizeof(titleLength));
    if (titleLength > 0) {
        char* titleBuffer = new char[titleLength + 1];
        is.read(titleBuffer, titleLength);
        titleBuffer[titleLength] = '\0';
        book.title = titleBuffer;
        delete[] titleBuffer;
    }
    
    // 读取作者
    size_t authorLength;
    is.read(reinterpret_cast<char*>(&authorLength), sizeof(authorLength));
    if (authorLength > 0) {
        char* authorBuffer = new char[authorLength + 1];
        is.read(authorBuffer, authorLength);
        authorBuffer[authorLength] = '\0';
        book.author = authorBuffer;
        delete[] authorBuffer;
    }
    
    // 读取出版社
    size_t publisherLength;
    is.read(reinterpret_cast<char*>(&publisherLength), sizeof(publisherLength));
    if (publisherLength > 0) {
        char* publisherBuffer = new char[publisherLength + 1];
        is.read(publisherBuffer, publisherLength);
        publisherBuffer[publisherLength] = '\0';
        book.publisher = publisherBuffer;
        delete[] publisherBuffer;
    }
    
    // 读取库存和价格
    is.read(reinterpret_cast<char*>(&book.stock), sizeof(book.stock));
    is.read(reinterpret_cast<char*>(&book.price), sizeof(book.price));
    
    return is;
}
