#ifndef SNAKE_H
#define SNAKE_H

#include <QWidget>
#include <QImage>
#include <QTimer>

#include "enums.h"
#include "neuroNet/net.h"

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
    DIRECTION m_netChoiseDirection;
    std::vector<DIRECTION> m_vDirection;
    // Вектора, содержащие текущие значения входов и выходов нейросети
    std::vector<TYPE_CELL> m_vIn;
    std::vector<double> m_vOut;
    // Вектора, содержащие обучающие выборки
    std::vector<std::vector<TYPE_CELL>> m_vInTrainingSet;
    std::vector<std::vector<double>> m_vOutTrainingSet;
    //std::vector<bool> m_vAcceptError;
    // Названия файлов, содержащие обучающие выборки
    std::string m_inputData;
    std::string m_outputDataIdeal;
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

private:
    void loadTextures();
    bool collision(const int* const snakeX, const int* const snakeY);
    bool isTheFruitEaten();
    bool isHopelessSituation();
    bool isSnakeLooped();
    void drawing();
    void initGame();
    void locateFruit();
    void movement();
    void writeData();
    std::vector<double> readDataToDouble(std::string fileName);
    std::vector<int> readDataToInt(std::string fileName);
    void learning();
    DIRECTION choiceDirectionCheckingCollision();
    //void synapsesConvalution();
    void readDataToTrainingSet();

    void snakeTraining();
    //void saveWeightOfSynapses();
    void restart();
    void goodMove();
    void badMove();
    void addDataToTrainingSet();
    size_t indexMaxElement();
    void initiallyPositionSnake();
    void averageNumberOfSteps(bool restart = false);
    //void disableUselessSynapses();
    void createFile(const std::string & fileName, bool clearFile);

public:
    Snake(QWidget *parent = nullptr);
    void setDelay(size_t delay);// { m_delay = delay; }
    virtual ~Snake();

    void stop();
    void start();
    Net* getNet() { return neuroNet; }
    void setNN(const std::vector<size_t> & vNeuron, const std::vector<size_t> & vSynapse, bool newSynapseWeights);
    void setAcceptError(double acceptError) { m_acceptError = acceptError; }
    void clearFiles(bool clear = true);
    double getAverage() const { return m_average; }
    size_t getNumTrainingSet() const { return m_vInTrainingSet.size(); }
    size_t getStepCount() const { return m_stepCount; }
    double getSummError() const { return m_infoSumError; }
    size_t getInfoCount() const { return m_infoCount; }
    size_t getSnakeLength() const { return m_snakeLength; }

protected:
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *);

private:
    Net* neuroNet;

public slots:
    void slotLoop();
    void slotBlackBackground();
    void slotGrayBackground100msec();

signals:
    void signalRunInfo();
    void signalErrorInfo();

};

#endif // SNAKE_H
