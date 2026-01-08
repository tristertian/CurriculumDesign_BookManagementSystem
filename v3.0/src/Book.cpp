#include "../include/Book.h"
#include <sstream>

Book::Book() : stock(0), price(0.0) {}

Book::Book(const std::string& title, const std::string& publisher, 
           const std::string& isbn, const std::string& author, 
           int stock, double price) 
    : title(title), publisher(publisher), isbn(isbn), author(author), 
      stock(stock), price(price) {}

Book::~Book() {}

// copy constructor
Book::Book(const Book& x) 
    : title(x.title), publisher(x.publisher), isbn(x.isbn), 
      author(x.author), stock(x.stock), price(x.price) {}

// operator=
Book& Book::operator=(const Book& x) {
    if (&x != this) {
        title = x.title;
        publisher = x.publisher;
        isbn = x.isbn;
        author = x.author;
        stock = x.stock;
        price = x.price;
    }
    return *this;
}

// Getter
std::string Book::getTitle()    const {return title;}
std::string Book::getPublisher()const {return publisher;}
std::string Book::getISBN()     const {return isbn;}
std::string Book::getAuthor()   const {return author;}
int Book::getStock()            const {return stock;}
double Book::getPrice()         const {return price;}

// Setter
void Book::setTitle(const std::string& newTitle)        {title = newTitle;}
void Book::setPublisher(const std::string& newPublisher){publisher = newPublisher;}
void Book::setISBN(const std::string& newISBN)          {isbn = newISBN;}
void Book::setAuthor(const std::string& newAuthor)      {author = newAuthor;}
void Book::setStock(int newStock)                       {stock = newStock;}
void Book::setPrice(double newPrice)                    {price = newPrice;}

std::string Book::toString() const {
    std::stringstream s;
    s <<"ISBN: "<<isbn<<", 书名: "<<title<<", 作者: "<<author
      <<", 出版社: "<<publisher<<", 库存: "<<stock<<", 价格: ¥"<<price;
    return s.str();
}

// STAR: binary read&write
// ===binary write===
std::ostream& operator<<(std::ostream& os, const Book& book) {
    // ISBN(长度 + 字符串)
    int isbnLen = book.isbn.length();
    os.write(reinterpret_cast<const char*>(&isbnLen), sizeof(isbnLen));
    os.write(book.isbn.c_str(), isbnLen);
    // 书名
    int titleLen = book.title.length();
    os.write(reinterpret_cast<const char*>(&titleLen), sizeof(titleLen));
    os.write(book.title.c_str(), titleLen);
    // 作者
    int authorLen = book.author.length();
    os.write(reinterpret_cast<const char*>(&authorLen), sizeof(authorLen));
    os.write(book.author.c_str(), authorLen);
    // 出版社
    int publisherLen = book.publisher.length();
    os.write(reinterpret_cast<const char*>(&publisherLen), sizeof(publisherLen));
    os.write(book.publisher.c_str(), publisherLen);
    // 库存 价格
    os.write(reinterpret_cast<const char*>(&book.stock), sizeof(book.stock));
    os.write(reinterpret_cast<const char*>(&book.price), sizeof(book.price));
    
    return os;
}

// ===binary read===
std::istream& operator>>(std::istream& is, Book& book) {
    // ISBN
    int isbnLen;
    is.read(reinterpret_cast<char*>(&isbnLen), sizeof(isbnLen));
    if (isbnLen > 0) {
        char* Temp = new char[isbnLen + 1]; // 'isbn+1'的原因：字符串的末尾有一个'\0'，倘若不处理会造成数组溢出
            is.read(Temp, isbnLen);
            Temp[isbnLen] = '\0';
            book.isbn = Temp;
        delete[] Temp;
    }
    // 读取书名
    int titleLen;
    is.read(reinterpret_cast<char*>(&titleLen), sizeof(titleLen));
    if (titleLen > 0) {
        char* Temp = new char[titleLen + 1];
            is.read(Temp, titleLen);
            Temp[titleLen] = '\0';
            book.title = Temp;
        delete[] Temp;
    }
    // 读取作者
    int authorLen;
    is.read(reinterpret_cast<char*>(&authorLen), sizeof(authorLen));
    if (authorLen > 0) {
        char* Temp = new char[authorLen + 1];
            is.read(Temp, authorLen);
            Temp[authorLen] = '\0';
            book.author = Temp;
        delete[] Temp;
    }
    // 读取出版社
    int publisherLen;
    is.read(reinterpret_cast<char*>(&publisherLen), sizeof(publisherLen));
    if (publisherLen > 0) {
        char* Temp = new char[publisherLen + 1];
            is.read(Temp, publisherLen);
            Temp[publisherLen] = '\0';
            book.publisher = Temp;
        delete[] Temp;
    }
    // 读取库存和价格
    is.read(reinterpret_cast<char*>(&book.stock), sizeof(book.stock));
    is.read(reinterpret_cast<char*>(&book.price), sizeof(book.price));
    
    return is;
}
