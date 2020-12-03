#ifndef WRITEDATA_H
#define WRITEDATA_H

#include <vector>
#include "snake/snake.h"

class Snake;

class WriteField
{
protected:
    Snake* m_pSnake;
    size_t m_sizeInputData;

protected:
    void checkBound(int* value, int bound);

public:
    WriteField(Snake* snake);
    virtual ~WriteField() {}

    size_t getNumInputData() const { return m_sizeInputData; }

    virtual void writeInputData() = 0;
};

class WriteFieldType_1 : public WriteField {
    // На входы НС подаются координаты головы, координаты фрукта, голод, область 5х5 вокруг головы
    // 30 входов НС
public:
    WriteFieldType_1(Snake* snake) : WriteField(snake) {}

    virtual void writeInputData() override;
};

#endif // WRITEDATA_H
