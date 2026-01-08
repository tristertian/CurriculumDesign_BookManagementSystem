# 图书管理系统核心类详细设计

## 1. Book类设计

### 1.1 类定义
```cpp
#ifndef BOOK_H
#define BOOK_H

#include <string>

class Book {
private:
    std::string title;      // 书名
    std::string publisher;  // 出版社
    std::string isbn;       // ISBN号
    std::string author;     // 作者
    int stock;              // 库存量
    double price;           // 价格

public:
    // 默认构造函数
    Book();
    
    // 带参数的构造函数
    Book(const std::string& title, const std::string& publisher, 
         const std::string& isbn, const std::string& author, 
         int stock, double price);
    
    // 拷贝构造函数
    Book(const Book& other);
    
    // 赋值运算符
    Book& operator=(const Book& other);
    
    // 析构函数
    ~Book();
    
    // Getter方法
    std::string getTitle() const;
    std::string getPublisher() const;
    std::string getISBN() const;
    std::string getAuthor() const;
    int getStock() const;
    double getPrice() const;
    
    // Setter方法
    void setTitle(const std::string& title);
    void setPublisher(const std::string& publisher);
    void setISBN(const std::string& isbn);
    void setAuthor(const std::string& author);
    void setStock(int stock);
    void setPrice(double price);
    
    // 转换为字符串表示
    std::string toString() const;
    
    // 友元函数：用于文件读写
    friend std::ostream& operator<<(std::ostream& os, const Book& book);
    friend std::istream& operator>>(std::istream& is, Book& book);
};

#endif // BOOK_H
```

### 1.2 方法说明

| 方法 | 参数 | 返回值 | 功能描述 |
|------|------|--------|----------|
| Book() | 无 | 无 | 默认构造函数，初始化空对象 |
| Book(...) | 书名,出版社,ISBN,作者,库存,价格 | 无 | 带参数构造函数 |
| getTitle() | 无 | string | 获取书名 |
| setTitle() | string | void | 设置书名 |
| getPublisher() | 无 | string | 获取出版社 |
| setPublisher() | string | void | 设置出版社 |
| getISBN() | 无 | string | 获取ISBN号 |
| setISBN() | string | void | 设置ISBN号 |
| getAuthor() | 无 | string | 获取作者 |
| setAuthor() | string | void | 设置作者 |
| getStock() | 无 | int | 获取库存量 |
| setStock() | int | void | 设置库存量 |
| getPrice() | 无 | double | 获取价格 |
| setPrice() | double | void | 设置价格 |
| toString() | 无 | string | 返回对象的字符串表示 |

## 2. BookManager类设计

### 2.1 类定义
```cpp
#ifndef BOOKMANAGER_H
#define BOOKMANAGER_H

#include <vector>
#include <string>
#include "Book.h"

class BookManager {
private:
    std::vector<Book> books;  // 图书容器
    
    // 检查ISBN是否已存在
    bool findIndex(const std::string& isbn) const;
    
    // 查找图书索引
    int findIndex(const std::string& isbn) const;

public:
    // 构造函数
    BookManager();
    
    // 析构函数
    ~BookManager();
    
    // 添加图书
    bool addBook(const Book& book);
    
    // 根据ISBN查找图书
    Book* findByISBN(const std::string& isbn);
    const Book* findByISBN(const std::string& isbn) const;
    
    // 根据书名查找图书（支持模糊查询）
    std::vector<Book*> findByTitle(const std::string& title);
    std::vector<const Book*> findByTitle(const std::string& title) const;
    
    // 根据作者查找图书
    std::vector<Book*> findByAuthor(const std::string& author);
    std::vector<const Book*> findByAuthor(const std::string& author) const;
    
    // 根据出版社查找图书
    std::vector<Book*> findByPublisher(const std::string& publisher);
    std::vector<const Book*> findByPublisher(const std::string& publisher) const;
    
    // 更新图书信息
    bool updateBook(const std::string& isbn, const Book& newBook);
    
    // 删除图书
    bool deleteBook(const std::string& isbn);
    
    // 获取所有图书
    std::vector<Book>& getAllBooks();
    const std::vector<Book>& getAllBooks() const;
    
    // 按价格排序（降序）
    std::vector<Book*> sortByPrice();
    
    // 按库存量排序（降序）
    std::vector<Book*> sortByStock();
    
    // 获取图书数量
    size_t getBookAmount() const;
    
    // 保存到文件
    bool saveFile(const std::string& filename) const;
    
    // 从文件加载
    bool loadFile(const std::string& filename);
    
    // 清空所有图书
    void clear();
};

#endif // BOOKMANAGER_H
```

### 2.2 方法说明

| 方法 | 参数 | 返回值 | 功能描述 |
|------|------|--------|----------|
| addBook() | Book | bool | 添加图书，ISBN重复返回false |
| findByISBN() | string | Book* | 根据ISBN精确查找 |
| findByTitle() | string | vector<Book*> | 根据书名模糊查找 |
| findByAuthor() | string | vector<Book*> | 根据作者查找 |
| findByPublisher() | string | vector<Book*> | 根据出版社查找 |
| updateBook() | string, Book | bool | 更新图书信息 |
| deleteBook() | string | bool | 删除图书 |
| getAllBooks() | 无 | vector<Book>& | 获取所有图书引用 |
| sortByPrice() | 无 | vector<Book*> | 按价格降序排序 |
| sortByStock() | 无 | vector<Book*> | 按库存降序排序 |
| getBookAmount() | 无 | size_t | 获取图书数量 |
| saveFile() | string | bool | 保存数据到文件 |
| loadFile() | string | bool | 从文件加载数据 |
| clear() | 无 | void | 清空所有图书 |

## 3. SalesSystem类设计

### 3.1 类定义
```cpp
#ifndef SALESSYSTEM_H
#define SALESSYSTEM_H

#include <string>
#include "BookManager.h"

class SaleSys {
private:
    BookManager* bookManager;  // 图书管理器指针
    
    // 计算总价
    double consume(double price, int quantity) const;

public:
    // 构造函数
    explicit SaleSys(BookManager* manager);
    
    // 析构函数
    ~SaleSys();
    
    // 购买图书
    bool purchaseBook(const std::string& isbn, int quantity);
    
    // 检查库存是否充足
    bool checkStock(const std::string& isbn, int quantity) const;
    
    // 获取图书价格
    double getBookPrice(const std::string& isbn) const;
    
    // 计算购买总价
    double getTotalPrice(const std::string& isbn, int quantity) const;
};

#endif // SALESSYSTEM_H
```

### 3.2 方法说明

| 方法 | 参数 | 返回值 | 功能描述 |
|------|------|--------|----------|
| purchaseBook() | string, int | bool | 购买图书，库存不足返回false |
| checkStock() | string, int | bool | 检查库存是否充足 |
| getBookPrice() | string | double | 获取图书价格 |
| getTotalPrice() | string, int | double | 计算购买总价 |

## 4. StatisticsSystem类设计

### 4.1 类定义
```cpp
#ifndef STATISTICSSYSTEM_H
#define STATISTICSSYSTEM_H

#include <vector>
#include <string>
#include "BookManager.h"

class StatisSys {
private:
    BookManager* bookManager;  // 图书管理器指针

public:
    // 构造函数
    explicit StatisSys(BookManager* manager);
    
    // 析构函数
    ~StatisSys();
    
    // 获取图书总数
    size_t getTotalBooks() const;
    
    // 获取总库存量
    int getTotalStock() const;
    
    // 获取库存总价值
    double getTotalValue() const;
    
    // 获取特定作者的所有图书
    std::vector<Book*> getBooksByAuthor(const std::string& author);
    
    // 获取特定出版社的所有图书
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
```

### 4.2 方法说明

| 方法 | 参数 | 返回值 | 功能描述 |
|------|------|--------|----------|
| getTotalBooks() | 无 | size_t | 获取图书种类总数 |
| getTotalStock() | 无 | int | 获取所有图书库存总量 |
| getTotalValue() | 无 | double | 计算库存总价值 |
| getBooksByAuthor() | string | vector<Book*> | 按作者筛选图书 |
| getBooksByPublisher() | string | vector<Book*> | 按出版社筛选图书 |
| getBooksSortedByPrice() | 无 | vector<Book*> | 按价格降序排序 |
| getBooksSortedByStock() | 无 | vector<Book*> | 按库存降序排序 |
| getAveragePrice() | 无 | double | 计算平均价格 |
| getMostExpensiveBook() | 无 | Book* | 获取最贵图书 |
| getHighestStockBook() | 无 | Book* | 获取库存最多图书 |

## 5. MainWindow类设计

### 5.1 类定义
```cpp
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Table_Row.H>
#include "BookManager.h"
#include "SaleSys.h"
#include "StatisSys.h"

class MainWindow : public Fl_Window {
private:
    // 系统组件
    BookManager* bookManager;
    SaleSys* SaleSys;
    StatisSys* statsSystem;
    
    // UI组件
    Fl_Button* addButton;
    Fl_Button* searchButton;
    Fl_Button* updateButton;
    Fl_Button* deleteButton;
    Fl_Button* purchaseButton;
    Fl_Button* statsButton;
    Fl_Button* saveButton;
    Fl_Button* loadButton;
    
    // 输入框
    Fl_Input* isbnInput;
    Fl_Input* titleInput;
    Fl_Input* authorInput;
    Fl_Input* publisherInput;
    Fl_Input* stockInput;
    Fl_Input* priceInput;
    Fl_Input* searchInput;
    Fl_Input* purchaseIsbnInput;
    Fl_Input* purchaseQuantityInput;
    
    // 显示区域
    Fl_Text_Display* resultDisplay;
    Fl_Text_Buffer* resultBuffer;
    Fl_Table_Row* bookTable;
    
    // 当前选中图书的ISBN
    std::string selectedISBN;
    
    // 私有方法
    void setupUI();  // 设置UI界面
    void setupCallbacks();  // 设置回调函数
    void updateTable();  // 更新表格显示
    void clearInputs();  // 清空输入框
    void showMessage(const std::string& message);  // 显示消息
    
    // 回调函数
    static void onAddBook(Fl_Widget* w, void* data);
    static void onSearchBook(Fl_Widget* w, void* data);
    static void onUpdateBook(Fl_Widget* w, void* data);
    static void onDeleteBook(Fl_Widget* w, void* data);
    static void onPurchaseBook(Fl_Widget* w, void* data);
    static void onShowStats(Fl_Widget* w, void* data);
    static void onSaveData(Fl_Widget* w, void* data);
    static void onLoadData(Fl_Widget* w, void* data);
    static void onTableSelect(Fl_Widget* w, void* data);

public:
    // 构造函数
    MainWindow(int width, int height, const char* title);
    
    // 析构函数
    ~MainWindow();
    
    // 显示窗口
    void show();
    
    // 处理添加图书
    void handleAddBook();
    
    // 处理查询图书
    void handleSearchBook();
    
    // 处理修改图书
    void handleUpdateBook();
    
    // 处理删除图书
    void handleDeleteBook();
    
    // 处理购买图书
    void handlePurchaseBook();
    
    // 处理统计显示
    void handleStatistics();
    
    // 处理保存数据
    void handleSave();
    
    // 处理加载数据
    void handleLoad();
};

#endif // MAINWINDOW_H
```

### 5.2 方法说明

| 方法 | 参数 | 返回值 | 功能描述 |
|------|------|--------|----------|
| setupUI() | 无 | void | 初始化UI界面 |
| setupCallbacks() | 无 | void | 设置事件回调 |
| updateTable() | 无 | void | 更新图书表格显示 |
| clearInputs() | 无 | void | 清空输入框 |
| showMessage() | string | void | 在结果显示区显示消息 |
| handleAddBook() | 无 | void | 处理添加图书事件 |
| handleSearchBook() | 无 | void | 处理查询图书事件 |
| handleUpdateBook() | 无 | void | 处理修改图书事件 |
| handleDeleteBook() | 无 | void | 处理删除图书事件 |
| handlePurchaseBook() | 无 | void | 处理购买图书事件 |
| handleStatistics() | 无 | void | 处理统计显示事件 |
| handleSave() | 无 | void | 处理保存数据事件 |
| handleLoad() | 无 | void | 处理加载数据事件 |

## 6. 文件格式设计

### 6.1 数据文件格式 (books.dat)

采用二进制格式存储，结构如下：

```
文件头:
- 魔数 (4 bytes): "BMS\0"
- 版本号 (4 bytes): 1
- 图书数量 (4 bytes): N

图书记录 (每条记录):
- ISBN长度 (4 bytes)
- ISBN字符串 (变长)
- 书名长度 (4 bytes)
- 书名字符串 (变长)
- 作者长度 (4 bytes)
- 作者字符串 (变长)
- 出版社长度 (4 bytes)
- 出版社字符串 (变长)
- 库存量 (4 bytes)
- 价格 (8 bytes)
```

### 6.2 文件操作错误码

| 错误码 | 说明 |
|--------|------|
| 0 | 成功 |
| 1 | 文件打开失败 |
| 2 | 文件格式错误 |
| 3 | 版本不匹配 |
| 4 | 读写错误 |

## 7. 界面布局设计

### 7.1 主窗口布局

```
+-----------------------------------------------------------+
| 图书管理系统                                              |
+-----------------------------------------------------------+
| 左侧面板 (管理功能)        | 右侧面板 (显示区域)          |
|                            |                              |
| ISBN: [____________]       | +------------------------+  |
| 书名: [____________]       | | 图书列表表格           |  |
| 作者: [____________]       | |                        |  |
| 出版社: [__________]       | | ISBN | 书名 | 作者 |  |  |
| 库存: [____________]       | | ...  | ...  | ...  |  |
| 价格: [____________]       | +------------------------+  |
|                            |                              |
| [添加图书] [修改图书]      | 查询: [____________]        |
| [删除图书] [清空输入]      | [按书名查] [按作者查]       |
|                            | [按ISBN查] [按出版社查]     |
| 购买功能:                  |                              |
| ISBN: [____________]       | 结果显示:                    |
| 数量: [____________]       | +------------------------+  |
| [购买图书]                 | | 操作结果和统计信息显示 |  |
|                            | |                        |  |
| 数据操作:                  | |                        |  |
| [保存数据] [加载数据]      | +------------------------+  |
| [统计信息]                 |                              |
+-----------------------------------------------------------+
```

### 7.2 表格列定义

| 列号 | 列名 | 宽度 | 说明 |
|------|------|------|------|
| 0 | ISBN | 120 | ISBN号 |
| 1 | 书名 | 200 | 图书名称 |
| 2 | 作者 | 100 | 作者名称 |
| 3 | 出版社 | 100 | 出版社名称 |
| 4 | 库存 | 60 | 库存数量 |
| 5 | 价格 | 60 | 图书价格 |

## 8. 错误处理设计

### 8.1 错误类型

1. **输入错误**
   - 空输入
   - 格式错误（如价格不是数字）
   - 范围错误（如库存为负数）

2. **业务逻辑错误**
   - ISBN重复
   - 图书不存在
   - 库存不足
   - 文件操作失败

3. **系统错误**
   - 内存不足
   - 文件损坏
   - 版本不兼容

### 8.2 错误提示方式

- 在结果显示区显示红色错误消息
- 弹出对话框提示重要错误
- 日志记录（可选）

## 9. 性能考虑

### 9.1 数据结构选择

- 使用`std::vector`存储图书，适合中小规模数据
- 查询操作时间复杂度：O(n)
- 排序操作使用标准库`sort`，时间复杂度：O(n log n)

### 9.2 优化建议

- 对于大规模数据，可考虑使用其他数据结构
- 实现缓存机制减少文件读写
- 使用索引加速查询

## 10. 扩展性设计

### 10.1 未来扩展方向

1. **多用户支持**：添加用户管理系统
2. **权限控制**：不同用户不同权限
3. **数据备份**：自动备份功能
4. **网络功能**：支持网络访问
5. **报表导出**：支持Excel、PDF等格式导出
6. **数据库支持**：支持MySQL、SQLite等数据库

### 10.2 插件机制

- 设计插件接口
- 支持功能模块动态加载
- 提供扩展点
