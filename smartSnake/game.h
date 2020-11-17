#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QtWidgets>
#include "snake.h"
#include "ui_mainWindow.h"

class Game : public QMainWindow, public Ui::MainWindow
{
private:

    Q_OBJECT
public:
    Game(QMainWindow *parent = nullptr);
    virtual ~Game() { delete snakeWindow; }
};

#endif // GAMEWINDOW_H
