#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H

#include <QWidget>
#include <vector>

#include "../managers/PaletteManager.h"

const int kBrailleWidth = 2;
const int kBrailleHeight = 4;

enum class DrawMode {
    DRAW, ERASE, COLOR
};

class CanvasWidget : public QWidget {
    Q_OBJECT

public:
    explicit CanvasWidget(PaletteManager *paletteManager, QWidget *parent = nullptr);
    void setMainColor(int colorIndex);
    void setSecondaryColor(int colorIndex);
    void swapColors();
    void setPaletteManager(PaletteManager *paletteManager);
    void setDrawMode(DrawMode mode);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private:
    int pixelSize = 10;  // Размер одного пикселя
    int gridWidth = 32;  // Количество пикселей в ширину
    int gridHeight = 32; // Количество пикселей в высоту
    QColor backgroundColor = QColor(30, 30, 30);

    float scaleFactor = 1.0f; // Коэффициент масштабирования
    float scaleStep = 1.2f;   // Скорость приближения
    float minScale = 0.1f;
    float maxScale = 10;
    QPointF offset = {0, 0};  // Смещение холста

    QPoint lastMousePos;    // Последняя позиция мыши (для перемещения)
    QPoint currentMousePos; // Позиция мышки (для подсвечивания текущей клетки)
    bool lastMouseState;    // true - левая кнопка мыши, false - правая

    std::vector<std::vector<bool>> pixels;  // Массив цветов пикселей
    std::vector<std::vector<int>> colors;  // Массив индексов цветов пикселей

    DrawMode mode = DrawMode::DRAW;  // Кисть

    int mainColorIndex;  // Индекс текущего главного цвета
    int secondaryColorIndex; // Индекс текущего второго цвета
    PaletteManager *paletteManager = nullptr;  // Менеджер палитры

    void paint(QMouseEvent *event);
    void setPixelState(int x, int y, bool state);
    void setChunkColor(int x, int y, int colorIndex);
    QColor getPixelColor(int x, int y);
};

#endif // CANVASWIDGET_H
