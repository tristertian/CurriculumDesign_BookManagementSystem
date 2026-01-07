#include "../include/FileManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <ctime>

namespace fs = std::filesystem;

// 构造函数
FileManager::FileManager(const std::string& booksFile, const std::string& salesFile)
    : booksFileName(booksFile), salesFileName(salesFile) {}

// 析构函数
FileManager::~FileManager() {}

// 保存所有数据
bool FileManager::saveAllData(const BookManager* bookManager, const SalesManager* salesManager) const {
    bool success = true;
    
    // 保存图书数据
    if (!bookManager->saveToFile(booksFileName)) {
        std::cout << "警告：图书数据保存失败！" << std::endl;
        success = false;
    }
    
    // 保存销售数据
    if (!salesManager->saveToFile(salesFileName)) {
        std::cout << "警告：销售数据保存失败！" << std::endl;
        success = false;
    }
    
    if (success) {
        std::cout << "所有数据保存成功！" << std::endl;
    }
    
    return success;
}

// 加载所有数据
bool FileManager::loadAllData(BookManager* bookManager, SalesManager* salesManager) const {
    bool success = true;
    
    // 加载图书数据
    if (!bookManager->loadFromFile(booksFileName)) {
        std::cout << "警告：图书数据加载失败！" << std::endl;
        success = false;
    }
    
    // 加载销售数据
    if (!salesManager->loadFromFile(salesFileName)) {
        std::cout << "警告：销售数据加载失败！" << std::endl;
        success = false;
    }
    
    if (success) {
        std::cout << "所有数据加载成功！" << std::endl;
    }
    
    return success;
}

// 备份数据
bool FileManager::backupData(const std::string& backupDir) const {
    try {
        // 创建备份目录
        if (!fs::exists(backupDir)) {
            fs::create_directories(backupDir);
        }
        
        // 获取当前时间
        auto now = std::time(nullptr);
        auto tm = *std::localtime(&now);
        std::stringstream ss;
        ss << std::put_time(&tm, "%Y%m%d_%H%M%S");
        std::string timestamp = ss.str();
        
        // 备份图书文件
        if (fs::exists(booksFileName)) {
            std::string backupBooksFile = backupDir + "/books_" + timestamp + ".txt";
            fs::copy_file(booksFileName, backupBooksFile);
            std::cout << "图书数据已备份到: " << backupBooksFile << std::endl;
        }
        
        // 备份销售文件
        if (fs::exists(salesFileName)) {
            std::string backupSalesFile = backupDir + "/sales_" + timestamp + ".txt";
            fs::copy_file(salesFileName, backupSalesFile);
            std::cout << "销售数据已备份到: " << backupSalesFile << std::endl;
        }
        
        return true;
    } catch (const std::exception& e) {
        std::cout << "备份失败: " << e.what() << std::endl;
        return false;
    }
}

// 导出图书数据为CSV格式
bool FileManager::exportBooksToCSV(const std::string& filename) const {
    std::ifstream booksFile(booksFileName);
    std::ofstream csvFile(filename);
    
    if (!booksFile.is_open() || !csvFile.is_open()) {
        std::cout << "导出失败：无法打开文件" << std::endl;
        return false;
    }
    
    // 写入CSV头
    csvFile << "书名,出版社,ISBN,作者,库存量,价格" << std::endl;
    
    // 转换数据
    std::string line;
    while (std::getline(booksFile, line)) {
        if (!line.empty()) {
            // 将分隔符从|改为,
            std::replace(line.begin(), line.end(), '|', ',');
            csvFile << line << std::endl;
        }
    }
    
    booksFile.close();
    csvFile.close();
    
    std::cout << "图书数据已导出到CSV文件: " << filename << std::endl;
    return true;
}

// 导出销售数据为CSV格式
bool FileManager::exportSalesToCSV(const std::string& filename) const {
    std::ifstream salesFile(salesFileName);
    std::ofstream csvFile(filename);
    
    if (!salesFile.is_open() || !csvFile.is_open()) {
        std::cout << "导出失败：无法打开文件" << std::endl;
        return false;
    }
    
    // 写入CSV头
    csvFile << "ISBN,书名,销售数量,总价格,销售时间" << std::endl;
    
    // 转换数据
    std::string line;
    while (std::getline(salesFile, line)) {
        if (!line.empty()) {
            // 将分隔符从|改为,
            std::replace(line.begin(), line.end(), '|', ',');
            csvFile << line << std::endl;
        }
    }
    
    salesFile.close();
    csvFile.close();
    
    std::cout << "销售数据已导出到CSV文件: " << filename << std::endl;
    return true;
}