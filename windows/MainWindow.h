#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QFileDialog>
#include <QMessageBox>

#include "CanvasWidget.h"
#include "ColorPaletteWidget.h"
#include "ToolPanelWidget.h"
#include "PreviewWindow.h"
#include "../managers/PaletteManager.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private:
    PaletteManager *paletteManager;
    CanvasWidget *canvas;
    QMenuBar *menuBar;

    void createMenu();
    void openColorPaletteWidget(Qt::DockWidgetArea placing = Qt::BottomDockWidgetArea);
    void openToolPanelWidget(Qt::DockWidgetArea placing = Qt::LeftDockWidgetArea);
    void openPreviewWindow(Qt::DockWidgetArea placing = Qt::RightDockWidgetArea);

private slots:
    void saveBW();
    void saveColor();
};

#endif // MAINWINDOW_H
