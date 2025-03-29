#ifndef PREVIEWWINDOW_H
#define PREVIEWWINDOW_H

#include <QMap>
#include <QLabel>
#include <QWidget>

#include "../managers/PaletteManager.h"

class PreviewWindow : public QWidget {
    Q_OBJECT

public:
    explicit PreviewWindow(QWidget *parent = nullptr);
    void updatePreview(const QString &text);

private:
    QLabel *label;
};

#endif // PREVIEWWINDOW_H
