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

    // Создаем Dock-окно для инструментов
    QDockWidget *toolDock = new QDockWidget("Инструменты", this);
    toolPanel = new ToolPanelWidget(toolDock);
    toolDock->setWidget(toolPanel);
    addDockWidget(Qt::LeftDockWidgetArea, toolDock);

    // Подключаем сигнал выбора инструмента
    connect(toolPanel, &ToolPanelWidget::toolSelected, [this](DrawMode mode) {
        canvas->setDrawMode(mode);
    });

    // Создаем Dock-окно для превью
    QDockWidget *previewDock = new QDockWidget("Превью", this);
    previewWindow = new PreviewWindow(previewDock);
    previewDock->setWidget(previewWindow);
    addDockWidget(Qt::BottomDockWidgetArea, previewDock);

    // Подключаем сигнал об изенение canvas к preview
    connect(canvas, &CanvasWidget::canvasUpdated, [this](
        const std::vector<std::vector<bool>> &pixelData,
        const std::vector<std::vector<int>> &colorData) {
        
        QString braille = BrailleConverter::convertToBraille(pixelData, colorData, paletteManager);
        previewWindow->updatePreview(braille);
    });

    setWindowTitle("pixie");
    resize(800, 600);
}
