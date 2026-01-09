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
    
    // 按作者进行统计
    std::vector<Book*> getBooksByAuthor(const std::string& author);
    // 按出版社进行统计
    std::vector<Book*> getBooksByPublisher(const std::string& publisher);
    
    // 按价格/库存量进行统计（降序）
    std::vector<Book*> getBooksSortedByPrice();
    std::vector<Book*> getBooksSortedByStock();
};

#endif // STATISTICSSYSTEM_H
