#include "snake/snake.h"
#include <QTimer>
#include <QtCore>
#include <QKeyEvent>
#include <QPainter>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <fstream>
#include <sstream>
#include <algorithm>

#include <QApplication>

Snake::~Snake() {
    if (neuroNet)           delete neuroNet;
    if (m_pWriteField)      delete m_pWriteField;
    if (m_pChoiseDirection) delete m_pChoiseDirection;
    if (m_LogOut)           delete m_LogOut;
    if (m_pLearning)        delete m_pLearning;
}

Snake::Snake(QWidget *parent) : QWidget{parent}
    , m_delay { 100 }
  , m_average { 0.0 }
    , m_loopMotion { false }
    , m_acceptError { 0.1 }
    , m_countOfStepsToNextTest { 1000 }
    , m_setCount { 0 }
    , m_bMutex { false }
  , m_bStop { true }
  , neuroNet { nullptr }
  , m_LogOut { new LogOut() }
  , m_pWriteField { new WriteField(this) }
  , m_pChoiseDirection { new ChoiseDirection(this) }
  , m_pLearning { new Learning(this) }
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
    averageNumberOfSteps(true);
    emit signalRunInfo();
}

void Snake::start(bool freedom) {
    setDelay(m_delay);
    m_bStop = false;
    m_freedom = freedom;
    emit signalRunInfo();
    slotLoop();
}

// Основной цикл игры
void Snake::slotLoop() {
    if ( !m_bMutex ) {
        m_bMutex = true;
        m_pWriteField->writeInputData();
        movement();
        checkTheFruitEaten(); // съела ли фрукт
        checkSnakeLooped(); // Зациклилась ли
        //checkHopelessSituation(); // Попала ли в ловушку
        effects();
        if (!m_freedom) m_pLearning->learning(); // учится
        processingSnakeEvents();
        m_bMutex = false;
    }
    update();
}

void Snake::initGame() {
    //m_firstMove = true;
    m_stepCount = 0;
    m_stepFromEating = 0;
    m_numFruitEaten = 0;
    m_isTheFruitEaten = false;
    m_collision = false;
    m_loopMotion = false;
    m_isHopelessSituation = false;
    m_loopCount = 0;

    m_snakeLength = 3;

    initiallyPositionSnake();
    locateFruit();
}

void Snake::locateFruit() {
    int random = 0;
    bool emptyCell = true;
    int temp = (m_numberOfCellsPerSide-2)*(m_numberOfCellsPerSide-2)
            - m_snakeLength - 1; // 2-толщина 2х стенок; 1-клетка, где лежит фрукт
    if ( temp ) {
        random = rand() % temp;
    }
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
    if (m_isTheFruitEaten) {
        ++m_snakeLength;
        m_isTheFruitEaten = false;
    }
    ++m_stepCount;
    ++m_stepFromEating;

    // >> Выбор направления нейросетью
    if (m_directionSelectedByNeuroNet) {
        m_direction = m_pChoiseDirection->choise();
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

    if(collision(snakeX, snakeY)) {
        averageNumberOfSteps();
        m_collision = true;
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
        qp.drawImage(fruitX * m_cellSize, fruitY * m_cellSize, res_fruit);
        for (int i = 0; i < m_snakeLength; ++i) {
            if (i == 0) {
                qp.drawImage(snakeX[i] * m_cellSize, snakeY[i] * m_cellSize, res_head);
            } else {
                qp.drawImage(snakeX[i] * m_cellSize, snakeY[i] * m_cellSize, res_body);
            }
        }
    }
    else {
        //gameOver(qp);
        qApp->quit();
    }
}

void Snake::keyPressEvent(QKeyEvent *e) {
    /*
    if (e->key() == Qt::Key_Insert) {
        qApp->quit();
    }
    */
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

bool Snake::checkTheFruitEaten() {
    if (snakeX[0] == fruitX && snakeY[0] == fruitY) {
        locateFruit();
        m_isTheFruitEaten = true;
        m_stepFromEating = 0;
        m_numFruitEaten++;
        return true;
    }
    m_isTheFruitEaten = false;
    return false;
}

bool Snake::checkHopelessSituation() {
    // >>  змейка попала в безвыходную ситуацию
    for (size_t x = 0; x < m_vField.size(); ++x) {
        for (size_t y = 0; y < m_vField[x].size(); ++y) {
            if ( m_vField[x][y] == TYPE_CELL::HEAD ) {
                if (    (m_vField[x + 1][y] == WALL || m_vField[x + 1][y] == BODY) &&
                        (m_vField[x - 1][y] == WALL || m_vField[x - 1][y] == BODY) &&
                        (m_vField[x][y + 1] == WALL || m_vField[x][y + 1] == BODY) &&
                        (m_vField[x][y - 1] == WALL || m_vField[x][y - 1] == BODY)    )
                {
                    m_isHopelessSituation = true;
                    return true;
                }
            }
        }
    }

    //m_isHopelessSituation = false;
    return false;
}

bool Snake::checkSnakeLooped() {
    size_t itemp = static_cast<size_t>(m_numberOfCellsPerSide-2); // 2 - толщина стенок
    m_loopCount++;
    if (m_loopCount > (itemp * itemp)) {
        // Змейка зациклилась
        m_loopMotion = true;
        m_loopCount = 0;
        return true;
    }
    m_loopMotion = false;
    if (m_isTheFruitEaten) m_loopCount = 0;
    return false;
}

void Snake::restart() {
    //slotGrayBackground100msec();
    initGame();
    update();
    emit signalRunInfo();
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
        m_vInTrainingSet.push_back(std::vector<int>());
        ss << tempString;
        while (ss >> intemp) {
            m_vInTrainingSet[count].push_back(/*static_cast<TYPE_CELL>*/(intemp));
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
    //emit signalRunInfo();
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

    // Первому из скрытых слоев присваиваем тип активации RELU
    for ( auto it = std::begin(neuroNet->getNeuron()[1]); it != std::end(neuroNet->getNeuron()[1]); ++it) {
        (*it)->setTypeActivation(RELU);
    }

/*
    // Второму из скрытых слоев присваиваем тип активации RELU
    for ( auto it = std::begin(neuroNet->getNeuron()[2]); it != std::end(neuroNet->getNeuron()[2]); ++it) {
        (*it)->setTypeActivation(RELU);
    }
*/
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
    if (m_collision || m_isHopelessSituation || m_loopMotion) {
        restart();
    }
}

void Snake::effects() {
    if (m_collision || m_isHopelessSituation) {
        slotGrayBackground100msec();
    }
}
