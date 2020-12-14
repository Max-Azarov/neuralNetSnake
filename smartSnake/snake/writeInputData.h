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
    // На входы НС подаются координаты головы, координаты фрукта, голод, область размером (sizeOfArea х sizeOfArea) вокруг головы
    //
public:
    WriteInputDataType_1(Snake* snake, int sizeOfArea);

    virtual void writeInputData() override;

private:
    int m_sizeOfArea; // Размер просматриваемой области вокруг головы размером (sizeOfArea х sizeOfArea)
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


// class WriteInputDataType_3. На входы НС подаются: координаты головы, координаты фрукта, голод, область вокруг головы(ситуация). 4 возможных направления для выбора (действия)
// Количество выходов 1. (целевая функция)
// Змейка может выбрать одно из 4х направлений и оказаться в одной из 4 ситуаций.
// В каждой из 4х ситуаций также образуется выбор из 4х направлений.
// Ищем максимальное значение выхода НС из 4х ситуаций в каждой по 4 значения направлений ( выбираем максимальное из 16 значений )
// Идем туда, где максимальное значение. Обучаем НС. Входы: текущая ситуация и выбранное действие, Выход: найденное максимальное значение
class WriteInputDataType_3 : public WriteInputData {

public:
    WriteInputDataType_3(Snake* snake, int sizeOfArea);

    virtual void writeInputData() override;

private:
    int m_sizeOfArea; // Размер просматриваемой области вокруг головы размером (sizeOfArea х sizeOfArea)
};

#endif // WRITEDATA_H
