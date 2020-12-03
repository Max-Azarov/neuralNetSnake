#include "snake/writeField.h"

WriteField::WriteField(Snake* snake) :
    m_pSnake { snake }
{
}

void WriteField::writeInputData() {
    m_pSnake->getVIn()->clear();
    // Заполняем входной вектор для подачи в нейросеть
    // Пустое поле и стены
    std::vector<std::vector<TYPE_CELL>>& vField = *m_pSnake->getVField(); // Матрица поля игры

    for (size_t x = 0; x < vField.size(); ++x) {
        for (size_t y = 0; y < vField[x].size(); ++y) {
            vField[x][y] = TYPE_CELL::EMPTY;
            if (x == 0 || y == 0 || x == ((size_t)m_pSnake->getNumberOfCellsPerSide() - 1) || y == ((size_t)m_pSnake->getNumberOfCellsPerSide() - 1)) {
                vField[x][y] = TYPE_CELL::WALL;
            }
        }
    }
    //
    for (size_t x = 0; x < vField.size(); ++x) {
        for (size_t y = 0; y < vField[x].size(); ++y) {
            if ( x == (size_t)m_pSnake->getFruitX() && y == (size_t)m_pSnake->getFruitY() ) {
                vField[x][y] = TYPE_CELL::FRUIT;
            }
            else if ( x == (size_t)m_pSnake->getSnakeX()[0] && y == (size_t)m_pSnake->getSnakeY()[0]) {
                vField[x][y] = TYPE_CELL::HEAD;
            }
            else {
                for (int i = 1; i < (int)m_pSnake->getSnakeLength(); ++i) {
                    if (x == (size_t)m_pSnake->getSnakeX()[i] && y == (size_t)m_pSnake->getSnakeY()[i]) {
                        vField[x][y] = TYPE_CELL::BODY;
                        break;
                    }
                }
            }
        }
    }

    // Подаем на входы координаты головы и фрукта
    int xHead = m_pSnake->getSnakeX()[0];
    int yHead = m_pSnake->getSnakeY()[0];
    m_pSnake->getVIn()->push_back(xHead);
    m_pSnake->getVIn()->push_back(yHead);
    m_pSnake->getVIn()->push_back(m_pSnake->getFruitX());
    m_pSnake->getVIn()->push_back(m_pSnake->getFruitY());

    m_pSnake->getVIn()->push_back((int)m_pSnake->getStepFromEating()); // голод

    // Подаем на следующие входы область вокруг головы
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

}

void WriteField::checkBound(int* value, int bound) {
    if (*value < 0) *value = 0;
    if (*value > bound) *value = bound;
}
