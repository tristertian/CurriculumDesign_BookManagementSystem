# 图书管理系统 (Book Management System)

一个功能完善的图书管理系统，采用C++面向对象编程技术开发。

![C++](https://img.shields.io/badge/C%2B%2B-11-blue.svg)
![License](https://img.shields.io/badge/License-MIT-green.svg)
![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20Windows%20%7C%20macOS-lightgrey.svg)

## 📋 目录

- [功能特性](#功能特性)
- [快速开始](#快速开始)
- [系统架构](#系统架构)
- [主要功能](#主要功能)
- [文件结构](#文件结构)
- [编译运行](#编译运行)
- [使用示例](#使用示例)
- [文档](#文档)
- [贡献指南](#贡献指南)
- [许可证](#许可证)

## ✨ 功能特性

### 核心功能
- ✅ **图书管理**: 添加、查询、修改、删除图书信息
- ✅ **销售管理**: 图书购买、库存管理、销售记录
- ✅ **统计查询**: 多维度统计、排序展示、综合报告
- ✅ **数据持久化**: 文件存盘、自动备份、CSV导出
- ✅ **用户界面**: 控制台界面、操作简单直观

### 技术特性
- 🚀 **面向对象设计**: 采用C++11标准，良好的封装、继承、多态
- 🏗️ **模块化架构**: 清晰的模块划分，易于扩展和维护
- 💾 **数据安全**: 智能指针管理内存，RAII原则
- 📊 **高效查询**: 多种查询方式，支持索引优化
- 🛡️ **异常处理**: 完善的错误处理机制
- 📈 **性能优化**: 使用STL容器和算法，高效排序和统计

## 🚀 快速开始

### 系统要求
- 编译器: GCC 4.8+ / Clang 3.3+ / MSVC 2013+
- 操作系统: Linux / Windows / macOS
- 依赖: 标准C++库（可选FLTK用于GUI）

### 安装运行

```bash
# 克隆项目
git clone https://github.com/yourusername/book-management-system.git
cd book-management-system

# 编译项目
make console

# 运行程序
./bin/book_console
```

### 添加第一本图书
```
请选择操作: 1  (图书管理)
请选择操作: 1  (添加图书)
书名: C++程序设计教程
出版社: 清华大学出版社
ISBN号: 9787302168979
作者: 谭浩强
库存量: 10
价格: 59.90

图书添加成功！
```

## 🏗️ 系统架构

### 类层次结构

```
实体类 (Entity)
├── Book (图书信息)
│   ├── 书名、出版社、ISBN、作者、库存、价格
│   └── 序列化、显示、比较
│
└── SaleRecord (销售记录)
    ├── ISBN、书名、数量、总价、时间
    └── 记录管理、统计

管理类 (Manager)
├── BookManager (图书管理)
│   ├── 增删改查图书
│   ├── 库存管理
│   └── 文件操作
│
├── SalesManager (销售管理)
│   ├── 购买处理
│   ├── 销售记录
│   └── 销售额统计
│
├── StatisticsManager (统计管理)
│   ├── 多维度统计
│   ├── 排序展示
│   └── 综合报告
│
└── FileManager (文件管理)
    ├── 数据持久化
    ├── 自动备份
    └── CSV导出

界面类 (UI)
├── ConsoleUI (控制台界面)
└── MainWindow (GUI界面，可选)
```

### 数据流

```
用户界面 → 管理器 → 实体对象 → 文件存储
    ↓              ↓              ↓
显示结果 ←  业务逻辑  ←  数据验证  ←  数据加载
```

## 📖 主要功能

### 1. 图书管理

#### 添加图书
- 输入完整的图书信息
- 自动检查ISBN号唯一性
- 验证数据格式和范围

#### 查询图书
支持多种查询方式：
- 按ISBN号查询（精确匹配）
- 按书名查询（完全匹配）
- 按作者查询
- 按出版社查询

#### 修改图书
- 根据ISBN号定位图书
- 可修改任意字段
- 自动验证新数据的合法性

#### 删除图书
- 根据ISBN号删除
- 删除前确认
- 自动清理相关引用

### 2. 销售管理

#### 购买图书
- 输入ISBN号和购买数量
- 自动检查库存充足性
- 计算总价并生成销售记录
- 自动更新库存

#### 销售记录
- 记录每次销售的详细信息
- 包含时间戳
- 支持按ISBN号查询销售记录

#### 销售统计
- 总销售额统计
- 销售记录数量统计
- 支持时间段筛选（可扩展）

### 3. 统计查询

#### 图书统计
- 显示所有图书信息
- 按价格排序（从高到低）
- 按库存量排序（从多到少）
- 按作者分组统计
- 按出版社分组统计

#### 综合报告
生成包含以下信息的完整报告：
- **库存统计**: 种类总数、库存总量、最大/最小/平均库存量
- **价格统计**: 最高/最低/平均价格、库存总价值
- **销售统计**: 销售记录总数、总销售额

### 4. 数据管理

#### 数据存盘
- 将图书信息保存到 `books.txt`
- 将销售记录保存到 `sales.txt`
- 支持手动保存
- 退出时自动保存（可选）

#### 读取数据
- 从文件加载图书信息
- 从文件加载销售记录
- 启动时自动加载
- 错误恢复机制

#### 数据备份
- 自动备份功能
- 备份文件带时间戳
- 支持定期清理旧备份

#### 数据导出
- 导出为CSV格式
- 便于Excel等软件分析
- 支持自定义导出字段

## 📁 文件结构

```
book_management_system/
├── src/                          # 源代码
│   ├── main.cpp                 # GUI主程序
│   ├── ConsoleUI.cpp            # 控制台界面
│   ├── Book.cpp                 # 图书类实现
│   ├── SaleRecord.cpp           # 销售记录类实现
│   ├── BookManager.cpp          # 图书管理器
│   ├── SalesManager.cpp         # 销售管理器
│   ├── StatisticsManager.cpp    # 统计管理器
│   └── FileManager.cpp          # 文件管理器
│
├── include/                     # 头文件
│   ├── MainWindow.h            # GUI主窗口
│   ├── Book.h                  # 图书类定义
│   ├── SaleRecord.h            # 销售记录类定义
│   ├── BookManager.h           # 图书管理器定义
│   ├── SalesManager.h          # 销售管理器定义
│   ├── StatisticsManager.h     # 统计管理器定义
│   └── FileManager.h           # 文件管理器定义
│
├── docs/                        # 文档
│   ├── design.md               # 设计文档
│   ├── user_manual.md          # 用户手册
│   └── development.md          # 开发文档
│
├── data/                        # 数据文件
│   ├── books.txt               # 图书数据
│   ├── sales.txt               # 销售数据
│   └── backup/                 # 备份文件
│
├── bin/                         # 可执行文件
│   ├── book_console            # 控制台版本
│   └── book_gui               # GUI版本
│
├── Makefile                    # 构建脚本
├── README.md                   # 项目说明
└── LICENSE                     # 许可证
```

## 🔧 编译运行

### 使用Makefile

```bash
# 编译控制台版本
make console

# 编译GUI版本（需要FLTK）
make gui

# 清理构建文件
make clean

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

#### GUI版本
```bash
g++ -std=c++11 -Wall -Wextra -g -I./include -DUSE_FLTK \
    src/Book.cpp src/SaleRecord.cpp \
    src/BookManager.cpp src/SalesManager.cpp \
    src/StatisticsManager.cpp src/FileManager.cpp \
    src/main.cpp \
    -lfltk -lXext -lXft -lfontconfig -lX11 -lm \
    -o bin/book_gui
```

### 安装依赖

#### Ubuntu/Debian
```bash
sudo apt-get update
sudo apt-get install build-essential

# 可选：安装FLTK
sudo apt-get install libfltk1.3-dev
```

#### CentOS/RHEL
```bash
sudo yum groupinstall "Development Tools"
sudo yum install fltk-devel
```

#### macOS
```bash
# 安装Xcode命令行工具
xcode-select --install

# 使用Homebrew
brew install gcc gdb valgrind doxygen fltk
```

## 💡 使用示例

### 示例1: 完整的图书管理流程

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
请选择操作: 1

========== 图书管理 ==========
1. 添加图书
2. 查询图书
3. 修改图书
4. 删除图书
5. 显示所有图书
6. 返回主菜单
==============================
请选择操作: 1

请输入图书信息:
书名: C++ Primer (第5版)
出版社: 电子工业出版社
ISBN号: 9787121391318
作者: Stanley B. Lippman
库存量: 5
价格: 128.00
图书添加成功！

========== 图书管理 ==========
1. 添加图书
2. 查询图书
3. 修改图书
4. 删除图书
5. 显示所有图书
6. 返回主菜单
==============================
请选择操作: 2

========== 图书查询 ==========
1. 按ISBN号查询
2. 按书名查询
3. 按作者查询
4. 按出版社查询
5. 返回上级菜单
==============================
请选择操作: 1
请输入ISBN号: 9787121391318

查询结果:
====================================
书名: C++ Primer (第5版)
出版社: 电子工业出版社
ISBN号: 9787121391318
作者: Stanley B. Lippman
库存量: 5
价格: ¥128.00
====================================
```

### 示例2: 图书销售流程

```
========== 图书管理 ==========
1. 添加图书
2. 查询图书
3. 修改图书
4. 删除图书
5. 显示所有图书
6. 返回主菜单
==============================
请选择操作: 6

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
请选择操作: 2

请输入要购买的图书ISBN号: 9787121391318

图书信息:
====================================
书名: C++ Primer (第5版)
出版社: 电子工业出版社
ISBN号: 9787121391318
作者: Stanley B. Lippman
库存量: 5
价格: ¥128.00
====================================

请输入购买数量: 2

购买成功！
图书: C++ Primer (第5版)
数量: 2
总价: ¥256.00
```

### 示例3: 统计查询

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
请选择操作: 3

========== 统计查询 ==========
1. 显示所有图书
2. 按价格排序统计
3. 按库存量排序统计
4. 按作者统计
5. 按出版社统计
6. 生成综合统计报告
7. 显示销售记录
8. 返回主菜单
==============================
请选择操作: 6

========================================
          图书管理系统统计报告          
========================================

【库存统计】
图书种类总数: 2 种
库存总量: 13 册
最大库存量: 10 册
最小库存量: 3 册
平均库存量: 6.5 册

【价格统计】
最高价格: ¥128.00
最低价格: ¥59.90
平均价格: ¥93.95
库存总价值: ¥1221.35

【销售统计】
销售记录总数: 1 条
总销售额: ¥256.00

========================================
```

## 📚 文档

- [📖 设计文档](docs/design.md) - 系统架构、类设计、数据流程
- [👤 用户手册](docs/user_manual.md) - 安装指南、使用教程、常见问题
- [🔧 开发文档](docs/development.md) - 环境配置、API参考、贡献指南

## 🤝 贡献指南

我们欢迎所有形式的贡献！

### 如何贡献

1. **Fork项目**
   ```bash
   # 点击GitHub上的Fork按钮
   git clone https://github.com/yourusername/book-management-system.git
   ```

2. **创建功能分支**
   ```bash
   git checkout -b feature/new-feature
   ```

3. **提交更改**
   ```bash
   git add .
   git commit -m "Add new feature: description"
   ```

4. **推送到分支**
   ```bash
   git push origin feature/new-feature
   ```

5. **创建Pull Request**
   - 在GitHub上创建PR
   - 描述更改内容
   - 等待代码审查

### 代码规范

- 使用4个空格缩进
- 类名使用大驼峰命名法（PascalCase）
- 函数和变量名使用小驼峰命名法（camelCase）
- 常量使用全大写加下划线
- 添加适当的注释

### 开发流程

1. 阅读[开发文档](docs/development.md)
2. 配置开发环境
3. 编写代码并添加测试
4. 运行测试确保通过
5. 提交Pull Request

### 报告问题

如果遇到问题，请通过以下方式报告：
- 创建GitHub Issue
- 提供详细的错误描述
- 附上相关的日志文件
- 说明复现步骤

## 📝 许可证

本项目采用 MIT 许可证 - 查看 [LICENSE](LICENSE) 文件了解详情。

## 🙏 致谢

- 感谢所有贡献者的努力
- 感谢开源社区的支持
- 感谢C++标准委员会

## 📞 联系方式

- **项目地址**: [GitHub](https://github.com/yourusername/book-management-system)
- **问题反馈**: [Issues](https://github.com/yourusername/book-management-system/issues)
- **邮件**: your.email@example.com

---

**如果觉得这个项目有帮助，请给个⭐ Star！**