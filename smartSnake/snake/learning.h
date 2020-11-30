#ifndef SNAKETRAINING_H
#define SNAKETRAINING_H

#include "snake/snake.h"

#include <vector>

class Snake;

class Learning {
private:
    Snake* m_pSnake;

    // Вектора, содержащие обучающие выборки
    std::vector<std::vector<int>> m_vInTrainingSet;
    std::vector<std::vector<double>> m_vOutTrainingSet;

private:

    void goodMove();
    void badMove();
    void training();
    void addDataToTrainingSet();


public:
    Learning(Snake* pSnake);

    void learning();
    void readDataToTrainingSet();
    void clearData();
    size_t getNumTrainingSet() const { return m_vInTrainingSet.size(); }
};

#endif // SNAKETRAINING_H
