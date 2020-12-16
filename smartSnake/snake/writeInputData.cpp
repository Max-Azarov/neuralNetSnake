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
// На входы НС подаются: координаты головы, координаты фрукта, голод, область вокруг головы

WriteInputDataType_1::WriteInputDataType_1(Snake* snake, int sizeOfArea) :
    WriteInputData(snake)
  , m_sizeOfArea { sizeOfArea }
{}

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
    // m_SizeArea; // Размер области зрения змейки 5х5 вокруг головы
    int correction = -m_sizeOfArea/2; // корректировка для вычисления локальных координат
    int xG; // глобальные координаты
    int yG; // глобальные координаты
    for (int x = 0; x < m_sizeOfArea; ++x) {
        for (int y = 0; y < m_sizeOfArea; ++y) {
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

WriteInputDataType_2::WriteInputDataType_2(Snake* snake, int depth) :
    WriteInputData(snake)
  , m_depth { depth }  // Дальность зрения depth слоев
{

}

void WriteInputDataType_2:: writeInputData() {

    m_pSnake->getVIn()->clear();

    // Координаты головы змейки
    int xHead = m_pSnake->getSnakeX()[0];
    int yHead = m_pSnake->getSnakeY()[0];

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

// WriteFieldType_3 =====================================================
// На входы НС подаются: координаты головы, координаты фрукта, голод, область вокруг головы(ситуация). 4 возможных направления для выбора (действия)
// Количество выходов 1.

WriteInputDataType_3::WriteInputDataType_3(Snake* snake, int sizeOfArea) :
    WriteInputData(snake)
  , m_sizeOfArea { sizeOfArea }
{}

void WriteInputDataType_3::writeInputData() {
    vvInNN.clear();
    std::vector<int> data; // для промежуточных вычислений
    size_t numDirections = 4; // Количество направлений
    for (size_t i = 0; i < numDirections; ++i) {
        copyData();
        DIRECTION directionMove = (DIRECTION)i;
        moveSnake(directionMove);
        readData();
        for (size_t j = 0; j < numDirections; ++j) {
            DIRECTION directionAdd = (DIRECTION)j;
            proccesingData(directionAdd, &data); // Заполняем вектор data
            vvInNN.push_back(data);
        }
    }
}

void WriteInputDataType_3::copyData() {
    // Создаем копию вектора поля
    m_vField.clear();
    size_t vSize = m_pSnake->getVField()->size();
    m_vField.resize(vSize);
    for (size_t i = 0; i < vSize; ++i) {
        m_vField.at(i) = m_pSnake->getVField()->at(i);
    }
    // << Создаем копию вектора поля

    m_pSnake->copySnake(m_snakeX, m_snakeY, &m_snakeLength);
    m_fruitX = m_pSnake->getFruitX();
    m_fruitY = m_pSnake->getFruitY();
}

void WriteInputDataType_3::moveSnake(DIRECTION direction) {
    for (int i = m_snakeLength - 1; i > 0; --i) {
        m_snakeX[i] = m_snakeX[i-1];
        m_snakeY[i] = m_snakeY[i-1];
    }

    if (direction == UP)    m_snakeY[0]--;
    if (direction == DOWN)  m_snakeY[0]++;
    if (direction == LEFT)  m_snakeX[0]--;
    if (direction == RIGHT) m_snakeX[0]++;
}

void WriteInputDataType_3::readData() {

    // Пустые поля и стены
    for (size_t x = 0; x < m_vField.size(); ++x) {
        for (size_t y = 0; y < m_vField[x].size(); ++y) {
            m_vField[x][y] = TYPE_CELL::EMPTY;
            if (   x == 0
                || y == 0
                || x == (m_vField.size() - 1)
                || y == (m_vField[x].size() - 1)
                 )
            {
                m_vField[x][y] = TYPE_CELL::WALL;
            }
        }
    }
    // Фрукт и змейка ( если положение змейки и фрукта совпадает, фрукт пропадает)
    for (size_t x = 0; x < m_vField.size(); ++x) {
        for (size_t y = 0; y < m_vField[x].size(); ++y) {
            if (
                x == (size_t)m_fruitX
                && y == (size_t)m_fruitY
                )
            {
                m_vField[x][y] = TYPE_CELL::FRUIT;
            }
            if (
                x == (size_t)m_snakeX[0]
                && y == (size_t)m_snakeY[0]
                )
            {
                m_vField[x][y] = TYPE_CELL::HEAD;
            }
            else {
                for (int i = 1; i < m_snakeLength; ++i) {
                    if (
                        x == (size_t)m_snakeX[i]
                        && y == (size_t)m_snakeY[i]
                        )
                    {
                        m_vField[x][y] = TYPE_CELL::BODY;
                        break;
                    }
                }
            }
        }
    }
}

void WriteInputDataType_3::proccesingData(DIRECTION direction, std::vector<int>* data) {
    data->clear(); // очищаем целевой вектор
    // Голод
    //data->push_back((int)m_pSnake->getStepFromEating());

    // Подаем на входы координаты головы и фрукта
    data->push_back(m_snakeX[0]);
    data->push_back(m_snakeY[0]);
    data->push_back(m_fruitX);
    data->push_back(m_fruitY);

    // Подаем область вокруг головы
    // m_SizeArea; Размер области зрения змейки m_SizeArea x m_SizeArea вокруг головы
    int correction = -m_sizeOfArea/2; // корректировка для вычисления локальных координат
    int xG; // глобальные координаты
    int yG; // глобальные координаты
    for (int x = 0; x < m_sizeOfArea; ++x) {
        for (int y = 0; y < m_sizeOfArea; ++y) {
            xG = m_snakeX[0] + correction + x;
            checkBound(&xG, (int)m_vField.size()-1); // Если вышли за границу, присваиваем значение границы
            yG = m_snakeY[0] + correction + y;
            checkBound(&yG, (int)m_vField[xG].size()-1); // Если вышли за границу, присваиваем значение границы
            //if (m_vField[xG][yG] != TYPE_CELL::HEAD) {
            data->push_back(m_vField[xG][yG]);
            //}
        }
    }

    // Добавляем вектор направления
    int vDirection[4] = {}; // Инициализируем все элементы массива значением 0
    if (direction == UP)    vDirection[0] = 1;
    if (direction == LEFT)  vDirection[1] = 1;
    if (direction == DOWN)  vDirection[2] = 1;
    if (direction == RIGHT) vDirection[3] = 1;
    for ( auto it = std::begin(vDirection); it != std::end(vDirection); ++it) {
        data->push_back(*it);
    }

    // Обязательная инициализация поля m_sizeInputData
    m_sizeInputData = data->size();
}
