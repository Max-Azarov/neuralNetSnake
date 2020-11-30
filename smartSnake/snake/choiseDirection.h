#ifndef CHOISEDIRECTION_H
#define CHOISEDIRECTION_H

#include <vector>

#include "snake/snake.h"
#include "snake/enums.h"

class LogOut;
class Snake;

class ChoiseDirection {
private:
    Snake* m_pSnake;
    LogOut* m_LogOut;

private:
    bool checkCollision();

public:
    ChoiseDirection(Snake* pSnake);

    DIRECTION choise();
};

#endif // CHOISEDIRECTION_H
