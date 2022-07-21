#include <QApplication>
#include <QStyleFactory>
#include "../Headers/RD5Window.h"

int main(int argc, char *argv[]) {
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    QApplication app(argc, argv);
    Window::RD5Window window;
    window.show();
    return QApplication::exec();
}
