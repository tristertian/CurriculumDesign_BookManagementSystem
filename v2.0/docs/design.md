# 图书管理系统设计文档

## 1. 系统概述

### 1.1 项目背景
图书管理系统是一个基于C++面向对象编程的应用程序，旨在实现对图书的添加、查询、修改、删除、销售、统计等功能。系统采用模块化设计，具有良好的可扩展性和可维护性。

### 1.2 功能需求
- **图书管理功能**: 添加、查询、修改、删除图书信息
- **销售功能**: 购买图书、库存管理、销售记录
- **统计功能**: 多维度统计、排序展示、综合报告
- **数据持久化**: 文件存盘、数据读取、备份导出

## 2. 系统架构

### 2.1 整体架构
系统采用三层架构设计：

```
┌─────────────────────────────────────┐
│         用户界面层 (UI Layer)        │
│  - 控制台界面 (ConsoleUI)           │
│  - 图形界面 (FLTK)                  │
├─────────────────────────────────────┤
│         业务逻辑层 (Business Layer)  │
│  - BookManager (图书管理)           │
│  - SalesManager (销售管理)          │
│  - StatisticsManager (统计管理)     │
│  - FileManager (文件管理)           │
├─────────────────────────────────────┤
│         数据访问层 (Data Layer)      │
│  - Book (图书实体)                  │
│  - SaleRecord (销售记录)            │
│  - 文件存储                         │
└─────────────────────────────────────┘
```

### 2.2 类层次结构

```
实体类 (Entity Classes)
├── Book (图书)
│   ├── 属性: 书名、出版社、ISBN、作者、库存、价格
│   └── 方法: getter/setter、显示、序列化
│
└── SaleRecord (销售记录)
    ├── 属性: ISBN、书名、数量、总价、时间
    └── 方法: getter/setter、显示、序列化

管理类 (Manager Classes)
├── BookManager (图书管理器)
│   ├── 功能: 增删改查图书
│   └── 特性: ISBN唯一性检查
│
├── SalesManager (销售管理器)
│   ├── 功能: 处理购买、管理库存
│   └── 特性: 库存检查、销售记录
│
├── StatisticsManager (统计管理器)
│   ├── 功能: 多维度统计分析
│   └── 特性: 排序、分组、聚合
│
└── FileManager (文件管理器)
    ├── 功能: 数据持久化、备份导出
    └── 特性: 自动备份、CSV导出

界面类 (UI Classes)
├── ConsoleUI (控制台界面)
│   └── 功能: 命令行交互
│
└── MainWindow (GUI主窗口)
    └── 功能: 图形界面交互
```

## 3. 详细设计

### 3.1 Book类设计

**类定义**:
```cpp
class Book {
private:
    std::string title;          // 书名
    std::string publisher;      // 出版社
    std::string isbn;           // ISBN号
    std::string author;         // 作者
    int stock;                  // 库存量
    double price;               // 价格

public:
    // 构造函数、拷贝构造函数、赋值运算符、析构函数
    // getter和setter方法
    // 显示方法
    // 序列化方法
    // 比较运算符重载
};
```

**设计要点**:
- 使用std::string管理字符串，避免内存泄漏
- 提供完整的拷贝构造函数和赋值运算符
- 支持对象的序列化和反序列化
- 重载比较运算符，便于排序和查找

### 3.2 BookManager类设计

**类定义**:
```cpp
class BookManager {
private:
    std::vector<std::shared_ptr<Book>> books;
    
public:
    // 图书管理操作
    bool addBook(const Book& book);
    bool deleteBook(const std::string& isbn);
    bool updateBook(const std::string& isbn, const Book& newBook);
    
    // 查询操作
    std::shared_ptr<Book> findBookByIsbn(const std::string& isbn) const;
    std::vector<std::shared_ptr<Book>> findBooksByTitle(const std::string& title) const;
    std::vector<std::shared_ptr<Book>> findBooksByAuthor(const std::string& author) const;
    std::vector<std::shared_ptr<Book>> findBooksByPublisher(const std::string& publisher) const;
    
    // 库存管理
    bool updateStock(const std::string& isbn, int quantity);
    int getStock(const std::string& isbn) const;
    
    // 文件操作
    bool loadFromFile(const std::string& filename);
    bool saveToFile(const std::string& filename) const;
};
```

**设计要点**:
- 使用std::shared_ptr管理对象生命周期
- ISBN号唯一性检查
- 支持多条件查询
- 库存原子性操作

### 3.3 SalesManager类设计

**类定义**:
```cpp
class SalesManager {
private:
    std::vector<std::shared_ptr<SaleRecord>> saleRecords;
    BookManager* bookManager;
    
public:
    // 销售操作
    bool purchaseBook(const std::string& isbn, int quantity);
    
    // 查询操作
    std::vector<std::shared_ptr<SaleRecord>> getSaleRecordsByIsbn(const std::string& isbn) const;
    
    // 统计操作
    double getTotalSales() const;
    
    // 文件操作
    bool loadFromFile(const std::string& filename);
    bool saveToFile(const std::string& filename) const;
};
```

**设计要点**:
- 依赖注入BookManager，实现图书和销售的关联
- 购买时自动更新库存
- 自动生成销售记录
- 支持销售额统计

### 3.4 StatisticsManager类设计

**类定义**:
```cpp
class StatisticsManager {
private:
    BookManager* bookManager;
    SalesManager* salesManager;
    
public:
    // 统计方法
    void printAllBooksInfo() const;
    void printBooksSortedByPrice() const;
    void printBooksSortedByStock() const;
    void printBooksByAuthor() const;
    void printBooksByPublisher() const;
    void generateReport() const;
    
    // 统计数据结构
    struct PriceStats {
        double maxPrice;
        double minPrice;
        double avgPrice;
        double totalValue;
    };
    
    struct StockStats {
        int totalBooks;
        int totalStock;
        int maxStock;
        int minStock;
        double avgStock;
    };
    
    PriceStats getPriceStatistics() const;
    StockStats getStockStatistics() const;
};
```

**设计要点**:
- 支持多种排序方式（价格、库存量）
- 支持分组统计（作者、出版社）
- 提供综合统计报告
- 使用lambda表达式进行排序

### 3.5 FileManager类设计

**类定义**:
```cpp
class FileManager {
private:
    std::string booksFileName;
    std::string salesFileName;
    
public:
    // 文件操作
    bool saveAllData(const BookManager* bookManager, const SalesManager* salesManager) const;
    bool loadAllData(BookManager* bookManager, SalesManager* salesManager) const;
    bool backupData(const std::string& backupDir = "backup") const;
    bool exportBooksToCSV(const std::string& filename) const;
    bool exportSalesToCSV(const std::string& filename) const;
};
```

**设计要点**:
- 支持自动备份，带时间戳
- 支持CSV格式导出
- 异常安全的文件操作
- 使用std::filesystem进行文件管理

## 4. 数据存储格式

### 4.1 图书数据格式
```
书名|出版社|ISBN|作者|库存量|价格
```

**示例**:
```
C++程序设计|清华大学出版社|9787302168979|谭浩强|10|59.90
数据结构与算法|人民邮电出版社|9787115458563|严蔚敏|5|45.00
```

### 4.2 销售记录格式
```
ISBN|书名|销售数量|总价格|销售时间
```

**示例**:
```
9787302168979|C++程序设计|2|119.80|2024-01-06 14:30:25
9787115458563|数据结构与算法|1|45.00|2024-01-06 14:35:10
```

## 5. 用户界面设计

### 5.1 控制台界面
采用菜单驱动的交互方式：

```
========================================
           图书管理系统主菜单           
========================================
1. 图书管理
2. 图书销售
3. 统计查询
4. 数据存盘
5. 读取数据
6. 退出系统
========================================
请选择操作: 
```

### 5.2 图形界面（可选）
使用FLTK库实现轻量级GUI，包括：
- 主菜单栏
- 图书信息表格
- 操作按钮
- 状态显示区域

## 6. 异常处理

### 6.1 错误处理策略
- 输入验证：检查数据格式和范围
- 资源管理：RAII原则，自动释放资源
- 文件操作：检查文件状态和权限
- 内存管理：使用智能指针避免内存泄漏

### 6.2 错误提示
- 重复添加："错误：ISBN号已存在！"
- 查询失败："该标题不存在！"
- 库存不足："错误：库存不足！"
- 文件错误："无法打开文件"

## 7. 性能优化

### 7.1 数据结构选择
- 使用std::vector存储图书数据，支持随机访问
- 使用std::map进行分组统计
- 使用std::shared_ptr管理对象生命周期

### 7.2 算法优化
- 使用std::sort进行高效排序
- 使用lambda表达式简化代码
- 使用移动语义避免不必要的拷贝

## 8. 扩展性设计

### 8.1 可扩展功能
- 用户管理系统
- 权限控制
- 数据库支持
- 网络功能
- 报表生成

### 8.2 设计模式应用
- 单例模式：管理器类
- 工厂模式：对象创建
- 观察者模式：数据更新通知
- 策略模式：不同的查询策略

## 9. 测试计划

### 9.1 单元测试
- Book类测试：构造、拷贝、序列化
- BookManager测试：增删改查、库存操作
- SalesManager测试：购买流程、销售记录
- StatisticsManager测试：统计计算

### 9.2 集成测试
- 完整业务流程测试
- 数据持久化测试
- 异常情况测试
- 性能压力测试

## 10. 部署和维护

### 10.1 编译部署
- 支持多种编译器（GCC、Clang、MSVC）
- 提供Makefile构建系统
- 支持跨平台编译（Linux、Windows、macOS）

### 10.2 维护建议
- 定期备份数据
- 监控日志文件
- 性能监控和优化
- 安全更新和补丁