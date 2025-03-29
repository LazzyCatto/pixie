#ifndef TOOLPANELWIDGET_H
#define TOOLPANELWIDGET_H

#include <QMap>

#include "special/GridWidget.h"
#include "customButtons/CustomButton.h"
#include "CanvasWidget.h"

class ToolPanelWidget : public GridWidget<CustomButton> {
    Q_OBJECT

public:
    explicit ToolPanelWidget(QWidget *parent = nullptr);

signals:
    void toolSelected(DrawMode);

private:
    QMap<DrawMode, int> modeToButtonIdx;
    CustomButton* selected = nullptr;

    void setupTools();
    void selectTool(DrawMode);
};

#endif // TOOLPANELWIDGET_H
