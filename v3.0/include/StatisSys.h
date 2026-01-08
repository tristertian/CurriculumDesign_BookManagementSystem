#ifndef STATISSYS_H
#define STATISSYS_H

#include <vector>
#include <string>
#include "BookManager.h"

class StatisSys {
private:
    BookManager* bookManager;

public:
    explicit StatisSys(BookManager* manager);   
    ~StatisSys();
    
    // 获取图书总数
    size_t getTotalBooks() const;
    // 获取总库存量
    int getTotalStock() const;
    // 获取库存总价值
    double getTotalValue() const;
    
    // 按作者进行统计
    std::vector<Book*> getBooksByAuthor(const std::string& author);
    // 按出版社进行统计
    std::vector<Book*> getBooksByPublisher(const std::string& publisher);
    
    // 按价格统计（从大到小）
    std::vector<Book*> getBooksSortedByPrice();
    // 按库存量统计（从大到小）
    std::vector<Book*> getBooksSortedByStock();
    
    // 获取平均价格
    double getAveragePrice() const;
    // 获取最贵图书
    Book* getMostExpensiveBook();
    // 获取库存最多图书
    Book* getHighestStockBook();
};

#endif // STATISTICSSYSTEM_H
