#ifndef BOOK_H
#define BOOK_H

#include <string>

class Book {
private:
    std::string title;
    std::string publisher;
    std::string isbn;
    std::string author;
    int stock;
    double price;

public:
    // constructor & deconstructor
    Book();  
    Book(const std::string& title, const std::string& publisher, 
         const std::string& isbn, const std::string& author, 
         int stock = 0, double price = 0.0);
    ~Book();

    // copy constructor
    Book(const Book& x);
    
    // Getter
    std::string getTitle() const;
    std::string getPublisher() const;
    std::string getISBN() const;
    std::string getAuthor() const;
    int getStock() const;
    double getPrice() const;
    
    // Setter
    void setTitle(const std::string& title);
    void setPublisher(const std::string& publisher);
    void setISBN(const std::string& isbn);
    void setAuthor(const std::string& author);
    void setStock(int stock);
    void setPrice(double price);
    
    // to_string函数
    std::string toString() const;
    
    Book& operator=(const Book& x);
    friend std::ostream& operator<<(std::ostream& os, const Book& book);
    friend std::istream& operator>>(std::istream& is, Book& book);
};

#endif
