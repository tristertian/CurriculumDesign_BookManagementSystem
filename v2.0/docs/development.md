# 图书管理系统开发文档

## 目录
1. [开发环境配置](#开发环境配置)
2. [项目结构](#项目结构)
3. [编译构建](#编译构建)
4. [代码规范](#代码规范)
5. [测试指南](#测试指南)
6. [部署指南](#部署指南)
7. [API参考](#api参考)

## 开发环境配置

### 推荐开发环境

#### Ubuntu/Debian
```bash
# 安装编译工具
sudo apt-get update
sudo apt-get install build-essential

# 安装调试工具
sudo apt-get install gdb valgrind

# 安装代码格式化工具
sudo apt-get install clang-format

# 安装文档工具
sudo apt-get install doxygen graphviz

# 可选：安装FLTK（用于GUI）
sudo apt-get install libfltk1.3-dev
```

#### CentOS/RHEL
```bash
# 安装编译工具
sudo yum groupinstall "Development Tools"

# 安装调试工具
sudo yum install gdb valgrind

# 安装可选依赖
sudo yum install fltk-devel
```

#### macOS
```bash
# 安装Xcode命令行工具
xcode-select --install

# 使用Homebrew安装依赖
brew install gcc gdb valgrind doxygen

# 可选：安装FLTK
brew install fltk
```

#### Windows
```bash
# 推荐使用MinGW-w64或Visual Studio
# 下载地址：https://www.mingw-w64.org/
# 或：https://visualstudio.microsoft.com/

# 可选：使用vcpkg安装FLTK
vcpkg install fltk
```

### 编辑器配置

#### VS Code
推荐插件：
- C/C++
- CMake Tools
- Clang-Tidy
- Code Runner

#### Vim/Neovim
推荐插件：
- YouCompleteMe
- clangd
- ALE

## 项目结构

```
book_management_system/
├── src/                    # 源代码文件
│   ├── main.cpp           # GUI版本主程序
│   ├── ConsoleUI.cpp      # 控制台界面
│   ├── Book.cpp           # 图书类实现
│   ├── SaleRecord.cpp     # 销售记录类实现
│   ├── BookManager.cpp    # 图书管理器实现
│   ├── SalesManager.cpp   # 销售管理器实现
│   ├── StatisticsManager.cpp  # 统计管理器实现
│   └── FileManager.cpp    # 文件管理器实现
│
├── include/               # 头文件
│   ├── Book.h            # 图书类定义
│   ├── SaleRecord.h      # 销售记录类定义
│   ├── BookManager.h     # 图书管理器定义
│   ├── SalesManager.h    # 销售管理器定义
│   ├── StatisticsManager.h  # 统计管理器定义
│   ├── FileManager.h     # 文件管理器定义
│   └── MainWindow.h      # GUI主窗口定义
│
├── docs/                 # 文档
│   ├── design.md         # 设计文档
│   ├── user_manual.md    # 用户手册
│   └── development.md    # 开发文档
│
├── data/                 # 数据文件
│   ├── books.txt         # 图书数据
│   ├── sales.txt         # 销售数据
│   └── backup/           # 备份文件
│
├── bin/                  # 可执行文件
│   ├── book_console      # 控制台版本
│   └── book_gui          # GUI版本
│
├── obj/                  # 对象文件
│
├── Makefile             # 构建脚本
└── README.md            # 项目说明
```

## 编译构建

### 使用Makefile

#### 编译控制台版本
```bash
make console
# 或
make
```

#### 编译GUI版本
```bash
make gui
```

#### 清理构建文件
```bash
make clean
```

#### 运行程序
```bash
# 运行控制台版本
make run-console

# 运行GUI版本
make run-gui
```

### 手动编译

#### 控制台版本
```bash
g++ -std=c++11 -Wall -Wextra -g -I./include \
    src/Book.cpp src/SaleRecord.cpp \
    src/BookManager.cpp src/SalesManager.cpp \
    src/StatisticsManager.cpp src/FileManager.cpp \
    src/ConsoleUI.cpp \
    -o bin/book_console
```

#### GUI版本（需要FLTK）
```bash
g++ -std=c++11 -Wall -Wextra -g -I./include -DUSE_FLTK \
    src/Book.cpp src/SaleRecord.cpp \
    src/BookManager.cpp src/SalesManager.cpp \
    src/StatisticsManager.cpp src/FileManager.cpp \
    src/main.cpp \
    -lfltk -lXext -lXft -lfontconfig -lX11 -lm \
    -o bin/book_gui
```

### 使用CMake（可选）

创建 `CMakeLists.txt`：
```cmake
cmake_minimum_required(VERSION 3.10)
project(BookManagementSystem)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 头文件目录
include_directories(include)

# 源文件
set(SOURCES
    src/Book.cpp
    src/SaleRecord.cpp
    src/BookManager.cpp
    src/SalesManager.cpp
    src/StatisticsManager.cpp
    src/FileManager.cpp
)

# 控制台版本
add_executable(book_console ${SOURCES} src/ConsoleUI.cpp)

# GUI版本（可选）
find_package(FLTK)
if(FLTK_FOUND)
    add_executable(book_gui ${SOURCES} src/main.cpp)
    target_link_libraries(book_gui ${FLTK_LIBRARIES})
endif()
```

编译：
```bash
mkdir build
cd build
cmake ..
make
```

## 代码规范

### 命名规范

#### 类名
使用大驼峰命名法（PascalCase）：
```cpp
class BookManager;
class SalesManager;
```

#### 函数名
使用小驼峰命名法（camelCase）：
```cpp
void displayInfo();
bool addBook(const Book& book);
```

#### 变量名
使用小驼峰命名法（camelCase）：
```cpp
int bookCount;
std::string bookTitle;
```

#### 常量名
使用全大写加下划线：
```cpp
const int MAX_BOOKS = 1000;
const std::string DEFAULT_FILE_NAME = "books.txt";
```

#### 成员变量
使用小驼峰命名法，可加前缀 `m_`：
```cpp
class Book {
private:
    std::string m_title;
    std::string m_isbn;
};
```

### 代码格式

#### 缩进
使用4个空格进行缩进：
```cpp
if (condition) {
    doSomething();
    if (anotherCondition) {
        doSomethingElse();
    }
}
```

#### 大括号
使用K&R风格：
```cpp
void function() {
    // 函数体
}

if (condition) {
    // if体
} else {
    // else体
}
```

#### 空格
运算符两侧加空格：
```cpp
int result = a + b;
bool flag = (x > y) && (y < z);
```

### 注释规范

#### 文件头注释
```cpp
/**
 * @file BookManager.h
 * @brief 图书管理器类定义
 * @author [作者名]
 * @date 2024-01-06
 * @version 1.0
 */
```

#### 类注释
```cpp
/**
 * @class BookManager
 * @brief 管理图书信息的类
 * @details 提供图书的增删改查功能，支持多种查询方式
 */
```

#### 函数注释
```cpp
/**
 * @brief 添加图书
 * @param book 要添加的图书对象
 * @return 添加成功返回true，失败返回false
 * @details 检查ISBN号唯一性，如果已存在则添加失败
 */
bool addBook(const Book& book);
```

#### 行内注释
```cpp
int count = 0;  // 计数器
// TODO: 优化算法性能
// FIXME: 修复边界条件问题
```

### 代码质量

#### 使用智能指针
```cpp
// 推荐
std::shared_ptr<Book> book = std::make_shared<Book>();

// 不推荐
Book* book = new Book();
delete book;  // 容易忘记释放
```

#### 使用const
```cpp
// 成员函数不修改对象
void display() const;

// 参数不修改
void process(const std::string& data);

// 返回值不修改
const std::vector<Book>& getBooks() const;
```

#### 异常安全
```cpp
// 推荐：使用RAII
void processFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file");
    }
    // 文件自动关闭
}
```

## 测试指南

### 单元测试

#### 使用Google Test
安装Google Test：
```bash
sudo apt-get install libgtest-dev
cd /usr/src/gtest
sudo cmake CMakeLists.txt
sudo make
sudo cp *.a /usr/lib
```

创建测试文件 `test/test_book.cpp`：
```cpp
#include <gtest/gtest.h>
#include "Book.h"

TEST(BookTest, ConstructorTest) {
    Book book("Test Book", "Test Publisher", "1234567890", "Test Author", 10, 29.99);
    
    EXPECT_EQ(book.getTitle(), "Test Book");
    EXPECT_EQ(book.getPublisher(), "Test Publisher");
    EXPECT_EQ(book.getIsbn(), "1234567890");
    EXPECT_EQ(book.getAuthor(), "Test Author");
    EXPECT_EQ(book.getStock(), 10);
    EXPECT_DOUBLE_EQ(book.getPrice(), 29.99);
}

TEST(BookTest, SerializationTest) {
    Book original("Test Book", "Test Publisher", "1234567890", "Test Author", 10, 29.99);
    std::string serialized = original.toString();
    
    Book deserialized;
    EXPECT_TRUE(deserialized.fromString(serialized));
    
    EXPECT_EQ(original.getTitle(), deserialized.getTitle());
    EXPECT_EQ(original.getIsbn(), deserialized.getIsbn());
}
```

编译并运行测试：
```bash
g++ -std=c++11 -I./include -I/usr/include/gtest \
    test/test_book.cpp src/Book.cpp \
    -lgtest -lgtest_main -pthread \
    -o test/test_book

./test/test_book
```

### 集成测试

#### 测试脚本
创建测试脚本 `test/integration_test.sh`：
```bash
#!/bin/bash

echo "=== 图书管理系统集成测试 ==="

# 启动程序
./bin/book_console < test_input.txt > test_output.txt 2>&1 &
PID=$!

# 等待程序启动
sleep 1

# 发送测试命令
echo "1" > /proc/$PID/fd/0  # 选择图书管理
echo "1" > /proc/$PID/fd/0  # 添加图书
echo "Test Book" > /proc/$PID/fd/0
echo "Test Publisher" > /proc/$PID/fd/0
echo "1234567890" > /proc/$PID/fd/0
echo "Test Author" > /proc/$PID/fd/0
echo "10" > /proc/$PID/fd/0
echo "29.99" > /proc/$PID/fd/0

# 等待并检查结果
sleep 2
kill $PID

# 验证输出
grep -q "图书添加成功" test_output.txt
if [ $? -eq 0 ]; then
    echo "✓ 添加图书测试通过"
else
    echo "✗ 添加图书测试失败"
fi
```

### 性能测试

#### 压力测试
```cpp
#include <chrono>
#include <iostream>
#include "BookManager.h"

void performanceTest() {
    BookManager manager;
    auto start = std::chrono::high_resolution_clock::now();
    
    // 添加10000本图书
    for (int i = 0; i < 10000; ++i) {
        Book book("Book " + std::to_string(i), 
                 "Publisher " + std::to_string(i % 100),
                 std::to_string(1000000000 + i),
                 "Author " + std::to_string(i % 50),
                 i % 100 + 1,
                 (i % 100) + 0.99);
        manager.addBook(book);
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    std::cout << "添加10000本图书耗时: " << duration.count() << "ms" << std::endl;
}
```

## 部署指南

### 生产环境部署

#### 1. 编译优化版本
```bash
# 使用优化选项编译
make CXXFLAGS="-std=c++11 -O2 -DNDEBUG"

# 或使用strip减小文件大小
strip bin/book_console
```

#### 2. 创建系统服务（Linux）
创建 `/etc/systemd/system/bookmanager.service`：
```ini
[Unit]
Description=Book Management System
After=network.target

[Service]
Type=simple
User=bookmanager
WorkingDirectory=/opt/bookmanager
ExecStart=/opt/bookmanager/bin/book_console
Restart=always
RestartSec=10

[Install]
WantedBy=multi-user.target
```

启动服务：
```bash
sudo systemctl enable bookmanager
sudo systemctl start bookmanager
```

#### 3. 数据备份策略
创建备份脚本 `scripts/backup.sh`：
```bash
#!/bin/bash

BACKUP_DIR="/var/backups/bookmanager"
DATA_DIR="/opt/bookmanager/data"
DATE=$(date +%Y%m%d_%H%M%S)

# 创建备份目录
mkdir -p $BACKUP_DIR

# 备份数据文件
tar -czf $BACKUP_DIR/backup_$DATE.tar.gz -C $DATA_DIR .

# 保留最近30天的备份
find $BACKUP_DIR -name "backup_*.tar.gz" -mtime +30 -delete

echo "Backup completed: backup_$DATE.tar.gz"
```

设置定时任务：
```bash
crontab -e
# 添加以下行，每天凌晨2点备份
0 2 * * * /opt/bookmanager/scripts/backup.sh
```

### Docker部署

创建 `Dockerfile`：
```dockerfile
FROM ubuntu:20.04

# 安装依赖
RUN apt-get update && apt-get install -y \
    build-essential \
    && rm -rf /var/lib/apt/lists/*

# 创建工作目录
WORKDIR /app

# 复制源代码
COPY . .

# 编译程序
RUN make console

# 创建数据目录
RUN mkdir -p data backup

# 设置数据卷
VOLUME ["/app/data", "/app/backup"]

# 暴露端口（如使用网络功能）
EXPOSE 8080

# 启动命令
CMD ["./bin/book_console"]
```

构建和运行：
```bash
# 构建镜像
docker build -t bookmanager:latest .

# 运行容器
docker run -d \
  --name bookmanager \
  -v $(pwd)/data:/app/data \
  -v $(pwd)/backup:/app/backup \
  bookmanager:latest
```

## API参考

### Book类

#### 构造函数
```cpp
Book();  // 默认构造函数
Book(const std::string& title, const std::string& publisher, 
     const std::string& isbn, const std::string& author, 
     int stock, double price);  // 带参数构造函数
Book(const Book& other);  // 拷贝构造函数
```

#### 成员函数
```cpp
// Getter方法
std::string getTitle() const;
std::string getPublisher() const;
std::string getIsbn() const;
std::string getAuthor() const;
int getStock() const;
double getPrice() const;

// Setter方法
void setTitle(const std::string& t);
void setPublisher(const std::string& p);
void setIsbn(const std::string& i);
void setAuthor(const std::string& a);
void setStock(int s);
void setPrice(double p);

// 其他方法
void display() const;
std::string toString() const;
bool fromString(const std::string& str);
```

### BookManager类

#### 图书管理
```cpp
bool addBook(const Book& book);  // 添加图书
bool deleteBook(const std::string& isbn);  // 删除图书
bool updateBook(const std::string& isbn, const Book& newBook);  // 更新图书
```

#### 查询功能
```cpp
std::shared_ptr<Book> findBookByIsbn(const std::string& isbn) const;
std::vector<std::shared_ptr<Book>> findBooksByTitle(const std::string& title) const;
std::vector<std::shared_ptr<Book>> findBooksByAuthor(const std::string& author) const;
std::vector<std::shared_ptr<Book>> findBooksByPublisher(const std::string& publisher) const;
std::vector<std::shared_ptr<Book>> getAllBooks() const;
```

#### 库存管理
```cpp
bool updateStock(const std::string& isbn, int quantity);
int getStock(const std::string& isbn) const;
```

#### 文件操作
```cpp
bool loadFromFile(const std::string& filename);
bool saveToFile(const std::string& filename) const;
```

### SalesManager类

#### 销售操作
```cpp
bool purchaseBook(const std::string& isbn, int quantity);
```

#### 查询功能
```cpp
std::vector<std::shared_ptr<SaleRecord>> getAllSaleRecords() const;
std::vector<std::shared_ptr<SaleRecord>> getSaleRecordsByIsbn(const std::string& isbn) const;
```

#### 统计功能
```cpp
double getTotalSales() const;
int getSaleRecordCount() const;
```

### StatisticsManager类

#### 统计方法
```cpp
void printAllBooksInfo() const;
void printBooksSortedByPrice() const;
void printBooksSortedByStock() const;
void printBooksByAuthor() const;
void printBooksByPublisher() const;
void generateReport() const;
```

#### 统计数据结构
```cpp
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
```

### FileManager类

#### 文件操作
```cpp
bool saveAllData(const BookManager* bookManager, const SalesManager* salesManager) const;
bool loadAllData(BookManager* bookManager, SalesManager* salesManager) const;
bool backupData(const std::string& backupDir = "backup") const;
bool exportBooksToCSV(const std::string& filename) const;
bool exportSalesToCSV(const std::string& filename) const;
```

### 错误处理

#### 异常类型
```cpp
// 文件操作异常
class FileException : public std::runtime_error {
public:
    explicit FileException(const std::string& message)
        : std::runtime_error(message) {}
};

// 数据验证异常
class ValidationException : public std::logic_error {
public:
    explicit ValidationException(const std::string& message)
        : std::logic_error(message) {}
};

// 库存不足异常
class InsufficientStockException : public std::runtime_error {
public:
    explicit InsufficientStockException(const std::string& message)
        : std::runtime_error(message) {}
};
```

#### 错误码
```cpp
enum class ErrorCode {
    SUCCESS = 0,
    ISBN_EXISTS = -1,
    BOOK_NOT_FOUND = -2,
    INSUFFICIENT_STOCK = -3,
    FILE_NOT_FOUND = -4,
    INVALID_DATA = -5
};
```

## 贡献指南

### 代码提交流程
1. Fork项目仓库
2. 创建功能分支：`git checkout -b feature/new-feature`
3. 提交更改：`git commit -am 'Add new feature'`
4. 推送到分支：`git push origin feature/new-feature`
5. 创建Pull Request

### 代码审查标准
- 代码符合项目规范
- 通过所有单元测试
- 添加适当的注释和文档
- 无内存泄漏和未定义行为

### 版本管理
- 使用语义化版本号：MAJOR.MINOR.PATCH
- 主版本：不兼容的API修改
- 次版本：向下兼容的功能性新增
- 修订号：向下兼容的问题修正

## 相关资源

### 文档链接
- [设计文档](design.md)
- [用户手册](user_manual.md)
- [API文档](api.md)（如使用Doxygen生成）

### 外部链接
- [C++ Reference](https://en.cppreference.com/)
- [FLTK Documentation](https://www.fltk.org/doc.php)
- [Google Test](https://github.com/google/googletest)
- [CMake Documentation](https://cmake.org/documentation/)