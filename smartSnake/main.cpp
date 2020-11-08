#include <QApplication>
#include "gameWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    GameWindow window;

    window.move(960, 0);
    window.show();

    return app.exec();
}
