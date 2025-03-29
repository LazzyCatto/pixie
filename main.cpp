#include <QApplication>
#include <QMainWindow>

#include "windows/MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Устанавливаем темную палитру для всего приложения
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(100, 100, 100));         // Фон окна
    darkPalette.setColor(QPalette::WindowText, Qt::white);                 // Цвет текста
    darkPalette.setColor(QPalette::Base, QColor(70, 70, 70));              // Фон ввода текста
    darkPalette.setColor(QPalette::AlternateBase, QColor(150, 150, 150));  // Альтернативный фон
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);                // Цвет подсказок
    darkPalette.setColor(QPalette::ToolTipText, Qt::black);                // Текст подсказок
    darkPalette.setColor(QPalette::Text, Qt::white);                       // Текст
    darkPalette.setColor(QPalette::Button, QColor(100, 100, 100));         // Цвет кнопок
    darkPalette.setColor(QPalette::ButtonText, Qt::white);                 // Цвет текста на кнопках
    darkPalette.setColor(QPalette::BrightText, Qt::red);                   // Текст с ярким цветом
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));            // Цвет ссылок

    // Применяем палитру
    app.setPalette(darkPalette);

    MainWindow window;
    window.show();

    return app.exec();
}
