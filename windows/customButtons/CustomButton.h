#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H

#include <QPushButton>
#include <QPainter>

class CustomButton : public QPushButton {
    Q_OBJECT

public:
    explicit CustomButton(const QString &iconPath, QSize iconSize, QWidget *parent = nullptr);
    void setSelection(bool state);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    bool state;

    QPixmap icon;
    QSize size;
};

#endif // CUSTOMBUTTON_H
