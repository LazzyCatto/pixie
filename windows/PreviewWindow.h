#ifndef PREVIEWWINDOW_H
#define PREVIEWWINDOW_H

#include <QMap>
#include <QLabel>
#include <QWidget>

#include "../managers/PaletteManager.h"

const int kFontScale = 7;

class PreviewWindow : public QWidget {
    Q_OBJECT

public:
    explicit PreviewWindow(QSize gridSize, QWidget *parent = nullptr);
    explicit PreviewWindow(QWidget *parent = nullptr);
    void updatePreview(const QString &text);
    void setGridSize(QSize gridSize);

private:
    QLabel *label;
};

#endif // PREVIEWWINDOW_H
