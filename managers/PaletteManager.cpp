#include "PaletteManager.h"

PaletteManager::PaletteManager() {
    // Инициализируем стандартные цвета для палитры
    palette = {
        Qt::black,
        Qt::white,
        Qt::red,
        Qt::green,
        Qt::blue,
        Qt::yellow,
        Qt::cyan,
        Qt::magenta,
        Qt::gray,
        Qt::darkRed
    };
}

QColor PaletteManager::getColor(int index) const {
    try {
        return palette.at(index);
    } catch (const std::out_of_range& ex) {
        return Qt::black;  // Возвращаем черный, если индекс не найден
    }
}

size_t PaletteManager::getSize() const {
    return palette.size();
}

void PaletteManager::setColor(int index, const QColor& color) {
    if (0 <= index & index < palette.size()) {
        palette[index] = color;
    }
}

std::vector<QColor> PaletteManager::getPalette() const {
    return palette;
}
