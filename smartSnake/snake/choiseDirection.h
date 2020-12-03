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

private:
    bool checkCollision();

public:
    ChoiseDirection(Snake* pSnake);

    virtual DIRECTION choise();
};

class ChoiseDirectionType_1 : public ChoiseDirection {
public:
    ChoiseDirectionType_1(Snake* pSnake);

    DIRECTION choise() override;
};

#endif // CHOISEDIRECTION_H
