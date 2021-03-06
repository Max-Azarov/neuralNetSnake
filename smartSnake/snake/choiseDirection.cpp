#include "snake/choiseDirection.h"

#include <QDebug>
#include <QStringList>
#include <algorithm>



ChoiseDirection::ChoiseDirection(Snake* pSnake, size_t numOfOutputs) :
    m_pSnake { pSnake }
  , m_numOfOutputs { numOfOutputs }
{
}


//  ChoiseDirectionType_1 ========================================================================
// Ищем максимальную мотивацию и, если она больше своего страха, идем в эту сторону.
// В противном случае, ищем следующую по значению мотивацию и сравниваем со страхом.
// Если все мотивации меньше своих страхов, идем туда, где меньше всего страх
// используется 8 выходов НС
ChoiseDirectionType_1::ChoiseDirectionType_1(Snake* pSnake) : ChoiseDirection(pSnake, 8)
{
}

DIRECTION ChoiseDirectionType_1::choise() {
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

    return direction;
}

//  ChoiseDirectionType_2 ========================================================================
// Применяется для WriteInputDataType_2
// Ищем максимальную мотивацию и, если она больше своего страха, идем в эту сторону.
// В противном случае, ищем следующую по значению мотивацию и сравниваем со страхом.
// Если все мотивации меньше своих страхов, идем туда, где меньше всего страх
// Выбор происходит отдельно для каждого из возможных направлений
// используется 2 выходфа НС
ChoiseDirectionType_2::ChoiseDirectionType_2(Snake* pSnake) : ChoiseDirection(pSnake, 2)
{
}

DIRECTION ChoiseDirectionType_2::choise()
{
    // Делим входной вектор на отдельные векторы по четырем сторонам, формируем 4 отдельных вектора для подачи в НС
    std::vector<std::vector<int>> vDataForDirections; // Вектор, содержащий данные для подачи в НС отдельно по четырем направлениям
    vDataForDirections.resize(4); // 4 направления

    separateToDirections(&vDataForDirections);
    // <<

    // Подаем данные в нейросеть, ответ записываем в вектора страха и мотивации
    std::vector<double> vMotivation;
    std::vector<double> vFear;
    createOutputVector(&vDataForDirections, &vMotivation, &vFear);

    DIRECTION direction;

    // Ищем максимальную мотивацию и, если она больше своего страха, идем в эту сторону. В противном случае, ищем следующую по значению мотивацию и сравниваем со страхом
    // Если все мотивации меньше своих страхов, идем туда, где меньше всего страх
    qDebug() << vMotivation[0] << vMotivation[1] << vMotivation[2] << vMotivation[3];
    qDebug() << vFear[0] << vFear[1] << vFear[2] << vFear[3];
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

    // Модифицируем вектор vIn, записывая в него только выбранное направление
    m_pSnake->getVIn()->assign(std::begin(vDataForDirections[direction]), std::end(vDataForDirections[direction]));

    // Окончательно подаем в НС выбранное направление
    m_pSnake->getNet()->training().forwardPass(*m_pSnake->getVIn());
    m_pSnake->getNet()->getOut(*m_pSnake->getVOut());


    return direction;
}

void ChoiseDirectionType_2::separateToDirections(std::vector<std::vector<int>>* vDataForDirections)
{
    int bindingDataSize = 5; // Количество обязательных данных, которые должна быть в каждом векторе направления из метода WriteInputDataType_2::writeInputData()

    std::vector<int>& vIn = *m_pSnake->getVIn(); // Вектор, который содержит разделяемые данные
    int baseSize = (int)vIn.size(); // Общий размер разделяемых данных
    int sizeOfDataDirection = (baseSize - bindingDataSize) / 4; // размер данных индивидуально для каждого из четырех направлений

    // Итераторы, с котрых начинаются необходимые в дальнейшем данные собираем в вектор vIt
    std::vector<std::vector<int>::iterator> vItIn;
    auto itUp = std::begin(vIn) + bindingDataSize;
    auto itLeft = itUp + sizeOfDataDirection;
    auto itDown = itLeft + sizeOfDataDirection;
    auto itRight = itDown + sizeOfDataDirection;
    auto itEnd = std::end(vIn);
    vItIn.assign({itUp, itLeft, itDown, itRight, itEnd});
    //

    std::vector<int> base;
    base.assign(std::begin(vIn), itUp); // База из первых обязательных ко всем направлениям данных

    // Наполняем вектор vDataForDirections
    auto vIt = std::begin(vItIn);
    auto it = std::begin(*vDataForDirections);
    for (;
         it != std::end(*vDataForDirections);
         ++it, ++vIt
         )
    {
        (it)->assign(std::begin(base), std::end(base));
        (it)->insert(std::end(*(it)), *vIt, *(vIt+1));
    }
}

void ChoiseDirectionType_2::createOutputVector(
        std::vector<std::vector<int>>* vDataForDirections,
        std::vector<double>* vMotivation,
        std::vector<double>* vFear
        )
{
    for (auto it = std::begin(*vDataForDirections);
         it != std::end(*vDataForDirections);
         ++it
         )
    {
        m_pSnake->getNet()->training().forwardPass(*it);
        pushToOutputVector(vMotivation, vFear);
    }
}

void ChoiseDirectionType_2::pushToOutputVector(
        std::vector<double>* vMotivation,
        std::vector<double>* vFear
        )
{
    std::vector<double> vTemp;
    vTemp.resize(2); // Количество выходов НС

    m_pSnake->getNet()->getOut(vTemp);
    vMotivation->push_back(*vTemp.begin());
    vFear->push_back(*(vTemp.begin() + 1));
}


// class ChoiseDirectionType_3 :
// Змейка может выбрать одно из 4х направлений и оказаться в одной из 4 ситуаций.
// В каждой из 4х ситуаций также образуется выбор из 4х направлений.
// Ищем максимальное значение выхода НС из 4х ситуаций в каждой по 4 значения направлений (подаем 16 ситуаций и действий, выбираем максимальное из 16 значений выходов НС)
// Идем туда, где максимальное значение. Обучаем НС. Входы: текущая ситуация и выбранное действие, Выход: найденное максимальное значение

ChoiseDirectionType_3::ChoiseDirectionType_3(Snake* pSnake) : ChoiseDirection(pSnake, 1)
{
}

DIRECTION ChoiseDirectionType_3::choise() {
    DIRECTION direction;

    // Берем vvInNN из WriteInputDataType_3
    WriteInputDataType_3* wID = dynamic_cast<WriteInputDataType_3*>(m_pSnake->getLearnState()->getWriteInputData());
    if (!wID) LogOut::messageOut("ChoiseDirectionType_3: ошибка при попытке dynamic_cast WriteInputDataType_3");
    std::vector<std::vector<int>>& vvInNN = wID->vvInNN;

    // Создаем vvOut
    std::vector<double> vvOut;

    calcVVOut(vvInNN, &vvOut);
    int indexMax = calcIndexDirection(&direction, vvOut);
    writeDataInOut(vvOut[indexMax], direction, wID);

    return direction;
}

void ChoiseDirectionType_3::calcVVOut(const std::vector<std::vector<int>>& vvInNN, std::vector<double>* vvOut) {

    vvOut->clear(); // предварительно очищаем целевой вектор
    std::vector<double> vTemp;
    // Подаем данные в нейросеть
    for (auto itIn = std::begin(vvInNN); itIn != std::end(vvInNN); ++itIn) {
        m_pSnake->getNet()->training().forwardPass(*itIn); // Подаем данные в нейросеть
        m_pSnake->getNet()->training().getOutValues(&vTemp); // Записываем ответ в vTemp
        vvOut->push_back(*(vTemp.begin())); // Наполняем vvOut значениями начального элемента vTemp, т.к. в НС этого state используется только 1 выход
    }
}

int ChoiseDirectionType_3::calcIndexDirection(DIRECTION* direction, const std::vector<double>& vvOut) {
    int indexMax = std::max_element(std::begin(vvOut), std::end(vvOut)) - std::begin(vvOut); // индекс элемента с максимальным значением
    int numOfDirections = 4;
    *direction = (DIRECTION)(indexMax / numOfDirections); // indexMax 0-3 -> UP, 4-7 -> LEFT, etc.
    return indexMax;
}

void ChoiseDirectionType_3::writeDataInOut(double OutMaxValue, DIRECTION direction, WriteInputDataType_3* const wID) {
    m_pSnake->getVOut()->clear();
    m_pSnake->getVOut()->push_back(OutMaxValue);
    wID->copyData();
    wID->proccesingData(direction, m_pSnake->getVIn());
}

