#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "BookManager.h"
#include "SalesManager.h"
#include <string>

class FileManager {
private:
    std::string booksFileName;
    std::string salesFileName;

public:
    // 构造函数
    FileManager(const std::string& booksFile = "books.txt", 
                const std::string& salesFile = "sales.txt");
    
    // 析构函数
    ~FileManager();
    
    // 设置文件名
    void setBooksFileName(const std::string& filename) { booksFileName = filename; }
    void setSalesFileName(const std::string& filename) { salesFileName = filename; }
    
    // 获取文件名
    std::string getBooksFileName() const { return booksFileName; }
    std::string getSalesFileName() const { return salesFileName; }
    
    // 保存所有数据
    bool saveAllData(const BookManager* bookManager, const SalesManager* salesManager) const;
    
    // 加载所有数据
    bool loadAllData(BookManager* bookManager, SalesManager* salesManager) const;
    
    // 备份数据
    bool backupData(const std::string& backupDir = "backup") const;
    
    // 导出数据为CSV格式
    bool exportBooksToCSV(const std::string& filename) const;
    bool exportSalesToCSV(const std::string& filename) const;
};

#endif // FILEMANAGER_H