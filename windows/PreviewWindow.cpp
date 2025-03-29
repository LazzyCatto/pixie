#include <QVBoxLayout>

#include "PreviewWindow.h"

PreviewWindow::PreviewWindow(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    label = new QLabel(this);
    label->setAlignment(Qt::AlignCenter);
    label->setFont(QFont("Monospace", 12));

    layout->addWidget(label);
    setLayout(layout);
}

void PreviewWindow::updatePreview(const QString &text) {
    label->setText(text);
}
