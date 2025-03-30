#include <QDockWidget>
#include <QTextStream>

#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    paletteManager = new PaletteManager();

    canvas = new CanvasWidget(paletteManager, this);
    setCentralWidget(canvas);

    openColorPaletteWidget(Qt::BottomDockWidgetArea);
    openToolPanelWidget(Qt::LeftDockWidgetArea);
    createMenu();

    setWindowTitle("pixie");
    resize(800, 600);
}

void MainWindow::openColorPaletteWidget(Qt::DockWidgetArea placing) {
    // Создаем Dock-окно для палитры
    QDockWidget *paletteDock = new QDockWidget("Палитра", this);
    ColorPaletteWidget *palette = new ColorPaletteWidget(paletteManager, paletteDock);
    paletteDock->setWidget(palette);
    addDockWidget(placing, paletteDock);

    // Подключаем сигнал выбора цвета
    connect(palette, &ColorPaletteWidget::mainColorSelected, [this](int colorIndex) {
        canvas->setMainColor(colorIndex);
    });
    connect(palette, &ColorPaletteWidget::secondaryColorSelected, [this](int colorIndex) {
        canvas->setSecondaryColor(colorIndex);
    });

}

void MainWindow::openToolPanelWidget(Qt::DockWidgetArea placing) {
    // Создаем Dock-окно для инструментов
    QDockWidget *toolDock = new QDockWidget("Инструменты", this);
    ToolPanelWidget *toolPanel = new ToolPanelWidget(toolDock);
    toolDock->setWidget(toolPanel);
    addDockWidget(placing, toolDock);

    // Подключаем сигнал выбора инструмента
    connect(toolPanel, &ToolPanelWidget::toolSelected, [this](DrawMode mode) {
        canvas->setDrawMode(mode);
    });
}

void MainWindow::openPreviewWindow(Qt::DockWidgetArea placing) {
    // Создаем Dock-окно для превью
    QDockWidget *previewDock = new QDockWidget("Превью", this);
    PreviewWindow *previewWindow = new PreviewWindow(previewDock);
    previewDock->setWidget(previewWindow);
    addDockWidget(placing, previewDock);

    // Подключаем сигнал об изенение canvas к preview
    connect(canvas, &CanvasWidget::canvasUpdated, [this, previewWindow](
        const std::vector<std::vector<bool>> &pixelData,
        const std::vector<std::vector<int>> &colorData) {
        
        QString braille = BrailleConverter::convertToBrailleColor(pixelData, colorData, paletteManager, QColor(50, 50, 50));
        previewWindow->updatePreview(braille);
    });
}

void MainWindow::createMenu() {
    // Создаем меню-бар
    menuBar = new QMenuBar(this);
    setMenuBar(menuBar);

    // Создаем меню "Файл"
    QMenu *fileMenu = new QMenu("Файл", this);
    menuBar->addMenu(fileMenu);

    // Создаем подменю "Экспортировать"
    QMenu *exportMenu = new QMenu("экспортировать", this);

    QAction *rawExportMenu = new QAction("сырой текст", this);      // сохранение только Braille
    QAction *colorExportMenu = new QAction("цветной текст", this);  // сохранение вместе с цветом

    exportMenu->addAction(rawExportMenu);
    exportMenu->addAction(colorExportMenu);

    connect(rawExportMenu, &QAction::triggered, this, &MainWindow::saveBW);
    connect(colorExportMenu, &QAction::triggered, this, &MainWindow::saveColor);

    // Добавляем действия в меню "Файл"
    QAction *saveAction = new QAction("Сохранить", this);
    QAction *loadAction = new QAction("Загрузить", this);
    QAction *exitAction = new QAction("Выход", this);

    fileMenu->addMenu(exportMenu);
    fileMenu->addSeparator();
    fileMenu->addAction(saveAction);
    fileMenu->addAction(loadAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    // Подключаем сигналы к слотам
    connect(exitAction, &QAction::triggered, this, &QMainWindow::close);

    // Создаем меню "Окна"
    QMenu *windowsMenu = new QMenu("Окна", this);
    menuBar->addMenu(windowsMenu);

    QAction *colorPaletteMenu = new QAction("палитра", this);   // сохранение только Braille
    QAction *toolPanelMenu = new QAction("инструменты", this);  // сохранение вместе с цветом
    QAction *previewMenu = new QAction("превью", this);         // сохранение вместе с цветом

    windowsMenu->addAction(colorPaletteMenu);
    windowsMenu->addAction(toolPanelMenu);
    windowsMenu->addAction(previewMenu);

    // Подключаем открытие соответствующих окон к слотам
    connect(colorPaletteMenu, &QAction::triggered, this, [this]() { openColorPaletteWidget(); });
    connect(toolPanelMenu, &QAction::triggered, this, [this]() { openToolPanelWidget(); });
    connect(previewMenu, &QAction::triggered, this, [this]() { openPreviewWindow(); });
}

void MainWindow::saveBW() {
    QString fileName = QFileDialog::getSaveFileName(this, "Сохранить в ЧБ", "", "Текстовые файлы (*.txt);;Все файлы (*.*)");
    
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл для записи");
        return;
    }

    QTextStream out(&file);
    out << BrailleConverter::convertToBraille(canvas->pixels);

    file.close();
}

void MainWindow::saveColor() {
    QString fileName = QFileDialog::getSaveFileName(this, "Сохранить в цвете", "", "Текстовые файлы (*.txt);;Все файлы (*.*)");
    
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл для записи");
        return;
    }

    QTextStream out(&file);
    out << BrailleConverter::convertToBrailleColor(canvas->pixels, canvas->colors, paletteManager, QColor(0, 0, 0, 0));

    file.close();
}
