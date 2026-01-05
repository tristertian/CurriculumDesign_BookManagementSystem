#include "../include/FileOperations.h"
#include <fstream>
#include <iostream>

FileOperations::FileOperations(const std::string& file) : filename(file) {}

bool FileOperations::save(BookManager& manager) {
    std::ofstream ofs(filename);
    if (!ofs.is_open()) {
        return false;
    }
    
    manager.serialize(ofs);
    ofs.close();
    return true;
}

bool FileOperations::load(BookManager& manager) {
    std::ifstream ifs(filename);
    if (!ifs.is_open()) {
        return false;
    }
    
    manager.deserialize(ifs);
    ifs.close();
    return true;
}