#include <QApplication>
#include "game/game.h"

#include <QDebug>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Game window;

    int screenWidth = QGuiApplication::primaryScreen()->geometry().width();
    window.move((screenWidth - window.width()) / 2, 0); // Размещаем окно сверху по центру экрана
    window.show();
    return app.exec();
}
