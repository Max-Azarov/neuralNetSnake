#include "snake.h"
#include <QTimer>
#include <QtCore>
#include <QKeyEvent>
#include <QPainter>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <fstream>
#include <sstream>

#include <QApplication>

Snake::~Snake() {
    if (neuroNet) delete neuroNet;
}

Snake::Snake(QWidget *parent) : QWidget{parent}
    , m_delay { 100 }
    , m_loopMotion { false }
    , m_acceptError { 0.1 }
    , m_countOfStepsToNextTest { 1000 }
    , m_setCount { 0 }
    , m_bMutex { false }
  , m_bStop { true }
  , neuroNet { nullptr }
{
    static bool startRandom = false;
    if (!startRandom) {
        srand(static_cast<unsigned int>(time(nullptr)));
        startRandom = true;
    }

    setAutoFillBackground(true);
    // Делаем черный фон
    slotBlackBackground();

    loadTextures();
    m_numberOfCellsPerSide = static_cast<int>(sqrt(NUM_CELLS));
    m_cellSize = WIDTH / m_numberOfCellsPerSide;
    //Cоздаем вектор поля.
    m_vField.resize(static_cast<unsigned int>(m_numberOfCellsPerSide));
    for (unsigned int i = 0; i < m_vField.size(); ++i) {
        m_vField[i].resize(static_cast<unsigned int>(m_numberOfCellsPerSide));
    }

    m_inputData = "input.txt";
    m_outputDataIdeal = "outputIdeal.txt";

    m_vInTrainingSet.clear();
    m_vOutTrainingSet.clear();
    readDataToTrainingSet();

    averageNumberOfSteps(true);

    initGame();
    pTimer = new QTimer(this);
    connect(pTimer, SIGNAL(timeout()), SLOT(slotLoop()));
}

void Snake::setDelay(size_t delay) {
    m_delay = delay;
    pTimer->stop();
    pTimer->start((int)m_delay);
}

void Snake::stop() {
    pTimer->stop();
    m_bStop = true;
}

void Snake::start(bool freedom) {
    setDelay(m_delay);
    m_bStop = false;
    m_freedom = freedom;
    slotLoop();
}

// Основной цикл игры
void Snake::slotLoop() {
    if ( !m_bMutex ) {
        m_bMutex = true;
        movement(); // Передвижение с проверкой будующего столкновения
        isTheFruitEaten(); // съела фрукт
        //isSnakeLooped(); // Зациклилась
        isHopelessSituation(); // Попала в ловушку
        //effects();
        if (!m_freedom) learning(); // учится
        processingSnakeEvents();
        m_bMutex = false;
    }
    update();
}

void Snake::initGame() {
    //m_firstMove = true;
    m_stepCount = 0;
    m_stepFromEating = 0;
    m_isTheFruitEaten = false;
    m_collision = false;
    m_loopMotion = false;
    m_isHopelessSituation = false;

    m_snakeLength = 3;

    initiallyPositionSnake();
    locateFruit();
}

void Snake::locateFruit() {
    int random;
    bool emptyCell = true;
    int temp = (m_numberOfCellsPerSide-2)*(m_numberOfCellsPerSide-2)
            - m_snakeLength - 1; // 2-толщина 2х стенок; 1-клетка, где лежит фрукт
    if ( temp == 0 ) {
        random = 0;
    }
    else random = rand() % temp;
    int count = 0;
    for (int x = 1; x < (m_numberOfCellsPerSide - 1); ++x) { // -1 толщина стенки
        for (int y = 1; y < (m_numberOfCellsPerSide - 1); ++y) { // -1 толщина стенки
            for (int i = 0; i < m_snakeLength; ++i) {
                if (x == snakeX[i] && y == snakeY[i]) {
                    emptyCell = false;
                    break;
                }
            }
            if (x == fruitX && y == fruitY) emptyCell = false;
            if (emptyCell) {
                if (count == random) {
                    fruitX = x;
                    fruitY = y;
                    //================== Принудительная установка фрукта
                    //fruitX = -1;
                    //fruitY = -1;
                    //==================
                    return;
                }
                ++count;
            }
            emptyCell = true;
        }
    }
    return;
}

void Snake::loadTextures() {
    res_head.load("source/head.png");
    res_body.load("source/body.png");
    res_fruit.load("source/fruit.png");
    res_wall.load("source/wall.png");
}

void Snake::movement() {
    qApp->processEvents();
    ++m_stepCount;
    ++m_stepFromEating;
    if (m_isTheFruitEaten) {
        ++m_snakeLength;
        m_isTheFruitEaten = false;
    }

    // >> Выбор направления нейросетью
    if (m_directionSelectedByNeuroNet) {
        m_direction = choiceDirectionCheckingCollision();
        if (m_collision || m_loopMotion) {
            return;
        }
    }

    // << Выбор направления нейросетью

    for (int i = m_snakeLength - 1; i > 0; --i) {
        snakeX[i] = snakeX[i-1];
        snakeY[i] = snakeY[i-1];
    }
    //
    if (m_direction == UP) snakeY[0]--;
    if (m_direction == DOWN) snakeY[0]++;
    if (m_direction == LEFT) snakeX[0]--;
    if (m_direction == RIGHT) snakeX[0]++;

    if (m_stepFromEating > NUM_CELLS) {
        restart();
    }
}

void Snake::paintEvent(QPaintEvent *e) {
    Q_UNUSED(e)
    drawing();
}

void Snake::drawing() {
    QPainter qp(this);
    if (!m_gameOver) {
        for (int i = 0; i < m_numberOfCellsPerSide; ++i) {
            for (int j = 0; j < m_numberOfCellsPerSide; ++j) {
                if ( i == 0 || i == (m_numberOfCellsPerSide - 1) ||
                     j == 0 || j == (m_numberOfCellsPerSide - 1)) {
                    qp.drawImage(i * m_cellSize, j * m_cellSize, res_wall);
                }
            }
        }
        qp.drawImage(fruitX * m_cellSize, fruitY * m_cellSize, res_fruit); // +1 для учета толщины стенки
        for (int i = 0; i < m_snakeLength; ++i) {
            if (i == 0) {
                qp.drawImage(snakeX[i] * m_cellSize, snakeY[i] * m_cellSize, res_head); // +1 для учета толщины стенки
            } else {
                qp.drawImage(snakeX[i] * m_cellSize, snakeY[i] * m_cellSize, res_body); // +1 для учета толщины стенки
            }
        }
    }
    else {
        //gameOver(qp);
        qApp->quit();
    }
}

void Snake::keyPressEvent(QKeyEvent *e) {
    if (e->key() == Qt::Key_Insert) {
        qApp->quit();
    }
    QWidget::keyPressEvent(e);
}

bool Snake::collision(const int* const snakeX, const int* const snakeY) {
    // Столкновения со стенками
    // -1 для учета ширины стенки
    if (snakeX[0] < 1 || snakeX[0] >= (m_numberOfCellsPerSide - 1) ||
        snakeY[0] < 1 || snakeY[0] >= (m_numberOfCellsPerSide - 1)) {
        return true;
    }

    // Столкновения с телом змейки
    for (int i = 1; i < m_snakeLength; ++i) {
        if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
            return true;
        }
    }
    return false;
}

bool Snake::isTheFruitEaten() {
    if (snakeX[0] == fruitX && snakeY[0] == fruitY) {
        locateFruit();
        m_isTheFruitEaten = true;
        m_stepFromEating = 0;
        return true;
    }
    m_isTheFruitEaten = false;
    return false;
}

void Snake::writeData() {
    m_vIn.clear();
    // Заполняем входной вектор для подачи в нейросеть
    for (size_t x = 0; x < m_vField.size(); ++x) {
        for (size_t y = 0; y < m_vField[x].size(); ++y) {
            m_vField[x][y] = TYPE_CELL::EMPTY;
            if (x == 0 || y == 0 || x == ((size_t)m_numberOfCellsPerSide - 1) || y == ((size_t)m_numberOfCellsPerSide - 1)) {
                m_vField[x][y] = TYPE_CELL::WALL;
            }
        }
    }
    for (size_t x = 0; x < m_vField.size(); ++x) {
        for (size_t y = 0; y < m_vField[x].size(); ++y) {
            if ( x == (size_t)fruitX && y == (size_t)fruitY ) {
                m_vField[x][y] = TYPE_CELL::FRUIT;
            }
            else if ( x == (size_t)snakeX[0] && y == (size_t)snakeY[0]) {
                m_vField[x][y] = TYPE_CELL::HEAD;
            }
            else {
                for (int i = 1; i < m_snakeLength; ++i) {
                    if (x == (size_t)snakeX[i] && y == (size_t)snakeY[i]) {
                        m_vField[x][y] = TYPE_CELL::BODY;
                        break;
                    }
                }
            }
            m_vIn.push_back(m_vField[x][y]);
        }
    }
}

void Snake::learning() {
    if (    m_loopMotion
        ||  m_collision
        ||  m_isTheFruitEaten
        ||  m_isHopelessSituation
        )
    {

        if (m_collision || m_isHopelessSituation) {
            slotGrayBackground100msec();
            badMove();
        }

        if (m_loopMotion) {
            slotGrayBackground100msec();
        }

        if (m_isTheFruitEaten) {
            goodMove();
        }
        // Записываем строчки в обучающую выборку
        //if ( m_stepCount < m_average ) {
        addDataToTrainingSet();
        //}

        snakeTraining();
    }
}

DIRECTION Snake::choiceDirectionCheckingCollision() {
    writeData();
    // Подаем данные в нейросеть, ответ записываем в вектор
    neuroNet->training().forwardPass(m_vIn);
    neuroNet->getOut(m_vOut);

    // Какое из чисел массива больше, туда и пойдет змейка.
    //Номера позиций в массиве 0 - up, 1 - left, 2 - down, 3 - right
    double dTemp = m_vOut[0];
    DIRECTION direction = UP;
    for (size_t i = 1; i < m_vOut.size(); ++i) {
        if (m_vOut[i] > dTemp) {
            direction = static_cast<DIRECTION>(i);
            dTemp = m_vOut[i];
        }
    }
/*
qDebug() << m_stepCount << " " <<   (direction == UP ? "UP " :
                                    direction == DOWN ? "DOWN " :
                                    direction == LEFT ? "LEFT " : "RIGHT ") <<
                                    m_vOut[0]<<" "<<m_vOut[1]<<" "<<m_vOut[2]<<" "<<m_vOut[3];
*/
    // >> Проверка на будующее столкновение
    // Делаем копию змейки
    int tempSnakeX[NUM_CELLS];
    int tempSnakeY[NUM_CELLS];
    for (int i = 0; i < m_snakeLength; ++i) {
        tempSnakeX[i] = snakeX[i];
        tempSnakeY[i] = snakeY[i];
    }
    for (int i = m_snakeLength - 1; i > 0; --i) {
        tempSnakeX[i] = tempSnakeX[i-1];
        tempSnakeY[i] = tempSnakeY[i-1];
    }
    m_netChoiseDirection = direction;
    if (direction == UP) tempSnakeY[0]--;
    if (direction == DOWN) tempSnakeY[0]++;
    if (direction == LEFT) tempSnakeX[0]--;
    if (direction == RIGHT) tempSnakeX[0]++;

    if(collision(tempSnakeX, tempSnakeY)) {
        averageNumberOfSteps();
        m_collision = true;
        return m_direction; // Если будет столкновение, оставляем старое направление)
    }

    return direction;
    // << Проверка на будующее столкновение


}

void Snake::snakeTraining() {
    // >> Обучаем
    if ( m_setCount > 10 && m_setCount > m_average * m_average && !m_bStop) {
        emit signalStatusInfo("learning");
        double sumError;
        double error;
        size_t countOfSet;
        size_t count;
        do {
            count = 0;
            error = 0;
            countOfSet = 0;
            sumError = 0;
            auto itOut = std::end(m_vOutTrainingSet);
            auto itIn = std::end(m_vInTrainingSet);
            for ( /**/ ;
                    itIn != std::begin(m_vInTrainingSet);
                    --itIn, --itOut, ++countOfSet )
            {
                qApp->processEvents();
                neuroNet->training().forwardPass(*std::prev(itIn));
                error = neuroNet->training().calculateError(*std::prev(itOut));
                neuroNet->training().backprop(*std::prev(itOut));
                sumError += error;
                if ( error > m_acceptError ) {
                    count++;
                }
                if (m_bStop) break;
            }
            if (m_bStop) break;
            sumError = sumError / countOfSet; // vSize;
            //qDebug() << count << "=== Total error:" << sumError << "===";
            m_infoSumError = sumError;
            m_infoCount = count;
            emit signalErrorInfo();
        }
        while ( count > (double)countOfSet/neuroNet->getCountOfOutputs()
                || sumError  > m_acceptError);
        // << Обучаем
        emit signalStatusInfo("moving");
        neuroNet->training().saveWeightOfSynapses();
        averageNumberOfSteps(true);
        m_setCount = 0;
    }
}

bool Snake::isHopelessSituation() {
    // >>  змейка попала в безвыходную ситуацию
    for (size_t i = 0; i < m_vIn.size(); ++i) {
        if (m_vIn[i] == HEAD) {
            // Если вокруг головы только стены или тело
            size_t num = static_cast<size_t>(m_numberOfCellsPerSide);
            if (    (m_vIn[i + 1] == WALL || m_vIn[i + 1] == BODY) &&
                    (m_vIn[i - 1] == WALL || m_vIn[i - 1] == BODY) &&
                    (m_vIn[i - num] == WALL || m_vIn[i - num] == BODY) &&
                    (m_vIn[i + num] == WALL || m_vIn[i + num] == BODY)    )
            {
                m_isHopelessSituation = true;
                return true;
            }
            break;
        }
    }
    m_isHopelessSituation = false;
    return false;
}

bool Snake::isSnakeLooped() {
    size_t itemp = static_cast<size_t>(m_numberOfCellsPerSide-2); // 2 - толщина стенок
    if (m_stepCount > (itemp * itemp)) {
        // Змейка зациклилась
        m_loopMotion = true;
        return true;
    }
    m_loopMotion = false;
    return false;
}

void Snake::restart() {
    slotGrayBackground100msec();
    killTimer(timerId);
    initGame();
}

void Snake::goodMove() {
    // Ищем индекс максимального элемента
    // "Поощряем" такой выбор, убираем с других направлений
    size_t maxElement = indexMaxElement();
    double dTemp = m_vOut[maxElement] / 3.0;
    for (size_t i = 0; i < m_vOut.size(); ++i) {
        m_vOut[i] = m_vOut[i] - dTemp;
        if (m_vOut[i] < 0.0) m_vOut[i] = 0.0;
    }
    m_vOut[indexMaxElement()] = 1.0;
}

void Snake::badMove() {
    // Ищем индекс максимального элемента
    // "Осуждаем" такой выбор, добавляем к другим выборам отнятое

    size_t maxElement = indexMaxElement();
    double dTemp = (1.0 - m_vOut[maxElement]) / 3.0; // Неправильный выбор делим на 3 части и распределяем по ровну по остальным сторонам
    for (size_t i = 0; i < m_vOut.size(); ++i) {
        m_vOut[i] = m_vOut[i] + dTemp;
        if (m_vOut[i] > 1.0) m_vOut[i] = 1.0;
    }
    m_vOut[maxElement] = 0.0;
}

void Snake::addDataToTrainingSet() {
    m_setCount++;
    // >> Добавляем данные в файлы обучающих выборок
    std::ofstream file; // файловый поток

    // Открываем входной файл
    std::string fileName = m_inputData;
    file.open(fileName, std::ios::app);
    if (!file) {
        std::cerr << "\"" << fileName << "\" could not be opened!" << std::endl;
        exit(EXIT_FAILURE);
    }
    // Записываем данные
    for (size_t i = 0; i < m_vIn.size(); ++i) {
        file << m_vIn[i] << " ";
    }
    file << "\n";
    file.close();

    // Открываем выходной файл
    fileName = m_outputDataIdeal;
    file.open(fileName, std::ios::app);
    if (!file) {
        std::cerr << "\"" << fileName << "\" could not be opened!" << std::endl;
        exit(EXIT_FAILURE);
    }
    // Записываем данные
    for (size_t i = 0; i < m_vOut.size(); ++i) {
        file << m_vOut[i] << " ";

    }
    file << "\n";
    file.close();
    // << Добавляем данные в файлы обучающих выборок

    // >> Добавляем данные в вектора обучающих выборок
    m_vInTrainingSet.push_back(m_vIn);
    m_vOutTrainingSet.push_back(m_vOut);
    //m_vAcceptError.push_back(false);
    // << Добавляем данные в вектора обучающих выборок
}

size_t Snake::indexMaxElement() {
    // >> Ищем индекс максимального элемента
    double dTemp = m_vOut[0];
    size_t iMax = 0;
    for (size_t i = 1; i < m_vOut.size(); ++i) {
        if (m_vOut[i] > dTemp) {
            iMax = i;
            dTemp = m_vOut[i];
        }
    }
    // << Ищем индекс максимального элемента
    return iMax;
}

void Snake::readDataToTrainingSet() {

    std::ifstream file; // файловый поток
    std::string fileName;
    std::string tempString;
    std::stringstream ss; // строковый поток для преобразования входных данных из строки
    size_t count = 0;

// >> Считываем из файла входы и выходы
    fileName = m_inputData;
    file.open(fileName);
    if (!file) {
        std::cerr << "\"" << fileName << "\" could not be opened!" << std::endl;
        exit(EXIT_FAILURE);
    }

    // >> "input.txt" считываем данные в вектор
    int intemp;
    while(getline(file, tempString)) {
        m_vInTrainingSet.push_back(std::vector<TYPE_CELL>());
        ss << tempString;
        while (ss >> intemp) {
            m_vInTrainingSet[count].push_back(static_cast<TYPE_CELL>(intemp));
        }
        ss.clear(); // очищаем флаги потока
        tempString.clear();
        count++;
    }
    file.close();
    count = 0;
    // << "input.txt" считываем данные в вектор

    fileName = m_outputDataIdeal;
    file.open(fileName);
    if (!file) {
        std::cerr << "\"" << fileName << "\" could not be opened!" << std::endl;
        exit(EXIT_FAILURE);
    }

    // >> "outputIdeal.txt" считываем данные в вектор
    double dTemp;
    while(getline(file, tempString)) {
        m_vOutTrainingSet.push_back(std::vector<double>());
        //m_vAcceptError.push_back(false);
        ss << tempString;
        while (ss >> dTemp) {
            m_vOutTrainingSet[count].push_back(dTemp);
        }
        ss.clear(); // очищаем флаги потока
        tempString.clear();
        count++;
    }
    file.close();
    // << "output.txt" считываем данные в вектор

// << Считываем из файла входы и выходы
}

void Snake::initiallyPositionSnake() {
    m_firstDirection = static_cast<DIRECTION>(rand() % 4);
    if (m_firstDirection == UP) {
        for (int i = 0; i < m_snakeLength; ++i) {
            snakeX[i] = m_numberOfCellsPerSide/2;
            snakeY[i] = m_numberOfCellsPerSide/2 + i;
        }
    }
    if (m_firstDirection == LEFT) {
        for (int i = 0; i < m_snakeLength; ++i) {
            snakeX[i] = m_numberOfCellsPerSide/2  + i;
            snakeY[i] = m_numberOfCellsPerSide/2;
        }
    }
    if (m_firstDirection == DOWN) {
        for (int i = 0; i < m_snakeLength; ++i) {
            snakeX[i] = m_numberOfCellsPerSide/2;
            snakeY[i] = m_numberOfCellsPerSide/2 - i;
        }
    }
    if (m_firstDirection == RIGHT) {
        for (int i = 0; i < m_snakeLength; ++i) {
            snakeX[i] = m_numberOfCellsPerSide/2 - i;
            snakeY[i] = m_numberOfCellsPerSide/2;
        }
    }
}

void Snake::averageNumberOfSteps(bool restart) {
    if (restart) {
        m_averageNumberOfSteps = {0, 0};
        return;
    }
    // >> Считаем среднее количество шагов
    m_averageNumberOfSteps.first += m_stepCount;
    ++m_averageNumberOfSteps.second;
    //double average;
    m_average = static_cast<double> (m_averageNumberOfSteps.first) /
                static_cast<double> (m_averageNumberOfSteps.second);

//qDebug() << m_vInTrainingSet.size() << ">>>" << m_stepCount
//                << "<<<\taverage:" << m_average
//                << "<<<";
    emit signalRunInfo();
    // << Считаем среднее количество шагов
}

void Snake::createFile(const std::string & fileName, bool clearFile) {
    std::fstream file; // файловый поток
    std::ios_base::openmode mode {std::ios::in};
    if (clearFile) mode = std::ios::out | std::ios::trunc;

    file.open(fileName, mode);
    if (!file) {
        std::cerr << "\"" << fileName << "\" could not be opened!" << std::endl;
        exit(EXIT_FAILURE);
    }
    file.close();

}

void Snake::setNN(const std::vector<size_t> & vNeuron, const std::vector<size_t> & vSynapse, bool newSynapseWeights) {
    if (neuroNet) delete neuroNet;
    neuroNet = new Net(vNeuron, vSynapse, newSynapseWeights);
    m_vIn.resize(neuroNet->getCountOfInputs());
    m_vOut.resize(neuroNet->getCountOfOutputs());
}

void Snake::clearFiles(bool clear) {
    m_clearFiles = clear;
    createFile(m_inputData, clear);
    createFile(m_outputDataIdeal, clear);
    if (clear) {
        m_vInTrainingSet.clear();
        m_vOutTrainingSet.clear();
        readDataToTrainingSet();
    }
}

void Snake::slotBlackBackground() {
    QPalette pall;
    pall.setColor(backgroundRole(), Qt::black);
    setPalette(pall);
    update();
}

void Snake::slotGrayBackground100msec() {
    QPalette pall;
    pall.setColor(backgroundRole(), Qt::darkGray);
    setPalette(pall);
    update();
    QTimer::singleShot(100, this, SLOT(slotBlackBackground()));
}

void Snake::processingSnakeEvents() {
    // После столкновения или безвыходной ситуации начинаем заново
    if (m_collision || m_isHopelessSituation) {
        restart();
    }
}

void Snake::effects() {
    if (m_collision || m_isHopelessSituation || m_loopMotion) {
        slotGrayBackground100msec();
    }
}
