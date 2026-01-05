#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include "BookManager.h"
#include <string>

class FileOperations {
private:
    std::string filename;
    
public:
    explicit FileOperations(const std::string& file);
    
    // 保存到文件
    bool save(BookManager& manager);
    
    // 从文件加载
    bool load(BookManager& manager);
    
    // 设置文件名
    void setFilename(const std::string& file) { filename = file; }
};

#endif // FILE_OPERATIONS_H