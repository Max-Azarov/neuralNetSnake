#ifndef CHOISEDIRECTION_H
#define CHOISEDIRECTION_H

#include <vector>

#include "snake/snake.h"
#include "snake/enums.h"

class LogOut;
class Snake;

class ChoiseDirection {
protected:
    Snake* m_pSnake;

protected:
    bool checkCollision();

public:
    ChoiseDirection(Snake* pSnake);
    virtual ~ChoiseDirection() {}

    virtual DIRECTION choise() = 0;
};


class ChoiseDirectionType_1 : public ChoiseDirection {
public:
    ChoiseDirectionType_1(Snake* pSnake);

    DIRECTION choise() override;
};

#endif // CHOISEDIRECTION_H
