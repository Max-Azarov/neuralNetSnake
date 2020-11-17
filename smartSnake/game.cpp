#include <list>
#include <QPushButton>

#include "game.h"


Game::Game(QMainWindow *parent) :
    QMainWindow{parent}
{

    //snakeWindow = new Snake(false, false, this);
    //m_pSnake->setWindowTitle("Snake");
    //m_pSnake->setToolTip("Snake");
    //m_pSnake->setFixedSize(400,400);

    setupUi(this);

}
