#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QtWidgets>
#include "snake.h"

class GameWindow : public QWidget
{
private:
    Snake* m_pSnake;

    Q_OBJECT
public:
    GameWindow(QWidget *parent = nullptr);
    virtual ~GameWindow() { delete m_pSnake; }
};

#endif // GAMEWINDOW_H
