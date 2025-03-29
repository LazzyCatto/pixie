#include <QMainWindow>

#include "CanvasWidget.h"
#include "ColorPaletteWidget.h"
#include "ToolPanelWidget.h"
#include "../managers/PaletteManager.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private:
    PaletteManager *paletteManager;
    CanvasWidget *canvas;
    ColorPaletteWidget *palette;
    ToolPanelWidget *toolPanel;
};
