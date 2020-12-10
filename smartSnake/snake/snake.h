#ifndef SNAKE_H
#define SNAKE_H

#include <QWidget>
#include <QImage>
#include <QTimer>
#include <QMouseEvent>
#include <memory>

#include "snake/enums.h"
#include "neuroNet/net.h"
#include "snake/writeInputData.h"
#include "snake/choiseDirection.h"
#include "snake/learning.h"
#include "logOut.h"
#include "learnState.h"

class WriteInputData;
class ChoiseDirection;
class Learning;
class ILearnState;

class Snake : public QWidget {
    Q_OBJECT
private:
    const bool m_directionSelectedByNeuroNet = true;
    DIRECTION m_direction;
    bool m_gameOver {false};
    bool m_isTheFruitEaten;
    bool m_collision;
    bool m_isHopelessSituation;
    const int WIDTH = 400;
    const int HEIGHT = 400;
    static const int NUM_CELLS = 100; // Количество клеток, по совместительности количество входов для нейронной сети
    int m_cellSize;
    int m_numberOfCellsPerSide;
    int snakeX[NUM_CELLS];
    int snakeY[NUM_CELLS];
    int fruitX;
    int fruitY;
    size_t m_delay;
    int m_snakeLength;
    int timerId;
    size_t m_stepFromEating;
    size_t m_numFruitEaten;

    std::vector<std::vector<TYPE_CELL>> m_vField; // В векторе содержатся типы клеток поля в координатах х, у

    QImage res_head;
    QImage res_body;
    QImage res_fruit;
    QImage res_wall;

    // Нейросеть
    bool m_newSynapseWeights; // Нужно ли заново случайным образом инициализировать веса синапсов
    size_t m_stepCount;
    std::pair<size_t, size_t> m_averageNumberOfSteps;
    double m_average;
    bool m_loopMotion;
    std::vector<DIRECTION> m_vDirection;
    // Вектора, содержащие текущие значения входов и выходов нейросети
    std::vector<int> m_vIn;
    std::vector<double> m_vOut;


    bool m_clearFiles;
    //bool m_firstMove;
    DIRECTION m_firstDirection;
    double m_acceptError;
    size_t m_countOfStepsToNextTest;
    size_t m_setCount;

    QTimer* pTimer;
    bool m_bMutex;
    bool m_bStop;

    double m_infoSumError;
    size_t m_infoCount;
    bool m_freedom;

private:
    // Type of Learning
    //std::unique_ptr<WriteInputData> m_pWriteInputData;
    //std::unique_ptr<ChoiseDirection> m_pChoiseDirection;
    //std::unique_ptr<Learning> m_pLearning;

    // State of Learning
    std::unique_ptr<ILearnState> m_pLearnState;

private:
    void loadTextures();
    bool collision(const int* const snakeX, const int* const snakeY);
    bool checkTheFruitEaten();
    bool checkHopelessSituation();
    void drawing();
    void initGame();

    void movement();
    std::vector<double> readDataToDouble(std::string fileName);
    std::vector<int> readDataToInt(std::string fileName);

    void restart();
    void initiallyPositionSnake();
    void averageNumberOfSteps(bool restart = false);
    void createFile(const std::string & fileName, bool clearFile);
    void processingSnakeEvents();
    void effects();
    void learning(Learning&);
    void readDataToTrainingSet(Learning&);
    size_t getNumTrainingSet(Learning&);
    void clearData(Learning&);
    void choiseDirection(ChoiseDirection&);
    void writeInputData(WriteInputData&);
    size_t getNumOfInputsNN(WriteInputData&);
    size_t getNumOfOutputsNN(ChoiseDirection&);
    void manualFruitLocate(int x, int y);
    void checkBound(int* value, int bound1, int bound2);
    void writeField(); // Заполняем вектор поля

public:
    Snake(QWidget *parent = nullptr);
    void setDelay(size_t delay);// { m_delay = delay; }
    virtual ~Snake();

    void stop();
    void start(bool freedom);
    Net* getNet() { return neuroNet; }
    void setNN(const std::vector<size_t> & vNeuron, const std::vector<size_t> & vSynapse, bool newSynapseWeights);
    void setAcceptError(double acceptError) { m_acceptError = acceptError; }
    double getAcceptError() const { return m_acceptError; }
    void clearFiles(bool clear = true);
    double getAverage() const { return m_average; }
    size_t getNumTrainingSet();
    size_t getStepCount() const { return m_stepCount; }
    void setSummError(double infoSumError) { m_infoSumError = infoSumError; }
    double getSummError() const { return m_infoSumError; }
    void setInfoCount(size_t infoCount) { m_infoCount = infoCount; }
    size_t getInfoCount() const { return m_infoCount; }
    size_t getSnakeLength() const { return m_snakeLength; }
    size_t getNumFruitEaten() const {return m_numFruitEaten; }
    std::vector<int>* getVIn() { return &m_vIn; }
    std::vector<double>* getVOut() { return &m_vOut; }
    DIRECTION getDirection() const { return m_direction; }
    void locateFruit();
    bool getStopStatus() const { return m_bStop; }
    void setSetCount(size_t setCount) { m_setCount = setCount; }
    size_t getSetCount() const { return m_setCount; }
    void incSetCount() { m_setCount++; }
    bool getStatusCollision() const { return m_collision; }
    bool getStatusFruitEaten() const { return m_isTheFruitEaten; }
    bool getStatusHopelessSituation() const { return m_isHopelessSituation; }
    std::vector<std::vector<TYPE_CELL>>* getVField() { return &m_vField; }
    int getNumberOfCellsPerSide() const { return m_numberOfCellsPerSide; }
    int getFruitX() const { return fruitX; }
    int getFruitY() const { return fruitY; }
    const int* getSnakeX() const { return snakeX; }
    const int* getSnakeY() const { return snakeY; }
    size_t getStepFromEating() const { return m_stepFromEating; }
    size_t getNumOfInputsNN();
    size_t getNumOfOutputsNN();

protected:
    void paintEvent(QPaintEvent*);
    void keyPressEvent(QKeyEvent*);
    void mousePressEvent(QMouseEvent*);

private:
    Net* neuroNet;

public slots:
    void slotLoop();
    void slotBlackBackground();
    void slotGrayBackground100msec();

signals:
    void signalRunInfo();
    void signalErrorInfo();
    void signalStatusInfo(const QString&);


};

#endif // SNAKE_H
