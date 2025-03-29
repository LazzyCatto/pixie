#include <QDockWidget>

#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    paletteManager = new PaletteManager();

    canvas = new CanvasWidget(paletteManager, this);
    setCentralWidget(canvas);

    // Создаем Dock-окно для палитры
    QDockWidget *paletteDock = new QDockWidget("Палитра", this);
    palette = new ColorPaletteWidget(paletteManager, paletteDock);
    paletteDock->setWidget(palette);
    addDockWidget(Qt::RightDockWidgetArea, paletteDock);

    // Подключаем сигнал выбора цвета
    connect(palette, &ColorPaletteWidget::mainColorSelected, [this](int colorIndex) {
        canvas->setMainColor(colorIndex);
    });
    connect(palette, &ColorPaletteWidget::secondaryColorSelected, [this](int colorIndex) {
        canvas->setSecondaryColor(colorIndex);
    });

    QDockWidget *toolDock = new QDockWidget(this);
    toolPanel = new ToolPanelWidget(toolDock);
    toolDock->setWidget(toolPanel);
    addDockWidget(Qt::LeftDockWidgetArea, toolDock);

    // Подключаем сигнал выбора инструмента
    connect(toolPanel, &ToolPanelWidget::toolSelected, [this](DrawMode mode) {
        canvas->setDrawMode(mode);
    });

    setWindowTitle("pixie");
    resize(800, 600);
}
