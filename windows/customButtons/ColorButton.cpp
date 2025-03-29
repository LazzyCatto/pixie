#include <QFile>

#include "ColorButton.h"

ColorButton::ColorButton(QSize buttonSize, int colorIndex, PaletteManager *paletteManager, QWidget *parent)
    : QPushButton(parent), size(buttonSize), color(colorIndex), paletteManager(paletteManager) {
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setFixedSize(buttonSize); // Фиксированный размер кнопки
}

void ColorButton::setSelectionMain(bool state) {
    main = state;
    update();
}

void ColorButton::setSelectionSecondary(bool state) {
    secondary = state;
    update();
}

void ColorButton::paintEvent(QPaintEvent *event) {
    if (!paletteManager) {
        throw NoPaletteManagerError{};
    }

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Рисуем кнопку
    painter.setBrush(paletteManager->getColor(color));
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(rect(), 8, 8);

    if (main) {
        painter.setBrush(Qt::white);
        painter.setPen(QPen(Qt::gray, 2));
        painter.drawEllipse(QRect(2, 2, 8, 8));
    }

    if (secondary) {
        painter.setBrush(Qt::black);
        painter.setPen(QPen(Qt::gray, 2));
        painter.drawEllipse(QRect(size.width() - 10, size.height() - 10, 8, 8));
    }
}

void ColorButton::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        emit leftClicked();
    } else if (event->button() == Qt::RightButton) {
        emit rightClicked();
    }
    QPushButton::mousePressEvent(event);  // Вызываем базовую реализацию
}
