#include "snake/writeField.h"

WriteField::WriteField(Snake* snake) :
    m_pSnake { snake }
{
}

void WriteField::checkBound(int* value, int bound) {
    if (*value < 0) *value = 0;
    if (*value > bound) *value = bound;
}

// WriteFieldType_1 =====================================================
// На входы НС подаются: координаты головы, координаты фрукта, голод, область 5х5 вокруг головы
void WriteFieldType_1::writeInputData() {
    std::vector<std::vector<TYPE_CELL>>& vField = *m_pSnake->getVField(); // Матрица поля игры

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
    m_sizeInputData = m_pSnake->getVIn()->size();
}
