#include "snake/writeField.h"

WriteField::WriteField(Snake* snake) :
    m_pSnake { snake }
{
}

void WriteField::writeInputData() {
    m_pSnake->m_vIn.clear();
    // Заполняем входной вектор для подачи в нейросеть
    // Пустое поле и стены
    for (size_t x = 0; x < m_pSnake->m_vField.size(); ++x) {
        for (size_t y = 0; y < m_pSnake->m_vField[x].size(); ++y) {
            m_pSnake->m_vField[x][y] = TYPE_CELL::EMPTY;
            if (x == 0 || y == 0 || x == ((size_t)m_pSnake->m_numberOfCellsPerSide - 1) || y == ((size_t)m_pSnake->m_numberOfCellsPerSide - 1)) {
                m_pSnake->m_vField[x][y] = TYPE_CELL::WALL;
            }
        }
    }
    //
    for (size_t x = 0; x < m_pSnake->m_vField.size(); ++x) {
        for (size_t y = 0; y < m_pSnake->m_vField[x].size(); ++y) {
            if ( x == (size_t)m_pSnake->fruitX && y == (size_t)m_pSnake->fruitY ) {
                m_pSnake->m_vField[x][y] = TYPE_CELL::FRUIT;
            }
            else if ( x == (size_t)m_pSnake->snakeX[0] && y == (size_t)m_pSnake->snakeY[0]) {
                m_pSnake->m_vField[x][y] = TYPE_CELL::HEAD;
            }
            else {
                for (int i = 1; i < m_pSnake->m_snakeLength; ++i) {
                    if (x == (size_t)m_pSnake->snakeX[i] && y == (size_t)m_pSnake->snakeY[i]) {
                        m_pSnake->m_vField[x][y] = TYPE_CELL::BODY;
                        break;
                    }
                }
            }
            //m_vIn.push_back(m_vField[x][y]);
        }
    }

    // Подаем на входы координаты головы и фрукта
    int xHead = m_pSnake->snakeX[0];
    int yHead = m_pSnake->snakeY[0];
    m_pSnake->m_vIn.push_back(xHead);
    m_pSnake->m_vIn.push_back(yHead);
    m_pSnake->m_vIn.push_back(m_pSnake->fruitX);
    m_pSnake->m_vIn.push_back(m_pSnake->fruitY);


    // Подаем на следующие входы область вокруг головы
    int sizeSquare = 5; // Размер области зрения змейки 5х5
    int correction = -sizeSquare/2;
    int xG; // глобальные координаты
    int yG; // глобальные координаты
    for (int x = 0; x < sizeSquare; ++x) {
        for (int y = 0; y < sizeSquare; ++y) {
            xG = xHead + correction + x;
            checkBound(&xG, (int)m_pSnake->m_vField.size()-1); // Если вышли за границу, присваиваем значение границы
            yG = yHead + correction + y;
            checkBound(&yG, (int)m_pSnake->m_vField[xG].size()-1); // Если вышли за границу, присваиваем значение границы
            m_pSnake->m_vIn.push_back(m_pSnake->m_vField[xG][yG]);
        }
    }
}

void WriteField::checkBound(int* value, int bound) {
    if (*value < 0) *value = 0;
    if (*value > bound) *value = bound;
}
