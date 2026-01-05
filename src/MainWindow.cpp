#include "../include/MainWindow.h"
#include <sstream>

MainWindow::MainWindow(int w, int h, const char* title) 
    : Fl_Window(w, h, title), 
      sales(bookManager), 
      statistics(bookManager),
      fileOps("data/books.dat") {
    
    // 创建菜单栏
    menuBar = new Fl_Menu_Bar(0, 0, w, 30);
    menuBar->add("图书/添加", 0, menuCallback, this);
    menuBar->add("图书/查询", 0, menuCallback, this);
    menuBar->add("图书/删除", 0, menuCallback, this);
    menuBar->add("销售/销售图书", 0, menuCallback, this);
    menuBar->add("统计/所有图书", 0, menuCallback, this);
    menuBar->add("统计/按价格", 0, menuCallback, this);
    menuBar->add("统计/按库存", 0, menuCallback, this);
    menuBar->add("文件/保存", 0, menuCallback, this);
    menuBar->add("文件/加载", 0, menuCallback, this);
    menuBar->add("文件/退出", 0, menuCallback, this);
    
    // 创建文本显示区域
    textBuffer = new Fl_Text_Buffer();
    outputDisplay = new Fl_Multiline_Output(10, 40, w - 20, h - 50);
    outputDisplay->textsize(12);
    
    updateDisplay("图书管理系统已启动。请使用菜单进行操作。");
}

MainWindow::~MainWindow() {
    delete textBuffer;
}

void MainWindow::menuCallback(Fl_Widget* w, void* data) {
    MainWindow* window = static_cast<MainWindow*>(data);
    Fl_Menu_Bar* menu = static_cast<Fl_Menu_Bar*>(w);
    const Fl_Menu_Item* item = menu->mvalue();
    
    if (strcmp(item->label(), "添加") == 0) {
        window->showAddBookDialog();
    } else if (strcmp(item->label(), "查询") == 0) {
        window->showSearchDialog();
    } else if (strcmp(item->label(), "删除") == 0) {
        const char* isbn = fl_input("请输入要删除的ISBN号:");
        if (isbn) {
            if (window->bookManager.deleteBook(isbn)) {
                window->updateDisplay("图书删除成功！");
            } else {
                window->updateDisplay("错误：该ISBN号不存在！");
            }
        }
    } else if (strcmp(item->label(), "销售图书") == 0) {
        window->showSellDialog();
    } else if (strcmp(item->label(), "所有图书") == 0) {
        window->showAllBooks();
    } else if (strcmp(item->label(), "按价格") == 0) {
        auto books = window->statistics.sortByPrice();
        std::stringstream ss;
        ss << "========== 按价格排序 ==========\n";
        for (auto* book : books) {
            book->displayInfo(ss);
            ss << "\n";
        }
        window->updateDisplay(ss.str());
    } else if (strcmp(item->label(), "按库存") == 0) {
        auto books = window->statistics.sortByStock();
        std::stringstream ss;
        ss << "========== 按库存排序 ==========\n";
        for (auto* book : books) {
            book->displayInfo(ss);
            ss << "\n";
        }
        window->updateDisplay(ss.str());
    } else if (strcmp(item->label(), "保存") == 0) {
        window->saveToFile();
    } else if (strcmp(item->label(), "加载") == 0) {
        window->loadFromFile();
    } else if (strcmp(item->label(), "退出") == 0) {
        window->hide();
    }
}

void MainWindow::showAddBookDialog() {
    // 创建输入对话框
    const char* title = fl_input("请输入书名:");
    if (!title) return;
    
    const char* publisher = fl_input("请输入出版社:");
    if (!publisher) return;
    
    const char* isbn = fl_input("请输入ISBN号:");
    if (!isbn) return;
    
    const char* author = fl_input("请输入作者:");
    if (!author) return;
    
    const char* stock_str = fl_input("请输入库存量:");
    if (!stock_str) return;
    
    const char* price_str = fl_input("请输入价格:");
    if (!price_str) return;
    
    int stock = std::atoi(stock_str);
    double price = std::atof(price_str);
    
    Book newBook(title, publisher, isbn, author, stock, price);
    
    if (bookManager.addBook(newBook)) {
        updateDisplay("图书添加成功！");
    } else {
        updateDisplay("错误：ISBN号重复，添加失败！");
    }
}

void MainWindow::showSearchDialog() {
    const char* type = fl_input("请选择查询类型 (1-书名, 2-ISBN, 3-作者, 4-出版社):");
    if (!type) return;
    
    int searchType = std::atoi(type);
    const char* keyword = fl_input("请输入查询关键字:");
    if (!keyword) return;
    
    std::vector<IBookOperations*> results;
    std::stringstream ss;
    
    switch (searchType) {
        case 1:
            results = bookManager.findByTitle(keyword);
            break;
        case 2:
            results = bookManager.findByISBN(keyword);
            break;
        case 3:
            results = bookManager.findByAuthor(keyword);
            break;
        case 4:
            results = bookManager.findByPublisher(keyword);
            break;
        default:
            updateDisplay("无效的查询类型！");
            return;
    }
    
    if (results.empty()) {
        ss << "该标题不存在！";
    } else {
        ss << "========== 查询结果 ==========\n";
        for (auto* book : results) {
            book->displayInfo(ss);
            ss << "\n";
        }
        ss << "============================";
    }
    
    updateDisplay(ss.str());
}

void MainWindow::showSellDialog() {
    const char* isbn = fl_input("请输入要购买的图书ISBN:");
    if (!isbn) return;
    
    const char* quantity_str = fl_input("请输入购买数量:");
    if (!quantity_str) return;
    
    int quantity = std::atoi(quantity_str);
    double totalPrice = 0.0;
    
    if (sales.sellBook(isbn, quantity, totalPrice)) {
        std::stringstream ss;
        ss << "销售成功！\n应付金额: ¥" << totalPrice 
           << "\n当前总收入: ¥" << sales.getTotalRevenue();
        updateDisplay(ss.str());
    } else {
        updateDisplay("销售失败！请检查ISBN号或库存是否充足。");
    }
}

void MainWindow::showAllBooks() {
    std::stringstream ss;
    statistics.printAllBooks(ss);
    updateDisplay(ss.str());
}

void MainWindow::saveToFile() {
    if (fileOps.save(bookManager)) {
        updateDisplay("数据保存成功！");
    } else {
        updateDisplay("错误：数据保存失败！");
    }
}

void MainWindow::loadFromFile() {
    if (fileOps.load(bookManager)) {
        updateDisplay("数据加载成功！");
    } else {
        updateDisplay("错误：数据加载失败！");
    }
}

void MainWindow::updateDisplay(const std::string& message) {
    outputDisplay->value(message.c_str());
}