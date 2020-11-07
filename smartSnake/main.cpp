#include <QApplication>
#include "snake.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Snake window(true, true);

    window.resize(400, 400);
    window.setWindowTitle("Snake");
    window.setToolTip("Snake");
    window.move(960, 0);
    window.show();

    return app.exec();
}
