#include <QFile>

#include "CustomButton.h"
#include <QDebug>

CustomButton::CustomButton(const QString &iconPath, QSize iconSize, QWidget *parent)
    : QPushButton(parent), icon(iconPath), size(iconSize) {
    if (QFile(iconPath).exists()) {
        qDebug() << "Ресурс загружен!";
    } else {
        qDebug() << "Ошибка: ресурс " << iconPath << " не найден!";
    }
        
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setFixedSize(iconSize); // Фиксированный размер кнопки
}

void CustomButton::setSelection(bool state) {
    this->state = state;
}

void CustomButton::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Рисуем кнопку
    painter.setBrush(QColor(110, 110, 110)); // Темный фон
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(rect(), 8, 8);

    // Рисуем иконку
    QRect iconRect(5, 5, width() - 10, height() - 10);
    painter.drawPixmap(iconRect, icon);
}
