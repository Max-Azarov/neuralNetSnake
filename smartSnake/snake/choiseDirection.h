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

#endif // CHOISEDIRECTION_H
