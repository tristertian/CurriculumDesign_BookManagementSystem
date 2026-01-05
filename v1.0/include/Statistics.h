#ifndef STATISTICS_H
#define STATISTICS_H

#include "BookManager.h"
#include <vector>

class Statistics {
private:
    BookManager& bookManager;
    
    // 排序比较器
    static bool compareByPrice(IBookOperations* a, IBookOperations* b);
    static bool compareByStock(IBookOperations* a, IBookOperations* b);
    static bool compareByTitle(IBookOperations* a, IBookOperations* b);
    
public:
    explicit Statistics(BookManager& bm);
    
    // 统计功能
    std::vector<IBookOperations*> sortByPrice(bool descending = true);
    std::vector<IBookOperations*> sortByStock(bool descending = true);
    std::vector<IBookOperations*> getBooksByAuthor(const std::string& author);
    std::vector<IBookOperations*> getBooksByPublisher(const std::string& publisher);
    
    // 输出所有图书
    void printAllBooks(std::ostream& os = std::cout);
};

#endif // STATISTICS_H