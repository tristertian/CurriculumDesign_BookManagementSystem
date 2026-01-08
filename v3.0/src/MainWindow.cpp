#include "../include/MainWindow.h"
#include <FL/fl_ask.H>
#include <FL/Fl_Table_Row.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Box.H>
#include <sstream>
#include <iomanip>

// 表格类定义
class BookTable : public Fl_Table_Row {
private:
    MainWindow* mainWindow;
    
public:
    BookTable(int x, int y, int w, int h, MainWindow* window) 
        : Fl_Table_Row(x, y, w, h), mainWindow(window) {
        cols(6);
        rows(0);
        col_header(1);
        row_header(0);
        col_resize(1);
        row_resize(0);
        end();
    }
    
    void draw_cell(TableContext context, int R, int C, int X, int Y, int W, int H) {
        switch (context) {
            case CONTEXT_STARTPAGE:
                fl_font(FL_HELVETICA, 12);
                return;
            
            case CONTEXT_COL_HEADER:
                fl_push_clip(X, Y, W, H);
                {
                    fl_draw_box(FL_THIN_UP_BOX, X, Y, W, H, color());
                    fl_color(FL_BLACK);
                    const char* headers[] = {"ISBN", "书名", "作者", "出版社", "库存", "价格"};
                    if (C < 6) {
                        fl_draw(headers[C], X + 5, Y, W, H, FL_ALIGN_CENTER);
                    }
                }
                fl_pop_clip();
                return;
            
            case CONTEXT_CELL: {
                fl_push_clip(X, Y, W, H);
                {
                    // 绘制单元格背景
                    if (R % 2 == 0) {
                        fl_color(fl_rgb_color(240, 240, 240));
                    } else {
                        fl_color(FL_WHITE);
                    }
                    fl_rectf(X, Y, W, H);
                    
                    // 绘制边框
                    fl_color(FL_LIGHT2);
                    fl_rect(X, Y, W, H);
                    
                    // 绘制文本
                    fl_color(FL_BLACK);
                    
                    // 获取图书数据
                    auto books = mainWindow->getBookManager()->getAllBooks();
                    if (R < static_cast<int>(books.size())) {
                        const Book& book = books[R];
                        std::string text;
                        switch (C) {
                            case 0: text = book.getISBN(); break;
                            case 1: text = book.getTitle(); break;
                            case 2: text = book.getAuthor(); break;
                            case 3: text = book.getPublisher(); break;
                            case 4: text = std::to_string(book.getStock()); break;
                            case 5: 
                                std::stringstream ss;
                                ss << "¥" << std::fixed << std::setprecision(2) << book.getPrice();
                                text = ss.str();
                                break;
                        }
                        fl_draw(text.c_str(), X + 5, Y, W, H, FL_ALIGN_LEFT);
                    }
                }
                fl_pop_clip();
                return;
            }
            
            default:
                return;
        }
    }
};

// 构造函数
MainWindow::MainWindow(int width, int height, const char* title) 
    : Fl_Window(width, height, title), selectedISBN("") {
    
    // 创建系统组件
    bookManager = new BookManager();
    saleSys = new SaleSys(bookManager);
    statsSystem = new StatisSys(bookManager);
    
    // 设置UI
    setupUI();
    setupCallbacks();
    
    // 设置窗口属性
    resizable(this);
    size_range(800, 600);
}

// 析构函数
MainWindow::~MainWindow() {
    delete saleSys;
    delete statsSystem;
    delete bookManager;
}

// 设置UI界面
void MainWindow::setupUI() {
    // 左侧面板
    Fl_Group* leftPanel = new Fl_Group(10, 10, 380, 580);
    
    // 标题
    Fl_Box* titleBox = new Fl_Box(10, 10, 380, 30, "图书信息管理");
    titleBox->labelfont(FL_BOLD);
    titleBox->labelsize(16);
    titleBox->align(FL_ALIGN_CENTER);
    
    // 输入框标签和输入框
    int y = 50;
    Fl_Box* isbnLabel = new Fl_Box(10, y, 80, 25, "ISBN:");
    isbnLabel->align(FL_ALIGN_RIGHT | FL_ALIGN_INSIDE);
    isbnInput = new Fl_Input(95, y, 280, 25);
    
    y += 35;
    Fl_Box* titleLabel = new Fl_Box(10, y, 80, 25, "书名:");
    titleLabel->align(FL_ALIGN_RIGHT | FL_ALIGN_INSIDE);
    titleInput = new Fl_Input(95, y, 280, 25);
    
    y += 35;
    Fl_Box* authorLabel = new Fl_Box(10, y, 80, 25, "作者:");
    authorLabel->align(FL_ALIGN_RIGHT | FL_ALIGN_INSIDE);
    authorInput = new Fl_Input(95, y, 280, 25);
    
    y += 35;
    Fl_Box* publisherLabel = new Fl_Box(10, y, 80, 25, "出版社:");
    publisherLabel->align(FL_ALIGN_RIGHT | FL_ALIGN_INSIDE);
    publisherInput = new Fl_Input(95, y, 280, 25);
    
    y += 35;
    Fl_Box* stockLabel = new Fl_Box(10, y, 80, 25, "库存:");
    stockLabel->align(FL_ALIGN_RIGHT | FL_ALIGN_INSIDE);
    stockInput = new Fl_Input(95, y, 280, 25);
    
    y += 35;
    Fl_Box* priceLabel = new Fl_Box(10, y, 80, 25, "价格:");
    priceLabel->align(FL_ALIGN_RIGHT | FL_ALIGN_INSIDE);
    priceInput = new Fl_Input(95, y, 280, 25);
    
    // 操作按钮
    y += 40;
    addButton = new Fl_Button(20, y, 80, 30, "添加图书");
    updateButton = new Fl_Button(110, y, 80, 30, "修改图书");
    deleteButton = new Fl_Button(200, y, 80, 30, "删除图书");
    clearButton = new Fl_Button(290, y, 80, 30, "清空输入");
    
    // 购买功能
    y += 50;
    Fl_Box* purchaseTitle = new Fl_Box(10, y, 380, 30, "图书购买");
    purchaseTitle->labelfont(FL_BOLD);
    purchaseTitle->labelsize(14);
    purchaseTitle->align(FL_ALIGN_CENTER);
    
    y += 35;
    Fl_Box* purchaseIsbnLabel = new Fl_Box(10, y, 80, 25, "ISBN:");
    purchaseIsbnLabel->align(FL_ALIGN_RIGHT | FL_ALIGN_INSIDE);
    purchaseIsbnInput = new Fl_Input(95, y, 200, 25);
    
    y += 35;
    Fl_Box* purchaseQtyLabel = new Fl_Box(10, y, 80, 25, "数量:");
    purchaseQtyLabel->align(FL_ALIGN_RIGHT | FL_ALIGN_INSIDE);
    purchaseQuantityInput = new Fl_Input(95, y, 200, 25);
    
    purchaseButton = new Fl_Button(300, y, 70, 25, "购买");
    
    // 数据操作按钮
    y += 50;
    saveButton = new Fl_Button(20, y, 80, 30, "保存数据");
    loadButton = new Fl_Button(110, y, 80, 30, "加载数据");
    statsButton = new Fl_Button(200, y, 80, 30, "统计信息");
    
    leftPanel->end();
    
    // 右侧面板
    Fl_Group* rightPanel = new Fl_Group(400, 10, 390, 580);
    
    // 查询区域
    Fl_Box* searchTitle = new Fl_Box(400, 10, 390, 30, "图书查询");
    searchTitle->labelfont(FL_BOLD);
    searchTitle->labelsize(14);
    searchTitle->align(FL_ALIGN_CENTER);
    
    searchInput = new Fl_Input(410, 45, 280, 25);
    searchButton = new Fl_Button(695, 45, 80, 25, "查询");
    
    // 图书表格
    bookTable = new BookTable(410, 80, 370, 250, this);
    
    // 结果显示区域
    Fl_Box* resultTitle = new Fl_Box(400, 340, 390, 30, "操作结果");
    resultTitle->labelfont(FL_BOLD);
    resultTitle->labelsize(14);
    resultTitle->align(FL_ALIGN_CENTER);
    
    resultBuffer = new Fl_Text_Buffer();
    resultDisplay = new Fl_Text_Display(410, 375, 370, 200);
    resultDisplay->buffer(resultBuffer);
    
    rightPanel->end();
    
    end();
}

// 设置回调函数
void MainWindow::setupCallbacks() {
    addButton->callback(onAddBook, this);
    updateButton->callback(onUpdateBook, this);
    deleteButton->callback(onDeleteBook, this);
    clearButton->callback(onClearInputs, this);
    searchButton->callback(onSearchBook, this);
    purchaseButton->callback(onPurchaseBook, this);
    statsButton->callback(onShowStats, this);
    saveButton->callback(onSaveData, this);
    loadButton->callback(onLoadData, this);
    
    bookTable->callback(onTableSelect);
    bookTable->when(FL_WHEN_CHANGED);
}

// 更新表格显示
void MainWindow::updateTable() {
    auto& books = bookManager->getAllBooks();
    bookTable->rows(books.size());
    bookTable->redraw();
}

// 清空输入框
void MainWindow::clearInputs() {
    isbnInput->value("");
    titleInput->value("");
    authorInput->value("");
    publisherInput->value("");
    stockInput->value("");
    priceInput->value("");
    searchInput->value("");
    purchaseIsbnInput->value("");
    purchaseQuantityInput->value("");
    selectedISBN = "";
}

// 显示消息
void MainWindow::showMessage(const std::string& message) {
    resultBuffer->text(message.c_str());
}

// 显示错误
void MainWindow::showError(const std::string& message) {
    resultBuffer->text((std::string("错误: ") + message).c_str());
}

// 选择图书
void MainWindow::selectBook(int row) {
    auto& books = bookManager->getAllBooks();
    if (row >= 0 && row < static_cast<int>(books.size())) {
        const Book& book = books[row];
        selectedISBN = book.getISBN();
        
        isbnInput->value(book.getISBN().c_str());
        titleInput->value(book.getTitle().c_str());
        authorInput->value(book.getAuthor().c_str());
        publisherInput->value(book.getPublisher().c_str());
        stockInput->value(std::to_string(book.getStock()).c_str());
        priceInput->value(std::to_string(book.getPrice()).c_str());
    }
}

// 回调函数实现
void MainWindow::onAddBook(Fl_Widget* w, void* data) {
    MainWindow* window = static_cast<MainWindow*>(data);
    window->handleAddBook();
}

void MainWindow::onUpdateBook(Fl_Widget* w, void* data) {
    MainWindow* window = static_cast<MainWindow*>(data);
    window->handleUpdateBook();
}

void MainWindow::onDeleteBook(Fl_Widget* w, void* data) {
    MainWindow* window = static_cast<MainWindow*>(data);
    window->handleDeleteBook();
}

void MainWindow::onClearInputs(Fl_Widget* w, void* data) {
    MainWindow* window = static_cast<MainWindow*>(data);
    window->clearInputs();
    window->showMessage("输入框已清空");
}

void MainWindow::onSearchBook(Fl_Widget* w, void* data) {
    MainWindow* window = static_cast<MainWindow*>(data);
    window->handleSearchBook();
}

void MainWindow::onPurchaseBook(Fl_Widget* w, void* data) {
    MainWindow* window = static_cast<MainWindow*>(data);
    window->handlePurchaseBook();
}

void MainWindow::onShowStats(Fl_Widget* w, void* data) {
    MainWindow* window = static_cast<MainWindow*>(data);
    window->handleStatistics();
}

void MainWindow::onSaveData(Fl_Widget* w, void* data) {
    MainWindow* window = static_cast<MainWindow*>(data);
    window->handleSave();
}

void MainWindow::onLoadData(Fl_Widget* w, void* data) {
    MainWindow* window = static_cast<MainWindow*>(data);
    window->handleLoad();
}

void MainWindow::onTableSelect(Fl_Widget* w, void* data) {
    BookTable* table = static_cast<BookTable*>(w);
    MainWindow* window = static_cast<MainWindow*>(data);
    int row = table->callback_row();
    window->selectBook(row);
}

// 处理添加图书
void MainWindow::handleAddBook() {
    const char* isbn = isbnInput->value();
    const char* title = titleInput->value();
    const char* author = authorInput->value();
    const char* publisher = publisherInput->value();
    const char* stockStr = stockInput->value();
    const char* priceStr = priceInput->value();
    
    // 验证输入
    if (!isbn || !title || !author || !publisher || !stockStr || !priceStr) {
        showError("请填写所有必填字段");
        return;
    }
    
    int stock = std::atoi(stockStr);
    double price = std::atof(priceStr);
    
    if (stock < 0) {
        showError("库存不能为负数");
        return;
    }
    
    if (price < 0) {
        showError("价格不能为负数");
        return;
    }
    
    Book book(title, publisher, isbn, author, stock, price);
    
    if (bookManager->addBook(book)) {
        updateTable();
        clearInputs();
        showMessage("图书添加成功！");
    } else {
        showError("添加失败：ISBN已存在");
    }
}

// 处理查询图书
void MainWindow::handleSearchBook() {
    const char* keyword = searchInput->value();
    if (!keyword || strlen(keyword) == 0) {
        updateTable();
        showMessage("显示所有图书");
        return;
    }
    
    std::string result = "查询结果：\n";
    auto books = bookManager->findByTitle(keyword);
    if (!books.empty()) {
        result += "按书名找到 " + std::to_string(books.size()) + " 本图书\n";
    }
    
    auto booksByAuthor = bookManager->findByAuthor(keyword);
    if (!booksByAuthor.empty()) {
        result += "按作者找到 " + std::to_string(booksByAuthor.size()) + " 本图书\n";
    }
    
    auto booksByPublisher = bookManager->findByPublisher(keyword);
    if (!booksByPublisher.empty()) {
        result += "按出版社找到 " + std::to_string(booksByPublisher.size()) + " 本图书\n";
    }
    
    showMessage(result);
}

// 处理修改图书
void MainWindow::handleUpdateBook() {
    if (selectedISBN.empty()) {
        showError("请先选择要修改的图书");
        return;
    }
    
    const char* isbn = isbnInput->value();
    const char* title = titleInput->value();
    const char* author = authorInput->value();
    const char* publisher = publisherInput->value();
    const char* stockStr = stockInput->value();
    const char* priceStr = priceInput->value();
    
    if (!isbn || !title || !author || !publisher || !stockStr || !priceStr) {
        showError("请填写所有必填字段");
        return;
    }
    
    int stock = std::atoi(stockStr);
    double price = std::atof(priceStr);
    
    if (stock < 0) {
        showError("库存不能为负数");
        return;
    }
    
    if (price < 0) {
        showError("价格不能为负数");
        return;
    }
    
    Book newBook(title, publisher, isbn, author, stock, price);
    
    if (bookManager->updateBook(selectedISBN, newBook)) {
        updateTable();
        clearInputs();
        showMessage("图书信息修改成功！");
    } else {
        showError("修改失败：图书不存在或ISBN冲突");
    }
}

// 处理删除图书
void MainWindow::handleDeleteBook() {
    if (selectedISBN.empty()) {
        showError("请先选择要删除的图书");
        return;
    }
    
    if (fl_ask("确定要删除选中的图书吗？")) {
        if (bookManager->deleteBook(selectedISBN)) {
            updateTable();
            clearInputs();
            showMessage("图书删除成功！");
        } else {
            showError("删除失败：图书不存在");
        }
    }
}

// 处理购买图书
void MainWindow::handlePurchaseBook() {
    const char* isbn = purchaseIsbnInput->value();
    const char* quantityStr = purchaseQuantityInput->value();
    
    if (!isbn || !quantityStr) {
        showError("请填写ISBN和购买数量");
        return;
    }
    
    int quantity = std::atoi(quantityStr);
    if (quantity <= 0) {
        showError("购买数量必须大于0");
        return;
    }
    
    if (saleSys->purchaseBook(isbn, quantity)) {
        updateTable();
        
        double total = saleSys->totalConsume(isbn, quantity);
        std::stringstream ss;
        ss << "购买成功！\nISBN: " << isbn << "\n数量: " << quantity 
           << "\n总价: ¥" << std::fixed << std::setprecision(2) << total;
        showMessage(ss.str());
        
        purchaseIsbnInput->value("");
        purchaseQuantityInput->value("");
    } else {
        showError("购买失败：图书不存在或库存不足");
    }
}

// 处理统计显示
void MainWindow::handleStatistics() {
    std::stringstream ss;
    ss << "=== 图书统计信息 ===\n\n";
    
    ss << "图书种类: " << statsSystem->getTotalBooks() << " 种\n";
    ss << "总库存量: " << statsSystem->getTotalStock() << " 本\n";
    ss << "库存总价值: ¥" << std::fixed << std::setprecision(2) 
       << statsSystem->getTotalValue() << "\n";
    ss << "平均价格: ¥" << std::fixed << std::setprecision(2) 
       << statsSystem->getAveragePrice() << "\n\n";
    
    // 最贵图书
    Book* mostExpensive = statsSystem->getMostExpensiveBook();
    if (mostExpensive) {
        ss << "最贵图书: " << mostExpensive->getTitle() 
           << " (¥" << mostExpensive->getPrice() << ")\n";
    }
    
    // 库存最多图书
    Book* highestStock = statsSystem->getHighestStockBook();
    if (highestStock) {
        ss << "库存最多: " << highestStock->getTitle() 
           << " (" << highestStock->getStock() << " 本)\n";
    }
    
    ss << "\n=== 价格排行榜（前5名）===\n";
    auto sortedByPrice = statsSystem->getBooksSortedByPrice();
    for (size_t i = 0; i < sortedByPrice.size() && i < 5; ++i) {
        Book* book = sortedByPrice[i];
        ss << (i + 1) << ". " << book->getTitle() 
           << " - ¥" << book->getPrice() << "\n";
    }
    
    ss << "\n=== 库存排行榜（前5名）===\n";
    auto sortedByStock = statsSystem->getBooksSortedByStock();
    for (size_t i = 0; i < sortedByStock.size() && i < 5; ++i) {
        Book* book = sortedByStock[i];
        ss << (i + 1) << ". " << book->getTitle() 
           << " - " << book->getStock() << " 本\n";
    }
    
    showMessage(ss.str());
}

// 处理保存数据
void MainWindow::handleSave() {
    if (bookManager->saveFile("../data/books.dat")) {
        showMessage("数据保存成功！\n文件位置: data/books.dat");
    } else {
        showError("数据保存失败！");
    }
}

// 处理加载数据
void MainWindow::handleLoad() {
    if (bookManager->loadFile("../data/books.dat")) {
        updateTable();
        showMessage("数据加载成功！\n共加载 " + 
                   std::to_string(bookManager->getBookAmount()) + " 本图书");
    } else {
        showError("数据加载失败！文件不存在或格式错误");
    }
}

// 显示窗口
void MainWindow::show() {
    updateTable();
    Fl_Window::show();
}
