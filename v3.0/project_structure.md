# 图书管理系统项目结构规划

## 目录结构

```
BMS/
├── include/                          # 头文件目录
│   ├── Book.h                       # 图书类声明
│   ├── BookManager.h                # 图书管理类声明
│   ├── SalesSystem.h                # 销售系统类声明
│   ├── StatisticsSystem.h           # 统计系统类声明
│   └── MainWindow.h                 # 主窗口类声明
├── src/                             # 源文件目录
│   ├── Book.cpp                     # 图书类实现
│   ├── BookManager.cpp              # 图书管理类实现
│   ├── SalesSystem.cpp              # 销售系统类实现
│   ├── StatisticsSystem.cpp         # 统计系统类实现
│   ├── MainWindow.cpp               # 主窗口类实现
│   └── main.cpp                     # 程序入口
├── data/                            # 数据文件目录
│   └── books.dat                    # 图书数据文件
├── docs/                            # 文档目录
│   ├── system_design.md             # 系统设计文档
│   └── project_structure.md         # 项目结构文档
├── CMakeLists.txt                   # CMake构建配置
└── README.md                        # 项目说明文档
```

## 文件详细说明

### 头文件 (include/)

1. **Book.h**
   - 图书类定义
   - 包含书名、出版社、ISBN、作者、库存、价格等属性
   - getter/setter方法声明

2. **BookManager.h**
   - 图书管理类定义
   - 图书增删改查功能
   - 文件存取功能
   - 排序功能

3. **SalesSystem.h**
   - 销售系统类定义
   - 购买书籍功能
   - 库存检查功能
   - 价格计算功能

4. **StatisticsSystem.h**
   - 统计系统类定义
   - 图书总数统计
   - 按不同条件排序统计
   - 作者和出版社统计

5. **MainWindow.h**
   - 主窗口类定义
   - FLTK UI组件声明
   - 事件处理函数声明

### 源文件 (src/)

1. **Book.cpp**
   - 图书类方法实现
   - 构造函数和成员函数实现

2. **BookManager.cpp**
   - 图书管理功能实现
   - 文件读写实现
   - 查询和排序算法实现

3. **SalesSystem.cpp**
   - 销售功能实现
   - 购买流程实现

4. **StatisticsSystem.cpp**
   - 统计功能实现
   - 数据分析和排序实现

5. **MainWindow.cpp**
   - UI界面实现
   - 事件处理实现
   - 界面布局实现

6. **main.cpp**
   - 程序入口函数
   - 系统初始化
   - 主事件循环

### 配置文件

1. **CMakeLists.txt**
   - CMake构建配置
   - FLTK库链接配置
   - 编译选项设置

2. **数据文件**
   - books.dat: 二进制格式的图书数据文件

## 构建和运行

### 构建步骤
```bash
mkdir build
cd build
cmake ..
make
```

### 运行程序
```bash
./BMS
```

## 依赖要求

- C++11 编译器
- FLTK 1.3.x 库
- CMake 3.10+

## 开发顺序建议

1. 先实现核心数据类 (Book, BookManager)
2. 实现业务逻辑类 (SalesSystem, StatisticsSystem)
3. 实现文件存取功能
4. 开发UI界面
5. 系统集成测试