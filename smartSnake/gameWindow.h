#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QtWidgets>

class GameWindow : public QWidget
{
    Q_OBJECT
public:
    GameWindow(QWidget *parent = nullptr);
    virtual ~GameWindow() {}
};

#endif // GAMEWINDOW_H
