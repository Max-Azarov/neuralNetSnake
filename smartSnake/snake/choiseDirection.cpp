#include "snake/choiseDirection.h"

#include <QDebug>
#include <QStringList>

ChoiseDirection::ChoiseDirection(Snake* pSnake) :
    m_pSnake { pSnake }
{
}

DIRECTION ChoiseDirection::choise() {
    // Подаем данные в нейросеть, ответ записываем в вектор
    m_pSnake->getNet()->training().forwardPass(*m_pSnake->getVIn());
    m_pSnake->getNet()->getOut(*m_pSnake->getVOut());
    DIRECTION direction;

    // Ищем максимальную мотивацию и, если она больше своего страха, идем в эту сторону. В противном случае, ищем следующую по значению мотивацию и сравниваем со страхом
    // Если все мотивации меньше своих страхов, идем туда, где меньше всего страх
    std::vector<double> vMotivation;
    std::vector<double> vFear;
    auto itMedian = std::begin(*m_pSnake->getVOut()) + m_pSnake->getVOut()->size() / 2;
    vMotivation.assign(std::begin(*m_pSnake->getVOut()), itMedian);
    vFear.assign(itMedian, std::end(*m_pSnake->getVOut()));

    while(true) {
        size_t maxMotivation = std::max_element(std::begin(vMotivation), std::end(vMotivation)) - std::begin(vMotivation); // индекс максимального элемента
        if (vMotivation[maxMotivation] == -1.0) {
            size_t minFear = std::min_element(std::begin(vFear), std::end(vFear)) - std::begin(vFear); // индекс минимального элемента
            direction = (DIRECTION)minFear;
            break;
        }
        if (vMotivation[maxMotivation] > vFear[maxMotivation]) {
            direction = (DIRECTION)maxMotivation;
            break;
        }
        else {
            vMotivation[maxMotivation] = -1.0;
        }
    }

    QStringList debug;
    debug << QString::number(m_pSnake->getStepCount()) <<
                (direction == UP ? "UP   " :
                direction == DOWN ? "DOWN " :
                direction == LEFT ? "LEFT " : "RIGHT");

    for (auto it = std::begin(*m_pSnake->getVOut()); it != std::end(*m_pSnake->getVOut()); ++it) {
        debug << QString::number(*it, 'f', 3);
    }

    LogOut::messageOut(debug.join(' '));

    return direction;
}
