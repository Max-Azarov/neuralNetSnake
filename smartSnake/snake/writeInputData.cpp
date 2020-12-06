#include "snake/writeInputData.h"

WriteInputData::WriteInputData(Snake* snake) :
    m_pSnake { snake }
{
}

void WriteInputData::checkBound(int* value, int bound) {
    if (*value < 0) *value = 0;
    if (*value > bound) *value = bound;
}

size_t WriteInputData::getNumInputData() {

    return m_sizeInputData;
}

// WriteFieldType_1 =====================================================
// На входы НС подаются: координаты головы, координаты фрукта, голод, область 5х5 вокруг головы

void WriteInputDataType_1::writeInputData() {

    std::vector<std::vector<TYPE_CELL>>& vField = *m_pSnake->getVField(); // Матрица поля игры
    m_pSnake->getVIn()->clear();

    // Координаты головы змейки
    int xHead = m_pSnake->getSnakeX()[0];
    int yHead = m_pSnake->getSnakeY()[0];

    // Подаем на входы координаты головы и фрукта
    m_pSnake->getVIn()->push_back(xHead);
    m_pSnake->getVIn()->push_back(yHead);
    m_pSnake->getVIn()->push_back(m_pSnake->getFruitX());
    m_pSnake->getVIn()->push_back(m_pSnake->getFruitY());

    // Голод
    m_pSnake->getVIn()->push_back((int)m_pSnake->getStepFromEating());

    // Подаем вокруг головы
    int sizeSquare = 5; // Размер области зрения змейки 5х5
    int correction = -sizeSquare/2;
    int xG; // глобальные координаты
    int yG; // глобальные координаты
    for (int x = 0; x < sizeSquare; ++x) {
        for (int y = 0; y < sizeSquare; ++y) {
            xG = xHead + correction + x;
            checkBound(&xG, (int)vField.size()-1); // Если вышли за границу, присваиваем значение границы
            yG = yHead + correction + y;
            checkBound(&yG, (int)vField[xG].size()-1); // Если вышли за границу, присваиваем значение границы
            m_pSnake->getVIn()->push_back(vField[xG][yG]);
        }
    }

    // Обязательная инициализация поля m_sizeInputData
    m_sizeInputData = m_pSnake->getVIn()->size();
}

// WriteFieldType_2 =====================================================
// На входы НС подаются: голод, координаты головы, координаты фрукта, сектора обозрения на определенную глубину depth
// В первом слое видим три клетки, во втором - пять, в третьем - семь и т.д.
// В вектор входных данных записываем значения по четырем сторонам
// Для выбора направления движения и для обучения в дальнейшем необходимо использовать реализации,
// которые берут данные по четырем сторонам по отдельности
// Количество входов НС в четыре раза меньше, чем сформированные здесь данные, т.к. данные симметричны.
// Также подается голод

WriteInputDataType_2::WriteInputDataType_2(Snake* snake) :
    WriteInputData(snake)
  , m_depth { 2 }  // Дальность зрения depth слоев
{

}

void WriteInputDataType_2::writeInputData() {

    //std::vector<std::vector<TYPE_CELL>>& vField = *m_pSnake->getVField(); // Матрица поля игры
    m_pSnake->getVIn()->clear();

    // Координаты головы змейки
    int xHead = m_pSnake->getSnakeX()[0];
    int yHead = m_pSnake->getSnakeY()[0];

    //int bindingData; // количество входов, которые должны подаваться в каждое направление
    // Голод
    m_pSnake->getVIn()->push_back((int)m_pSnake->getStepFromEating());

    // Подаем на входы координаты головы и фрукта
    m_pSnake->getVIn()->push_back(xHead);
    m_pSnake->getVIn()->push_back(yHead);
    m_pSnake->getVIn()->push_back(m_pSnake->getFruitX());
    m_pSnake->getVIn()->push_back(m_pSnake->getFruitY());

    m_bindingData = (int)m_pSnake->getVIn()->size();

    int minXY;
    int maxXY;

    // Смотрим вверх
    minXY = maxXY = xHead;
    for (int y = yHead - 1; y >= yHead - m_depth; --y) {
        minXY--;
        maxXY++;
        for (int x = minXY; x <= maxXY; ++x) {
            readField(x, y);
        }
    }

    // Смотрим налево
    minXY = maxXY = yHead;
    for (int x = xHead - 1; x >= xHead - m_depth; --x) {
        minXY--;
        maxXY++;
        for (int y = maxXY; y >= minXY; --y) {
            readField(x, y);
        }
    }

    // Смотрим вниз
    minXY = maxXY = xHead;
    for (int y = yHead + 1; y <= yHead + m_depth; ++y) {
        minXY--;
        maxXY++;
        for (int x = maxXY; x >= minXY; --x) {
            readField(x, y);
        }
    }

    // Смотрим вправо
    minXY = maxXY = yHead;
    for (int x = xHead + 1; x <= xHead + m_depth; ++x) {
        minXY--;
        maxXY++;
        for (int y = minXY; y <= maxXY; ++y) {
            readField(x, y);
        }
    }

    // Обязательная инициализация поля m_sizeInputData
    m_sizeInputData = m_bindingData + (m_pSnake->getVIn()->size() - m_bindingData) / 4;
}

void WriteInputDataType_2::readField(int x, int y) {
    std::vector<std::vector<TYPE_CELL>>& vField = *m_pSnake->getVField(); // Матрица поля игры
    checkBound(&x, (int)vField.size()-1); // Если вышли за границу, присваиваем значение границы
    checkBound(&y, (int)vField[x].size()-1); // Если вышли за границу, присваиваем значение границы
    m_pSnake->getVIn()->push_back(vField[x][y]);
}
