#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QtWidgets>
#include "snake.h"
#include "ui_mainWindow.h"

class Game : public QMainWindow
{
private:
    Ui::MainWindow* ui;
    Snake* snake;

    Q_OBJECT
public:
    Game(QWidget *parent = nullptr);
    virtual ~Game() { delete ui; }

public slots:
    void on_sldSnakeSpeed_valueChanged(int);
    void on_sldSnakeSpeed_sliderReleased();
    //void on_sldSnakeSpeed_sliderPressed();

    void on_leSnakeSpeed_returnPressed();
    void on_cbSnakeSpeed_stateChanged(int state);

private:
    void setSnakeSpeed(int);
};

#endif // GAMEWINDOW_H
