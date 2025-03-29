#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

#include "ColorPaletteWidget.h"

ColorPaletteWidget::ColorPaletteWidget(PaletteManager *paletteManager, QWidget *parent)
    : GridWidget(32, parent), paletteManager(paletteManager) {
    // setFixedSize(200, 200); // Размер окна палитры
    updatePalette();
}

int ColorPaletteWidget::selectedMainColor() const {
    return mainColorIndex;
}

int ColorPaletteWidget::selectedSecondaryColor() const {
    return secondaryColorIndex;
}

void ColorPaletteWidget::setPaletteManager(PaletteManager *paletteManager) {
    this->paletteManager = paletteManager;
}

void ColorPaletteWidget::updatePalette() {
    if (!paletteManager) {
        throw NoPaletteManagerError{};
    }

    size_t color_count = paletteManager->getSize();
    for (size_t i = 0; i < color_count; ++i) {
        ColorButton *color = new ColorButton(QSize(32, 32), i, paletteManager, this);
        connect(color, &ColorButton::leftClicked, [this, i]() {
            qDebug() << "selected " << i << " as a main color";
            selectMainColor(i);
        });
        connect(color, &ColorButton::rightClicked, [this, i]() {
            qDebug() << "selected " << i << " as a secondary color";
            selectSecondaryColor(i);
        });
        addTool(color);
    }
}

void ColorPaletteWidget::selectMainColor(int colorIndex) {
    tools[mainColorIndex]->setSelectionMain(false);
    tools[colorIndex]->setSelectionMain(true);
    mainColorIndex = colorIndex;
    emit mainColorSelected(colorIndex);
}

void ColorPaletteWidget::selectSecondaryColor(int colorIndex) {
    tools[secondaryColorIndex]->setSelectionSecondary(false);
    tools[colorIndex]->setSelectionSecondary(true);
    secondaryColorIndex = colorIndex;
    emit secondaryColorSelected(colorIndex);
}
