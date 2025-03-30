#ifndef COLORPALETTEWIDGET_H
#define COLORPALETTEWIDGET_H

#include <QWidget>
#include <QColor>

#include "../managers/PaletteManager.h"
#include "customButtons/ColorButton.h"
#include "special/GridWidget.h"

class ColorPaletteWidget : public GridWidget<ColorButton> {
    Q_OBJECT

public:
    explicit ColorPaletteWidget(PaletteManager *paletteManager, QWidget *parent = nullptr);
    int selectedMainColor() const;
    int selectedSecondaryColor() const;
    void setPaletteManager(PaletteManager *paletteManager);
    void updatePalette();

signals:
    void mainColorSelected(int colorIndex);
    void secondaryColorSelected(int colorIndex);

private:
    int mainColorIndex = 0;       // Выбранный индекс главного цвета
    int secondaryColorIndex = 0;  // Выбранный индекс второго цвета

    PaletteManager *paletteManager;

    void selectMainColor(int colorIndex);
    void selectSecondaryColor(int colorIndex);
};

#endif // COLORPALETTEWIDGET_H
