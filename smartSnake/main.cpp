#include <QApplication>
#include "game.h"

#include <QDebug>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Game window;

    //window.move(960, 0);
    int screenWidth = QApplication::desktop()->screenGeometry().width();
    //int screenHeight = QApplication::desktop()->screenGeometry().height();
    window.move((screenWidth - window.width()) / 2, 0);
    window.show();
    //qDebug() << window.width();
    //qDebug() << window.height();

    return app.exec();
}
