# 图书管理系统设计文档

## 1. 系统功能模块框图

```mermaid
graph TD
    A[图书管理系统] --> B[图书管理模块]
    A --> C[销售功能模块]
    A --> D[统计功能模块]
    A --> E[文件存取模块]
    A --> F[UI界面模块]
    
    B --> B1[添加图书]
    B --> B2[查询图书]
    B --> B3[修改图书]
    B --> B4[删除图书]
    
    C --> C1[购买书籍]
    C --> C2[库存检查]
    C --> C3[价格计算]
    
    D --> D1[图书总数统计]
    D --> D2[按价格排序统计]
    D --> D3[按库存量排序统计]
    D --> D4[按作者统计]
    D --> D5[按出版社统计]
    
    E --> E1[图书信息存盘]
    E --> E2[图书信息读出]
    
    F --> F1[主界面]
    F --> F2[管理界面]
    F --> F3[销售界面]
    F --> F4[统计界面]
```

## 2. 系统类层次结构

```mermaid
classDiagram
    class Book {
        -string title
        -string publisher
        -string isbn
        -string author
        -int stock
        -double price
        +Book()
        +Book(string, string, string, string, int, double)
        +getTitle() string
        +setTitle(string)
        +getPublisher() string
        +setPublisher(string)
        +getISBN() string
        +setISBN(string)
        +getAuthor() string
        +setAuthor(string)
        +getStock() int
        +setStock(int)
        +getPrice() double
        +setPrice(double)
        +toString() string
    }
    
    class BookManager {
        -vector~Book~ books
        +BookManager()
        +addBook(Book) bool
        +findByISBN(string) Book*
        +findByTitle(string) vector~Book~
        +findByAuthor(string) vector~Book~
        +findByPublisher(string) vector~Book~
        +updateBook(string, Book) bool
        +deleteBook(string) bool
        +getAllBooks() vector~Book~
        +sortByPrice() vector~Book~
        +sortByStock() vector~Book~
        +saveFile(string) bool
        +loadFile(string) bool
    }
    
    class SaleSys {
        -BookManager* bookManager
        +SaleSys(BookManager*)
        +purchaseBook(string, int) bool
        +consume(double, int) double
    }
    
    class StatisSys {
        -BookManager* bookManager
        +StatisSys(BookManager*)
        +getTotalBooks() int
        +getTotalStock() int
        +getTotalValue() double
        +getBooksByAuthor(string) vector~Book~
        +getBooksByPublisher(string) vector~Book~
        +sortAndDisplayByPrice()
        +sortAndDisplayByStock()
    }
    
    class MainWindow {
        -BookManager* bookManager
        -SaleSys* SaleSys
        -StatisSys* statsSystem
        +MainWindow()
        +show()
        +handleAddBook()
        +handleSearchBook()
        +handleUpdateBook()
        +handleDeleteBook()
        +handlePurchaseBook()
        +handleStatistics()
        +handleSave()
        +handleLoad()
    }
    
    BookManager --> Book : 管理
    SaleSys --> BookManager : 使用
    StatisSys --> BookManager : 使用
    MainWindow --> BookManager : 使用
    MainWindow --> SaleSys : 使用
    MainWindow --> StatisSys : 使用
```

## 3. 核心类设计

### 3.1 Book类
- **属性**：书名、出版社、ISBN号、作者、库存量、价格
- **方法**：构造函数、getter/setter方法、字符串转换方法

### 3.2 BookManager类
- **属性**：图书容器（vector<Book>）
- **方法**：增删改查、排序、文件存取

### 3.3 SalesSystem类
- **属性**：指向BookManager的指针
- **方法**：购买书籍、价格计算

### 3.4 StatisticsSystem类
- **属性**：指向BookManager的指针
- **方法**：各类统计功能

### 3.5 MainWindow类
- **属性**：各系统指针、UI组件
- **方法**：界面事件处理、功能调用

## 4. 文件结构设计

```
BMS/
├── include/
│   ├── Book.h
│   ├── BookManager.h
│   ├── SaleSys.h
│   ├── StatisSys.h
│   └── MainWindow.h
├── src/
│   ├── Book.cpp
│   ├── BookManager.cpp
│   ├── SaleSys.cpp
│   ├── StatisSys.cpp
│   ├── MainWindow.cpp
│   └── main.cpp
├── data/
│   └── books.dat
├── docs/
│   └── system_design.md
└── CMakeLists.txt
```

## 5. 技术栈

- **语言**：C++11
- **UI库**：FLTK 1.3.x
- **数据结构**：std::vector
- **文件格式**：二进制序列化
- **编译系统**：CMake

## 6. 实现优先级

1. 核心数据类（Book, BookManager）
2. 业务逻辑类（SaleSys, StatisticsSystem）
3. 文件存取功能
4. UI界面开发
5. 系统集成测试