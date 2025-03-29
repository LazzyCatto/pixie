#ifndef PALETTEMANAGER_H
#define PALETTEMANAGER_H

#include <QColor>
#include <vector>

struct NoPaletteManagerError : std::logic_error {
    NoPaletteManagerError() : std::logic_error{"no PaletteManager was found"} {};
};

class PaletteManager {
public:
    PaletteManager();

    // Получить цвет по индексу
    QColor getColor(int index) const;

    // Получить размер палитры
    size_t getSize() const;

    // Установить новый цвет по индексу
    void setColor(int index, const QColor& color);


    // Получить все цвета в палитре
    std::vector<QColor> getPalette() const;

private:
    std::vector<QColor> palette;  // Хранение палитры
};

#endif // PALETTEMANAGER_H
