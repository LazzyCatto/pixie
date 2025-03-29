#ifndef GRIDWIDGET_H
#define GRIDWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QVector>
#include <QPushButton>
#include <QResizeEvent>

template<typename Widget>
class GridWidget : public QWidget {
public:
    explicit GridWidget(int widgetWidth, QWidget *parent = nullptr);

    void addTool(Widget* tool); // Добавить элемент
    void clearTools();           // Очистить сетку

protected:
    void resizeEvent(QResizeEvent *event) override; // Изменение размеров

    int columnCount;          // Количество колонок
    int widgetWidth;          // Ширина элементов
    QGridLayout *gridLayout;  // Сетка с элементами
    QVector<Widget*> tools;   // Список инструментов

    void updateLayout();      // Перестроение сетки
};

template<typename Widget>
GridWidget<Widget>::GridWidget(int widgetWidth, QWidget *parent)
    : QWidget(parent), widgetWidth(widgetWidth) {
    gridLayout = new QGridLayout(this);
    gridLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    setLayout(gridLayout);
    setMinimumSize(widgetWidth, widgetWidth); 
}

template<typename Widget>
void GridWidget<Widget>::addTool(Widget* tool) {
    tools.append(tool);
    updateLayout();
}

template<typename Widget>
void GridWidget<Widget>::clearTools() {
    for (QWidget* tool : tools) {
        gridLayout->removeWidget(tool);
        tool->setParent(nullptr);
    }
    tools.clear();
}

template<typename Widget>
void GridWidget<Widget>::resizeEvent(QResizeEvent *event) {
    int newColumns = (event->size().width() - widgetWidth) / widgetWidth;
    newColumns = std::max(1, newColumns);

    if (newColumns != columnCount) {
        columnCount = newColumns;
        updateLayout();
    }
}

template<typename Widget>
void GridWidget<Widget>::updateLayout() {
    // Очищаем старую сетку
    QLayoutItem *child;
    while ((child = gridLayout->takeAt(0)) != nullptr) {
        delete child;
    }

    // Перестраиваем
    int row = 0, col = 0;
    for (QWidget* tool : tools) {
        gridLayout->addWidget(tool, row, col);
        if (++col >= columnCount) {
            col = 0;
            row++;
        }
    }
}

#endif // GRIDWIDGET_H
