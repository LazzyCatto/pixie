#include <QPainter>
#include <QMouseEvent>

#include "CanvasWidget.h"

CanvasWidget::CanvasWidget(PaletteManager *paletteManager, QWidget *parent)
    : QWidget(parent), paletteManager(paletteManager) {
    setMinimumSize(gridWidth * pixelSize, gridHeight * pixelSize);
    
    // Инициализируем массив белыми пикселями
    pixels.resize(gridWidth, std::vector<bool>(gridHeight, false));
    colors.resize(gridWidth / kBrailleWidth, std::vector<int>(gridHeight, 0));

    setMouseTracking(true); // Мышка будет ослеживаться и без нажатия
}

void CanvasWidget::setMainColor(int colorIndex) {
    mainColorIndex = colorIndex;
}

void CanvasWidget::setSecondaryColor(int colorIndex) {
    secondaryColorIndex = colorIndex;
}

void CanvasWidget::swapColors() {
    std::swap(mainColorIndex, secondaryColorIndex);
}

void CanvasWidget::setPaletteManager(PaletteManager *paletteManager) {
    this->paletteManager = paletteManager;
}

void CanvasWidget::setDrawMode(DrawMode mode) {
    this->mode = mode;
}

void CanvasWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.fillRect(rect(), QColor(50, 50, 50));  // Заливаем фон

    // Устанавливаем масштаб и сдвиг
    painter.translate(offset);
    painter.scale(scaleFactor, scaleFactor);

    // Рисуем закрашенные пиксели
    for (int x = 0; x < gridWidth; ++x) {
        for (int y = 0; y < gridHeight; ++y) {
            painter.fillRect(x * pixelSize, y * pixelSize, pixelSize, pixelSize, getPixelColor(x, y));
        }
    }

    // Рисуем сетку
    painter.setPen(QColor(20, 20, 20));
    for (int x = 0; x <= gridWidth; ++x) {
        painter.drawLine(x * pixelSize, 0, x * pixelSize, gridHeight * pixelSize);
    }
    for (int y = 0; y <= gridHeight; ++y) {
        painter.drawLine(0, y * pixelSize, gridWidth * pixelSize, y * pixelSize);
    }

    // Помечаем зону действия курсора
    if (mode == DrawMode::COLOR) {
        int x = (currentMousePos.x() - offset.x()) / (pixelSize * scaleFactor * kBrailleWidth);
        int y = (currentMousePos.y() - offset.y()) / (pixelSize * scaleFactor * kBrailleHeight);
        if (x >= 0 && x < gridWidth / kBrailleWidth && y >= 0 && y < gridHeight / kBrailleHeight) {
            painter.setBrush(QColor(255, 255, 255, 100));  // Прозрачная подсветка
            painter.setPen(Qt::NoPen);
            painter.drawRect(
                x * pixelSize * kBrailleWidth,
                y * pixelSize * kBrailleHeight,
                pixelSize * kBrailleWidth,
                pixelSize * kBrailleHeight);
        }
    } else {
        int x = (currentMousePos.x() - offset.x()) / (pixelSize * scaleFactor);
        int y = (currentMousePos.y() - offset.y()) / (pixelSize * scaleFactor);
        if (x >= 0 && x < gridWidth && y >= 0 && y < gridHeight) {
            painter.setBrush(QColor(255, 255, 255, 100));  // Прозрачная подсветка
            painter.setPen(Qt::NoPen);
            painter.drawRect(x * pixelSize, y * pixelSize, pixelSize, pixelSize);
        }
    }
}

// Устанавливаем пиксель
void CanvasWidget::setPixelState(int x, int y, bool state) {
    if (x >= 0 && x < gridWidth && y >= 0 && y < gridHeight) {
        pixels[x][y] = state;
        update();  // Перерисовываем виджет
    }
}

// Устанавливаем цвет
void CanvasWidget::setChunkColor(int x, int y, int colorIndex) {
    if (x >= 0 && x < gridWidth / kBrailleWidth && y >= 0 && y < gridHeight / kBrailleHeight) {
        colors[x][y] = colorIndex;
        update();  // Перерисовываем виджет
    }
}

// Получение цвета пикселя
QColor CanvasWidget::getPixelColor(int x, int y) {
    if (!paletteManager) {
        throw NoPaletteManagerError{};
    }
    if (x >= 0 && x < gridWidth && y >= 0 && y < gridHeight) {
        if (pixels[x][y]) {
            int colorIndex = colors[x / kBrailleWidth][y / kBrailleHeight];
            return paletteManager->getColor(colorIndex);
        } else {
            return backgroundColor;
        }
    }
    return backgroundColor;
}

// Обрабатываем нажатие мыши
void CanvasWidget::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::MiddleButton) {
        lastMousePos = event->pos(); // Запоминаем позицию для перемещения
    } else {
        lastMouseState = (event->button() == Qt::LeftButton);
        paint(event);
    }
}

// Обрабатываем движение мыши (чтобы рисовать при движении)
void CanvasWidget::mouseMoveEvent(QMouseEvent *event) {
    currentMousePos = event->pos();
    if (event->buttons() & Qt::MiddleButton) {
        QPoint delta = event->pos() - lastMousePos;
        offset += delta;
        lastMousePos = event->pos();
    } else if (event->buttons()) {
        paint(event);
    }
    update();
}

// Обрабатываем кисти
void CanvasWidget::paint(QMouseEvent *event) {
    if (mode == DrawMode::COLOR) {
        int x = (event->pos().x() - offset.x()) / (pixelSize * scaleFactor * kBrailleWidth);
        int y = (event->pos().y() - offset.y()) / (pixelSize * scaleFactor * kBrailleHeight);

        int color = lastMouseState ? mainColorIndex : secondaryColorIndex;
        setChunkColor(x, y, color);
    } else if (mode == DrawMode::DRAW) {
        int x = (event->pos().x() - offset.x()) / (pixelSize * scaleFactor);
        int y = (event->pos().y() - offset.y()) / (pixelSize * scaleFactor);

        setPixelState(x, y, lastMouseState);
    } else if (mode == DrawMode::ERASE) {
        int x = (event->pos().x() - offset.x()) / (pixelSize * scaleFactor);
        int y = (event->pos().y() - offset.y()) / (pixelSize * scaleFactor);

        setPixelState(x, y, false);
    }
}

void CanvasWidget::wheelEvent(QWheelEvent *event) {
    // Получаем позицию курсора в мировых координатах (до изменения масштаба)
    QPointF cursorBeforeZoom = (event->position() - offset) / scaleFactor;

    // Меняем масштаб
    if (event->angleDelta().y() > 0) {
        scaleFactor = std::min(maxScale, scaleFactor * scaleStep);
    } else {
        scaleFactor = std::max(minScale, scaleFactor / scaleStep);
    }

    // Получаем позицию курсора в новых мировых координатах
    QPointF cursorAfterZoom = (event->position() - offset) / scaleFactor;

    // Смещаем холст так, чтобы курсор оставался на том же месте
    offset += (cursorAfterZoom - cursorBeforeZoom) * scaleFactor;

    update();
}