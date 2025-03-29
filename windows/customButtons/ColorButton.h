#ifndef COLORBUTTON_H
#define COLORBUTTON_H

#include <QPushButton>
#include <QPainter>
#include <QMouseEvent>

#include "../../managers/PaletteManager.h"

class ColorButton : public QPushButton {
    Q_OBJECT

public:
    explicit ColorButton(QSize buttonSize, int colorIndex, PaletteManager *paletteManager, QWidget *parent = nullptr);
    void setSelectionMain(bool state);
    void setSelectionSecondary(bool state);

signals:
    void leftClicked();
    void rightClicked();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    QSize size;
    bool main = false;
    bool secondary = false;

    int color;
    PaletteManager *paletteManager;
};

#endif // COLORBUTTON_H
