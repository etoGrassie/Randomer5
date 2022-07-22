#include <QApplication>
#include <QDebug>
#include <iostream>
#include "../Headers/RD5Window.h"

int main(int argc, char *argv[]) {
    // QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    app.setStyle("fusion");
    Window::RD5Window window;
    window.show();
    return QApplication::exec();
}
