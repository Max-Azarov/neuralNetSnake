#ifndef WRITEDATA_H
#define WRITEDATA_H

#include <vector>
#include "snake/snake.h"

class Snake;

class WriteInputData
{
protected:
    Snake* m_pSnake;
    size_t m_sizeInputData;

protected:
    void checkBound(int* value, int bound);

public:
    WriteInputData(Snake* snake);
    virtual ~WriteInputData() {}

    size_t getNumInputData();

    virtual void writeInputData() = 0;
};

class WriteInputDataType_1 : public WriteInputData {
    // На входы НС подаются координаты головы, координаты фрукта, голод, область 5х5 вокруг головы
    // 30 входов НС
public:
    WriteInputDataType_1(Snake* snake, int sizeOfArea);// : WriteInputData(snake) {}

    virtual void writeInputData() override;

private:
    int m_sizeOfArea;
};

class WriteInputDataType_2 : public WriteInputData {
    // На входы НС подается сектор обозрения в одну из сторон, координаты головы, координаты фрукта, голод
private:
    int m_bindingData; // количество входов, которые должны подаваться в каждое направление
    int m_depth; // Дальность зрения depth слоев

private:
    void readField(int x, int y);

public:
    WriteInputDataType_2(Snake* snake, int depth);

    int getBindingData() const { return m_bindingData; }

    virtual void writeInputData() override;
};

#endif // WRITEDATA_H
