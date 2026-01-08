# 图书管理系统功能调试计划

## 1. 调试目标

### 1.1 功能完整性
- 确保所有功能模块正常工作
- 验证业务逻辑正确性
- 检查数据一致性

### 1.2 性能要求
- 响应时间满足用户需求
- 内存使用合理
- 文件读写效率

### 1.3 稳定性要求
- 无崩溃和异常退出
- 错误处理完善
- 数据安全性

## 2. 调试环境准备

### 2.1 硬件环境
- 开发机：Windows 10/11
- 内存：8GB+
- 存储：SSD推荐

### 2.2 软件环境
- 编译器：Visual Studio 2019+ 或 MinGW-w64
- CMake：3.10+
- FLTK：1.3.x
- C++标准：C++11

### 2.3 测试数据准备
```cpp
// 测试图书数据
测试数据1：
- ISBN: "978-7-111-12345-6"
- 书名: "C++程序设计"
- 作者: "谭浩强"
- 出版社: "机械工业出版社"
- 库存: 50
- 价格: 45.00

测试数据2：
- ISBN: "978-7-302-23456-7"
- 书名: "数据结构与算法"
- 作者: "严蔚敏"
- 出版社: "清华大学出版社"
- 库存: 30
- 价格: 38.00

测试数据3：
- ISBN: "978-7-121-34567-8"
- 书名: "Java核心技术"
- 作者: "Cay Horstmann"
- 出版社: "电子工业出版社"
- 库存: 25
- 价格: 98.00

边界测试数据：
- 空字符串
- 超长字符串（>255字符）
- 负数库存
- 负数价格
- 特殊字符
```

## 3. 单元测试计划

### 3.1 Book类测试

#### 3.1.1 构造函数测试
```cpp
// 测试1：默认构造函数
Book book1;
ASSERT(book1.getISBN().empty());
ASSERT(book1.getStock() == 0);
ASSERT(book1.getPrice() == 0.0);

// 测试2：参数构造函数
Book book2("Test Title", "Test Publisher", "123-456", "Test Author", 10, 29.99);
ASSERT(book2.getTitle() == "Test Title");
ASSERT(book2.getISBN() == "123-456");
ASSERT(book2.getStock() == 10);
ASSERT(book2.getPrice() == 29.99);

// 测试3：拷贝构造函数
Book book3(book2);
ASSERT(book3.getTitle() == book2.getTitle());
ASSERT(book3.getISBN() == book2.getISBN());
```

#### 3.1.2 Getter/Setter测试
```cpp
Book book;

// 测试setter和getter
book.setTitle("New Title");
ASSERT(book.getTitle() == "New Title");

book.setISBN("987-654");
ASSERT(book.getISBN() == "987-654");

book.setStock(100);
ASSERT(book.getStock() == 100);

book.setPrice(59.99);
ASSERT(book.getPrice() == 59.99);
```

#### 3.1.3 边界条件测试
```cpp
Book book;

// 测试空字符串
book.setTitle("");
ASSERT(book.getTitle().empty());

// 测试超长字符串
std::string longStr(1000, 'A');
book.setTitle(longStr);
ASSERT(book.getTitle().length() == 1000);

// 测试负数库存
book.setStock(-5);
ASSERT(book.getStock() == -5); // 应该允许，由业务逻辑控制

// 测试负数价格
book.setPrice(-10.0);
ASSERT(book.getPrice() == -10.0); // 应该允许，由业务逻辑控制
```

### 3.2 BookManager类测试

#### 3.2.1 添加图书测试
```cpp
BookManager manager;
Book book1("C++编程", "机械工业", "123", "作者1", 10, 30.0);

// 测试1：正常添加
ASSERT(manager.addBook(book1) == true);
ASSERT(manager.getBookAmount() == 1);

// 测试2：重复ISBN添加
Book book2("Java编程", "清华大学", "123", "作者2", 20, 40.0);
ASSERT(manager.addBook(book2) == false); // 应该失败
ASSERT(manager.getBookAmount() == 1);

// 测试3：添加多本图书
Book book3("Python编程", "电子工业", "456", "作者3", 15, 35.0);
ASSERT(manager.addBook(book3) == true);
ASSERT(manager.getBookAmount() == 2);
```

#### 3.2.2 查询功能测试
```cpp
BookManager manager;
// 先添加测试数据
manager.addBook(Book("C++", "机工", "001", "A", 10, 30.0));
manager.addBook(Book("Java", "清华", "002", "B", 20, 40.0));
manager.addBook(Book("Python", "电子", "003", "A", 15, 35.0));

// 测试1：按ISBN查询
Book* found = manager.findByISBN("001");
ASSERT(found != nullptr);
ASSERT(found->getTitle() == "C++");

// 测试2：查询不存在的ISBN
Book* notFound = manager.findByISBN("999");
ASSERT(notFound == nullptr);

// 测试3：按书名查询
auto results = manager.findByTitle("C++");
ASSERT(results.size() == 1);

// 测试4：模糊查询
auto results2 = manager.findByTitle("编程");
ASSERT(results2.size() == 0); // 没有完全匹配

// 测试5：按作者查询
auto results3 = manager.findByAuthor("A");
ASSERT(results3.size() == 2);

// 测试6：按出版社查询
auto results4 = manager.findByPublisher("清华");
ASSERT(results4.size() == 1);
```

#### 3.2.3 修改和删除测试
```cpp
BookManager manager;
manager.addBook(Book("C++", "机工", "001", "A", 10, 30.0));

// 测试修改
Book newBook("C++高级", "机工新版", "001", "A", 15, 35.0);
ASSERT(manager.updateBook("001", newBook) == true);
Book* updated = manager.findByISBN("001");
ASSERT(updated->getTitle() == "C++高级");
ASSERT(updated->getPrice() == 35.0);

// 测试删除
ASSERT(manager.deleteBook("001") == true);
ASSERT(manager.getBookAmount() == 0);
ASSERT(manager.findByISBN("001") == nullptr);

// 测试删除不存在的图书
ASSERT(manager.deleteBook("999") == false);
```

#### 3.2.4 排序功能测试
```cpp
BookManager manager;
manager.addBook(Book("Book1", "Pub1", "001", "A", 30, 25.0));
manager.addBook(Book("Book2", "Pub2", "002", "B", 10, 45.0));
manager.addBook(Book("Book3", "Pub3", "003", "C", 20, 15.0));

// 测试按价格排序
auto sortedByPrice = manager.sortByPrice();
ASSERT(sortedByPrice.size() == 3);
ASSERT(sortedByPrice[0]->getPrice() == 45.0); // 最高价格
ASSERT(sortedByPrice[2]->getPrice() == 15.0); // 最低价格

// 测试按库存排序
auto sortedByStock = manager.sortByStock();
ASSERT(sortedByStock.size() == 3);
ASSERT(sortedByStock[0]->getStock() == 30); // 最大库存
ASSERT(sortedByStock[2]->getStock() == 10); // 最小库存
```

### 3.3 SalesSystem类测试

#### 3.3.1 购买功能测试
```cpp
BookManager manager;
manager.addBook(Book("C++", "机工", "001", "A", 10, 30.0));
SaleSys sales(&manager);

// 测试1：正常购买
ASSERT(sales.purchaseBook("001", 5) == true);
ASSERT(manager.findByISBN("001")->getStock() == 5);

// 测试2：购买数量超过库存
ASSERT(sales.purchaseBook("001", 10) == false); // 应该失败
ASSERT(manager.findByISBN("001")->getStock() == 5); // 库存不变

// 测试3：购买不存在的图书
ASSERT(sales.purchaseBook("999", 1) == false);

// 测试4：购买0本
ASSERT(sales.purchaseBook("001", 0) == true);
ASSERT(manager.findByISBN("001")->getStock() == 5); // 库存不变
```

#### 3.3.2 价格计算测试
```cpp
BookManager manager;
manager.addBook(Book("C++", "机工", "001", "A", 10, 30.0));
SaleSys sales(&manager);

// 测试总价计算
ASSERT(sales.getTotalPrice("001", 3) == 90.0);
ASSERT(sales.getTotalPrice("001", 0) == 0.0);

// 测试获取单价
ASSERT(sales.getBookPrice("001") == 30.0);
ASSERT(sales.getBookPrice("999") == 0.0); // 不存在的图书
```

### 3.4 StatisticsSystem类测试

#### 3.4.1 基本统计测试
```cpp
BookManager manager;
manager.addBook(Book("Book1", "Pub1", "001", "A", 10, 30.0));
manager.addBook(Book("Book2", "Pub2", "002", "B", 20, 40.0));
manager.addBook(Book("Book3", "Pub1", "003", "A", 15, 35.0));
StatisSys stats(&manager);

// 测试图书总数
ASSERT(stats.getTotalBooks() == 3);

// 测试总库存
ASSERT(stats.getTotalStock() == 45); // 10 + 20 + 15

// 测试总价值
ASSERT(stats.getTotalValue() == 30.0*10 + 40.0*20 + 35.0*15);

// 测试平均价格
ASSERT(stats.getAveragePrice() == (30.0 + 40.0 + 35.0) / 3.0);
```

#### 3.4.2 筛选和排序测试
```cpp
// 测试按作者筛选
auto booksByA = stats.getBooksByAuthor("A");
ASSERT(booksByA.size() == 2);

// 测试按出版社筛选
auto booksByPub1 = stats.getBooksByPublisher("Pub1");
ASSERT(booksByPub1.size() == 2);

// 测试价格排序
auto sortedByPrice = stats.getBooksSortedByPrice();
ASSERT(sortedByPrice[0]->getPrice() >= sortedByPrice[1]->getPrice());

// 测试库存排序
auto sortedByStock = stats.getBooksSortedByStock();
ASSERT(sortedByStock[0]->getStock() >= sortedByStock[1]->getStock());
```

### 3.5 文件存取测试

#### 3.5.1 文件保存测试
```cpp
BookManager manager;
manager.addBook(Book("C++", "机工", "001", "A", 10, 30.0));
manager.addBook(Book("Java", "清华", "002", "B", 20, 40.0));

// 测试保存到文件
ASSERT(manager.saveFile("test_books.dat") == true);
ASSERT(std::ifstream("test_books.dat").good() == true);
```

#### 3.5.2 文件加载测试
```cpp
BookManager manager;

// 测试从文件加载
ASSERT(manager.loadFile("test_books.dat") == true);
ASSERT(manager.getBookAmount() == 2);
ASSERT(manager.findByISBN("001") != nullptr);
ASSERT(manager.findByISBN("002") != nullptr);

// 测试加载不存在的文件
BookManager manager2;
ASSERT(manager2.loadFile("nonexistent.dat") == false);

// 测试加载损坏的文件
std::ofstream badFile("bad.dat", std::ios::binary);
badFile << "corrupted data";
badFile.close();
BookManager manager3;
ASSERT(manager3.loadFile("bad.dat") == false);
```

## 4. 集成测试计划

### 4.1 功能流程测试

#### 4.1.1 完整业务流程测试
```cpp
// 场景：添加图书 -> 查询 -> 修改 -> 购买 -> 统计 -> 保存 -> 加载

BookManager manager;
SaleSys sales(&manager);
StatisSys stats(&manager);

// 1. 添加图书
manager.addBook(Book("C++", "机工", "001", "A", 50, 45.0));
manager.addBook(Book("Java", "清华", "002", "B", 30, 38.0));

// 2. 查询图书
auto found = manager.findByISBN("001");
ASSERT(found != nullptr);

// 3. 修改图书
Book updated("C++高级", "机工新版", "001", "A", 45, 48.0);
manager.updateBook("001", updated);

// 4. 购买图书
sales.purchaseBook("001", 5);
ASSERT(manager.findByISBN("001")->getStock() == 40);

// 5. 统计信息
ASSERT(stats.getTotalBooks() == 2);
ASSERT(stats.getTotalStock() == 70); // 40 + 30

// 6. 保存到文件
manager.saveFile("integration_test.dat");

// 7. 加载到新管理器
BookManager manager2;
manager2.loadFile("integration_test.dat");
ASSERT(manager2.getBookAmount() == 2);
ASSERT(manager2.findByISBN("001")->getStock() == 40);
```

### 4.2 UI界面测试

#### 4.2.1 界面元素测试
- [ ] 所有按钮可点击
- [ ] 输入框可输入
- [ ] 表格显示正确
- [ ] 结果显示区域正常

#### 4.2.2 交互流程测试
- [ ] 添加图书流程
- [ ] 查询图书流程
- [ ] 修改图书流程
- [ ] 删除图书流程
- [ ] 购买图书流程
- [ ] 统计功能流程
- [ ] 文件保存/加载流程

## 5. 性能测试计划

### 5.1 大数据量测试
```cpp
// 测试大量图书数据的性能
BookManager manager;

// 添加1000本图书
for (int i = 0; i < 1000; i++) {
    std::string isbn = "ISBN" + std::to_string(i);
    std::string title = "Book" + std::to_string(i);
    manager.addBook(Book(title, "Publisher", isbn, "Author", i % 100, (i % 50) + 10.0));
}

// 测试查询性能
auto start = std::chrono::high_resolution_clock::now();
auto result = manager.findByISBN("ISBN500");
auto end = std::chrono::high_resolution_clock::now();
auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
ASSERT(duration.count() < 1000); // 查询时间应小于1毫秒

// 测试排序性能
start = std::chrono::high_resolution_clock::now();
auto sorted = manager.sortByPrice();
end = std::chrono::high_resolution_clock::now();
duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
ASSERT(duration.count() < 100); // 排序时间应小于100毫秒
```

### 5.2 文件读写性能测试
```cpp
BookManager manager;

// 添加测试数据
for (int i = 0; i < 100; i++) {
    std::string isbn = "ISBN" + std::to_string(i);
    std::string title = "Book" + std::to_string(i);
    manager.addBook(Book(title, "Publisher", isbn, "Author", 50, 30.0));
}

// 测试保存性能
auto start = std::chrono::high_resolution_clock::now();
manager.saveFile("perf_test.dat");
auto end = std::chrono::high_resolution_clock::now();
auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
ASSERT(duration.count() < 500); // 保存时间应小于500毫秒

// 测试加载性能
BookManager manager2;
start = std::chrono::high_resolution_clock::now();
manager2.loadFile("perf_test.dat");
end = std::chrono::high_resolution_clock::now();
duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
ASSERT(duration.count() < 500); // 加载时间应小于500毫秒
```

## 6. 错误处理测试

### 6.1 异常情况测试
```cpp
// 测试空指针处理
BookManager* nullManager = nullptr;
// SaleSys sales(nullManager); // 应该抛出异常或处理

// 测试文件权限问题
// 尝试保存到只读目录
// manager.saveFile("/root/test.dat"); // 应该失败

// 测试磁盘满的情况
// 需要模拟磁盘满的场景

// 测试并发访问（如果有多线程）
// 需要线程安全测试
```

### 6.2 边界条件测试
```cpp
// 测试库存为0的情况
BookManager manager;
manager.addBook(Book("Book", "Pub", "001", "A", 0, 30.0));
SaleSys sales(&manager);
ASSERT(sales.purchaseBook("001", 1) == false);

// 测试价格为0的情况
manager.addBook(Book("FreeBook", "Pub", "002", "B", 10, 0.0));
ASSERT(sales.getTotalPrice("002", 5) == 0.0);

// 测试极大数值
manager.addBook(Book("Book", "Pub", "003", "C", INT_MAX, DBL_MAX));
ASSERT(manager.findByISBN("003")->getStock() == INT_MAX);
```

## 7. 用户验收测试

### 7.1 功能验收清单

#### 图书管理功能
- [ ] 添加图书：ISBN唯一性检查
- [ ] 查询图书：支持多种查询方式
- [ ] 修改图书：保持ISBN唯一性
- [ ] 删除图书：确认删除操作

#### 销售功能
- [ ] 购买流程：库存检查
- [ ] 价格计算：正确计算总价
- [ ] 库存更新：购买后库存减少

#### 统计功能
- [ ] 总数统计：图书种类和库存
- [ ] 排序统计：按价格、库存排序
- [ ] 筛选统计：按作者、出版社筛选

#### 文件功能
- [ ] 保存数据：完整保存所有信息
- [ ] 加载数据：正确恢复数据
- [ ] 文件格式：二进制格式正确

### 7.2 界面验收清单
- [ ] 界面布局：合理美观
- [ ] 操作流程：直观易用
- [ ] 错误提示：清晰明确
- [ ] 响应速度：快速流畅

## 8. 调试工具和方法

### 8.1 调试工具
- Visual Studio调试器
- GDB（Linux环境）
- 内存检测工具（Valgrind）
- 性能分析工具

### 8.2 调试方法
- 断点调试
- 单步执行
- 变量监视
- 内存检查
- 日志输出

### 8.3 日志记录
```cpp
// 建议添加日志系统
enum class LogLevel {
    DEBUG,
    INFO,
    WARNING,
    ERROR
};

class Logger {
public:
    static void log(LogLevel level, const std::string& message);
    static void debug(const std::string& message);
    static void info(const std::string& message);
    static void warning(const std::string& message);
    static void error(const std::string& message);
};
```

## 9. 测试报告模板

### 9.1 测试报告格式
```
测试报告
========

测试日期：YYYY-MM-DD
测试人员：XXX
测试版本：vX.X.X

1. 测试概述
   - 测试范围
   - 测试环境
   - 测试数据

2. 测试结果
   - 通过的测试：XX/XX
   - 失败的测试：XX/XX
   - 未完成的测试：XX/XX

3. 详细结果
   - 功能测试：
     * 添加图书：通过/失败
     * 查询图书：通过/失败
     * ...
   
   - 性能测试：
     * 查询响应时间：XXXms
     * 排序响应时间：XXXms
     * ...

4. 问题列表
   - 问题1：描述
     * 严重程度：高/中/低
     * 状态：已修复/未修复
   
   - 问题2：描述
     * 严重程度：高/中/低
     * 状态：已修复/未修复

5. 结论
   - 系统是否可接受
   - 建议和改进
```

## 10. 回归测试计划

### 10.1 回归测试策略
- 每次修改后运行核心功能测试
- 重点测试修改相关的功能
- 定期进行完整测试

### 10.2 自动化测试
- 建议编写自动化测试脚本
- 使用CI/CD进行持续集成
- 自动化测试覆盖率目标：80%+

## 11. 性能优化建议

### 11.1 性能瓶颈分析
- 查询操作：O(n)复杂度，大数据量时可能慢
- 排序操作：O(n log n)复杂度
- 文件I/O：二进制格式已优化

### 11.2 优化方案
- 使用索引加速查询
- 实现缓存机制
- 考虑使用多线程
- 数据库替代方案（未来）

## 12. 安全测试考虑

### 12.1 数据安全
- 文件加密存储
- 数据备份机制
- 防止数据损坏

### 12.2 输入验证
- 防止缓冲区溢出
- 输入长度限制
- 特殊字符处理

## 13. 调试完成标准

### 13.1 功能完成标准
- [ ] 所有功能测试通过
- [ ] 边界条件测试通过
- [ ] 错误处理测试通过
- [ ] 用户验收测试通过

### 13.2 性能完成标准
- [ ] 查询响应时间 < 1秒
- [ ] 排序响应时间 < 3秒
- [ ] 文件读写时间 < 5秒
- [ ] 内存使用合理

### 13.3 稳定性完成标准
- [ ] 连续运行24小时无崩溃
- [ ] 大数据量测试通过
- [ ] 并发测试通过（如适用）
- [ ] 错误恢复机制正常

## 14. 后续工作建议

### 14.1 持续改进
- 收集用户反馈
- 定期更新和优化
- 添加新功能

### 14.2 维护计划
- 定期备份数据
- 监控系统性能
- 及时修复bug

### 14.3 扩展功能
- 多用户支持
- 权限管理
- 网络功能
- 数据库支持