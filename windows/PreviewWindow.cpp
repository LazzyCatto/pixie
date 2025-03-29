#include <QVBoxLayout>
#include <QFontDatabase>
#include <QDebug>

#include "PreviewWindow.h"

PreviewWindow::PreviewWindow(QSize gridSize, QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    label = new QLabel(this);
    label->setAlignment(Qt::AlignCenter);
    label->setTextFormat(Qt::RichText);
    label->setTextInteractionFlags(Qt::TextSelectableByMouse);

    QFont font = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    font.setLetterSpacing(QFont::AbsoluteSpacing, 0);
    label->setFont(font);
    label->setText("<html><body><span style='color: rgb(0, 0, 200z);'>d</span></body></html>");


    layout->addWidget(label);
    setLayout(layout);

    setGridSize(gridSize);
    qDebug() << "Current font:" << label->font().family();
}

PreviewWindow::PreviewWindow(QWidget *parent) : PreviewWindow(QSize(32, 32), parent) {}

void PreviewWindow::updatePreview(const QString &text) {
    label->setText(text);
}

void PreviewWindow::setGridSize(QSize gridSize) {
    setFixedSize(gridSize.width() * kFontScale, gridSize.height() * kFontScale);
}
