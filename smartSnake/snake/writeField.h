#ifndef WRITEDATA_H
#define WRITEDATA_H

#include <vector>
#include "snake/snake.h"

class Snake;

class WriteField
{
private:
    Snake* m_pSnake;

private:
    void checkBound(int* value, int bound);

public:
    WriteField(Snake* snake);
    void writeInputData();

};

#endif // WRITEDATA_H
