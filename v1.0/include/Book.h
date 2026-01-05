#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <iostream>

// 抽象基类 - 用于多态
class IBookOperations {
public:
    virtual ~IBookOperations() = default;
    virtual void displayInfo(std::ostream& os) const = 0;
    virtual double getPrice() const = 0;
    virtual int getStock() const = 0;
    virtual std::string getISBN() const = 0;
    virtual std::string getTitle() const = 0;
};

// 基础图书类
class Book : public IBookOperations {
protected:
    std::string title;
    std::string publisher;
    std::string isbn;
    std::string author;
    int stock;
    double price;

public:
    Book();
    Book(const std::string& t, const std::string& p, const std::string& i, 
         const std::string& a, int s, double pr);
    
    // 虚函数实现多态
    virtual void displayInfo(std::ostream& os) const override;
    virtual double getPrice() const override { return price; }
    virtual int getStock() const override { return stock; }
    virtual std::string getISBN() const override { return isbn; }
    virtual std::string getTitle() const override { return title; }
    
    // 友元函数
    friend std::ostream& operator<<(std::ostream& os, const Book& book);
    friend class BookManager;
    friend class FileOperations;
    
    // 成员函数
    void updateStock(int quantity);
    bool reduceStock(int quantity);
    
    // 多继承接口
    class Serializable {
    public:
        virtual void serialize(std::ostream& os) const = 0;
        virtual void deserialize(std::istream& is) = 0;
        virtual ~Serializable() = default;
    };
    
    // Book类同时继承IBookOperations和Serializable
    class BookDetails : public IBookOperations, public Serializable {
    private:
        Book* book;
    public:
        explicit BookDetails(Book* b) : book(b) {}
        
        void displayInfo(std::ostream& os) const override {
            book->displayInfo(os);
        }
        
        double getPrice() const override { return book->getPrice(); }
        int getStock() const override { return book->getStock(); }
        std::string getISBN() const override { return book->getISBN(); }
        std::string getTitle() const override { return book->getTitle(); }
        
        void serialize(std::ostream& os) const override;
        void deserialize(std::istream& is) override;
    };
    
    BookDetails* getDetails() { return new BookDetails(this); }
    
protected:
    virtual void printDetails(std::ostream& os) const;
};

// 装饰器类 - 用于扩展功能
class BookDecorator : public IBookOperations {
protected:
    IBookOperations* wrappedBook;
    
public:
    explicit BookDecorator(IBookOperations* book) : wrappedBook(book) {}
    virtual ~BookDecorator() { delete wrappedBook; }
    
    void displayInfo(std::ostream& os) const override {
        wrappedBook->displayInfo(os);
    }
    
    double getPrice() const override {
        return wrappedBook->getPrice();
    }
    
    int getStock() const override {
        return wrappedBook->getStock();
    }
    
    std::string getISBN() const override {
        return wrappedBook->getISBN();
    }
    
    std::string getTitle() const override {
        return wrappedBook->getTitle();
    }
};

// 带折扣的图书装饰器
class DiscountedBook : public BookDecorator {
private:
    double discountRate;
    
public:
    DiscountedBook(IBookOperations* book, double discount) 
        : BookDecorator(book), discountRate(discount) {}
    
    double getPrice() const override {
        return wrappedBook->getPrice() * (1 - discountRate);
    }
    
    void displayInfo(std::ostream& os) const override {
        os << "[Discounted] ";
        wrappedBook->displayInfo(os);
        os << " | Discount: " << (discountRate * 100) << "%";
    }
};

#endif // BOOK_H