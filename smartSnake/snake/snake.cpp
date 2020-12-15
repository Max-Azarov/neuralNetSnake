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
    delete neuroNet;
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
  , m_pLearnState { nullptr }
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

    averageNumberOfSteps(true);

    initGame();
    pTimer = new QTimer(this);
    connect(pTimer, SIGNAL(timeout()), SLOT(slotLoop()));
}

size_t Snake::getNumTrainingSet() {
    return getNumTrainingSet(*m_pLearnState->getLearning());
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
        writeInputData(*m_pLearnState->getWriteInputData());
        movement(); // в том числе choiseDirection
        checkTheFruitEaten(); // съела ли фрукт
        checkHopelessSituation(); // Попала ли в ловушку
        effects();
        if (!m_freedom) learning(*m_pLearnState->getLearning()); // учится
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
                    return;
                }
                ++count;
            }
            emptyCell = true;
        }
    }
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
        choiseDirection(*m_pLearnState->getChoiseDirection());
    }
    QStringList debug;
    debug << QString::number(this->getStepCount()) <<
                (m_direction == UP ? "UP   " :
                m_direction == DOWN ? "DOWN " :
                m_direction == LEFT ? "LEFT " : "RIGHT");

    for (auto it = std::begin(*this->getVOut()); it != std::end(*this->getVOut()); ++it) {
        debug << QString::number(*it, 'f', 3);
    }
    LogOut::messageOut(debug.join("  "));
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
        update();
        return true;
    }
    m_isTheFruitEaten = false;
    return false;
}

bool Snake::checkHopelessSituation() {
    writeField();
    // >>  змейка попала в безвыходную ситуацию
    for (size_t x = 1; x < m_vField.size()-1; ++x) {
        for (size_t y = 1; y < m_vField[x].size()-1; ++y) {
            if ( m_vField[x][y] == TYPE_CELL::HEAD ) {
                if (    (m_vField[x + 1][y] == WALL || m_vField[x + 1][y] == BODY) &&
                        (m_vField[x - 1][y] == WALL || m_vField[x - 1][y] == BODY) &&
                        (m_vField[x][y + 1] == WALL || m_vField[x][y + 1] == BODY) &&
                        (m_vField[x][y - 1] == WALL || m_vField[x][y - 1] == BODY)    )
                {
                    m_isHopelessSituation = true;

                    update();
                    return true;
                }
                return false;
            }
        }
    }
    return false;
}

void Snake::restart() {
    averageNumberOfSteps();
    initGame();
    update();
    emit signalRunInfo();
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

    // << Считаем среднее количество шагов
}



void Snake::setNN(const std::vector<size_t> & vNeuron, const std::vector<size_t> & vSynapse, bool newSynapseWeights) {
    if (neuroNet) delete neuroNet;
    neuroNet = new Net(vNeuron, vSynapse, newSynapseWeights);

    // Начиная с первого скрытого слоя, далее нейронам каждого второго из скрытых слоев присваиваем тип активации RELU (кроме нейрона смещения)
    auto itLayer = std::begin(neuroNet->getNeuron());
    auto endIt = std::end(neuroNet->getNeuron());
    auto prevEndIt = std::prev(std::end(neuroNet->getNeuron()));
    itLayer++;
    for ( ;
          (itLayer != prevEndIt) && (itLayer != endIt);
          itLayer +=2 )
    {
        for ( auto it = std::begin(*itLayer); it != std::prev(std::end(*itLayer)); ++it) {
            (*it)->setTypeActivation(RELU);
        }
    }
    // <<

    m_vIn.resize(neuroNet->getCountOfInputs());
    m_vOut.resize(neuroNet->getCountOfOutputs());
}

void Snake::clearFiles(bool clear) {
    m_clearFiles = clear;
    if (clear) clearData(*m_pLearnState->getLearning());
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
    if (m_collision) {
        slotGrayBackground100msec();
    }
}

void Snake::learning(Learning& concreteLearning) {
    emit signalStatusInfo("learning");
    concreteLearning.learning();
    emit signalStatusInfo("moving");
}

void Snake::readDataToTrainingSet(Learning& concreteLearning) {
    concreteLearning.readDataToTrainingSet();
}

size_t Snake::getNumTrainingSet(Learning& concreteLearning) {
    return concreteLearning.getNumTrainingSet();
}

void Snake::clearData(Learning& concreteLearning) {
    concreteLearning.clearData();
}

void Snake::choiseDirection(ChoiseDirection& concreteChoise) {
    m_direction = concreteChoise.choise();
}

void Snake::writeInputData(WriteInputData& concreteWriteField) {
    writeField();
    concreteWriteField.writeInputData();
}

size_t Snake::getNumOfInputsNN(WriteInputData& concreteWriteField) {
    return concreteWriteField.getNumInputData();
}

size_t Snake::getNumOfOutputsNN(ChoiseDirection& concreteChoiseDirection) {
    return concreteChoiseDirection.getNumOfOutputs();
}

size_t Snake::getNumOfInputsNN() {
    return getNumOfInputsNN(*m_pLearnState->getWriteInputData());
}

size_t Snake::getNumOfOutputsNN() {
    return getNumOfOutputsNN(*m_pLearnState->getChoiseDirection());
}

void Snake::setLearningState1(int sizeOfArea) {
    m_pLearnState.reset(new LearnStateType1(this, sizeOfArea));
}

void Snake::setLearningState2(int depthOfVision) {
    m_pLearnState.reset(new LearnStateType2(this, depthOfVision));
}

void Snake::mousePressEvent(QMouseEvent* e) {
    manualFruitLocate(e->localPos().x(), e->localPos().y());
    e->accept();
}

void Snake::manualFruitLocate(int x, int y) {
    fruitX = x / m_cellSize;
    fruitY = y / m_cellSize;
    checkBound(&fruitX, 1, m_numberOfCellsPerSide - 2); // ширина игрового поля за исключением ширины стенок
    checkBound(&fruitY, 1, m_numberOfCellsPerSide - 2);
}

void Snake::checkBound(int* value, int bound1, int bound2) {
    if (*value < bound1) *value = bound1;
    if (*value > bound2) *value = bound2;
}

void Snake::writeField() {
    // Заполняем входной вектор для подачи в нейросеть. Не использованы private поля, т.к. метод перекочевал из стороннего класса
    // Пустое поле и стены
    std::vector<std::vector<TYPE_CELL>>& vField = *this->getVField(); // Матрица поля игры

    for (size_t x = 0; x < vField.size(); ++x) {
        for (size_t y = 0; y < vField[x].size(); ++y) {
            vField[x][y] = TYPE_CELL::EMPTY;
            if (x == 0 || y == 0 || x == ((size_t)this->getNumberOfCellsPerSide() - 1) || y == ((size_t)this->getNumberOfCellsPerSide() - 1)) {
                vField[x][y] = TYPE_CELL::WALL;
            }
        }
    }
    //
    for (size_t x = 0; x < vField.size(); ++x) {
        for (size_t y = 0; y < vField[x].size(); ++y) {
            if ( x == (size_t)this->getFruitX() && y == (size_t)this->getFruitY() ) {
                vField[x][y] = TYPE_CELL::FRUIT;
            }
            else if ( x == (size_t)this->getSnakeX()[0] && y == (size_t)this->getSnakeY()[0]) {
                vField[x][y] = TYPE_CELL::HEAD;
            }
            else {
                for (int i = 1; i < (int)this->getSnakeLength(); ++i) {
                    if (x == (size_t)this->getSnakeX()[i] && y == (size_t)this->getSnakeY()[i]) {
                        vField[x][y] = TYPE_CELL::BODY;
                        break;
                    }
                }
            }
        }
    }
}

void Snake::copySnake(int* pSnakeX, int* pSnakeY, int* length) const {
    size_t snakeSize = playFieldSize * playFieldSize;
    for (size_t i = 0; i < snakeSize; ++i) {
        pSnakeX[i] = snakeX[i];
        pSnakeY[i] = snakeY[i];
    }

    *length = m_snakeLength;
}
