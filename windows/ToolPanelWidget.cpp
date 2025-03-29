#include <QDebug>

#include "ToolPanelWidget.h"

ToolPanelWidget::ToolPanelWidget(QWidget *parent)
    : GridWidget(32, parent) {
    setupTools();
}

void ToolPanelWidget::setupTools() {
    CustomButton *drawTool = new CustomButton(":/icons/draw_tool.png", QSize(32, 32), this);
    CustomButton *eraseTool = new CustomButton(":/icons/erase_tool.png", QSize(32, 32), this);
    CustomButton *colorTool = new CustomButton(":/icons/color_tool.png", QSize(32, 32), this);

    connect(drawTool, &CustomButton::clicked, [this]() {
        qDebug() << "draw tool selected";
        selectTool(DrawMode::DRAW);
    });
    connect(eraseTool, &CustomButton::clicked, [this]() {
        qDebug() << "erase tool selected";
        selectTool(DrawMode::ERASE);
    });
    connect(colorTool, &CustomButton::clicked, [this]() {
        qDebug() << "color tool selected";
        selectTool(DrawMode::COLOR);
    });

    modeToButtonIdx[DrawMode::DRAW] = 0;
    modeToButtonIdx[DrawMode::ERASE] = 1;
    modeToButtonIdx[DrawMode::COLOR] = 2;

    addTool(drawTool);
    addTool(eraseTool);
    addTool(colorTool);
}

void ToolPanelWidget::selectTool(DrawMode mode) {
    if (selected) {
        selected->setSelection(false);
    }
    selected = tools[modeToButtonIdx[mode]];
    selected->setSelection(true);
    emit toolSelected(mode);
}
