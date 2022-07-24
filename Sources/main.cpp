#include <QApplication>
#include <QDebug>
#include <QStyleFactory>
#include "../Headers/RD5Window.h"

int main(int argc, char *argv[]) {
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    Window::RD5Window window;
    window.show();
    return QApplication::exec();
}
