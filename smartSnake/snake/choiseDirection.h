#ifndef CHOISEDIRECTION_H
#define CHOISEDIRECTION_H

#include <vector>

#include "snake/snake.h"
#include "snake/enums.h"
#include "writeInputData.h"

class LogOut;
class Snake;
class WriteInputDataType_3;

class ChoiseDirection {
protected:
    Snake* m_pSnake;
    size_t m_numOfOutputs;

protected:
    bool checkCollision();

public:
    ChoiseDirection(Snake* pSnake, size_t numOfOutputs);
    virtual ~ChoiseDirection() {}

    size_t getNumOfOutputs() const { return m_numOfOutputs; }

    virtual DIRECTION choise() = 0;
};


class ChoiseDirectionType_1 : public ChoiseDirection
{
    // Ищем максимальную мотивацию и, если она больше своего страха, идем в эту сторону.
    // В противном случае, ищем следующую по значению мотивацию и сравниваем со страхом.
    // Если все мотивации меньше своих страхов, идем туда, где меньше всего страх
    // используется 8 выходов НС
public:
    ChoiseDirectionType_1(Snake* pSnake);

    DIRECTION choise() override;
};

class ChoiseDirectionType_2 : public ChoiseDirection
{
    // Применяется для WriteInputDataType_2
    // Ищем максимальную мотивацию и, если она больше своего страха, идем в эту сторону.
    // В противном случае, ищем следующую по значению мотивацию и сравниваем со страхом.
    // Если все мотивации меньше своих страхов, идем туда, где меньше всего страх
    // Выбор происходит отдельно для каждого из возможных направлений
    // используется 2 выхода НС

private:
    // Делим входной вектор на отдельные векторы по четырем сторонам, формируем 4 отдельных вектора для подачи в НС
    void separateToDirections(std::vector<std::vector<int>>* vDataForDirections);

    // Создает вектора страхов и мотиваций из ответов НС для последующего выбора направления
    void createOutputVector(std::vector<std::vector<int>>* vDataForDirections,
                            std::vector<double>* vMotivation,
                            std::vector<double>* vFear
                            );

    void pushToOutputVector(
            std::vector<double>* vMotivation,
            std::vector<double>* vFear
            );


public:
    ChoiseDirectionType_2(Snake* pSnake);

    DIRECTION choise() override;
};

// class ChoiseDirectionType_3 :
// Змейка может выбрать одно из 4х направлений и оказаться в одной из 4 ситуаций.
// В каждой из 4х ситуаций также образуется выбор из 4х направлений.
// Ищем максимальное значение выхода НС из 4х ситуаций в каждой по 4 значения направлений (подаем 16 ситуаций и действий, выбираем максимальное из 16 значений выходов НС)
// Идем туда, где максимальное значение. Обучаем НС. Входы: текущая ситуация и выбранное действие, Выход: найденное максимальное значение
class ChoiseDirectionType_3 : public ChoiseDirection
{

public:
    ChoiseDirectionType_3(Snake* pSnake);

    DIRECTION choise() override;

private:
    void calcVVOut(const std::vector<std::vector<int>>& vvInNN, std::vector<double>* vvOut); // Инициализируем vvOut путем подачи vvInNN в НС
    int calcIndexDirection(DIRECTION* direction, const std::vector<double>& vvOut); // Находим индекс максимального элемента vvOut и направление, по которому этот индекс расположен
    void writeDataInOut(double OutMaxValue, DIRECTION direction, WriteInputDataType_3* const wID); // инициализируем m_pSnake vIn и vOut для последующего обучения НС

private:


};

#endif // CHOISEDIRECTION_H
