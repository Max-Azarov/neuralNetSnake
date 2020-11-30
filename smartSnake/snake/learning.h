#ifndef SNAKETRAINING_H
#define SNAKETRAINING_H

#include "snake/snake.h"

class Snake;

class Learning {
private:
    Snake* m_pSnake;

private:

    void goodMove();
    void badMove();
    void training();
    void addDataToTrainingSet();

public:
    Learning(Snake* pSnake);

    void learning();

};

#endif // SNAKETRAINING_H
