#include <QApplication>
#include "snake.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Snake window(false, false);

    window.resize(400, 400);
    window.setWindowTitle("Snake");
    window.setToolTip("Snake");
    window.move(960, 0);
    window.show();

    return app.exec();
}
