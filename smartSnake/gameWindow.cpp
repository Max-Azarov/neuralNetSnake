#include <list>
#include <QPushButton>

#include "gameWindow.h"

GameWindow::GameWindow(QWidget *parent) :
    QWidget{parent}
{
    QGridLayout* pGLayout = new QGridLayout;
    QSize cellSize {60, 26};
    std::list<QWidget*> widgets;

    // >> First row Neural Net
    int rowNumber = 0;
    QLabel* lblNN = new QLabel("Neural Net");
    widgets.push_back(lblNN);
    QLineEdit* leInNeuron = new QLineEdit("100");
    leInNeuron->setToolTip("Count of inputs neural net (equal to the number of cells on the screen)");
    leInNeuron->setEnabled(false);
    widgets.push_back(leInNeuron);
    leInNeuron->setAlignment(Qt::AlignCenter);
    QLineEdit* leFirstLayer = new QLineEdit("100");
    leFirstLayer->setToolTip("Count of neurons in the first hidden layer");
    widgets.push_back(leFirstLayer);
    QLineEdit* leSecondLayer = new QLineEdit("200");
    leSecondLayer->setToolTip("Count of neurons in the second hidden layer");
    widgets.push_back(leSecondLayer);
    QLineEdit* leOutNeuron = new QLineEdit("4");
    leOutNeuron->setToolTip("Count of outputs neural net (equal to the number of possible directions: right, left, up, down)");
    widgets.push_back(leOutNeuron);
    leOutNeuron->setEnabled(false);
    QHBoxLayout* hblNN = new QHBoxLayout;
    hblNN->addWidget(leInNeuron);
    hblNN->addWidget(leFirstLayer);
    hblNN->addWidget(leSecondLayer);
    hblNN->addWidget(leOutNeuron);
    QGroupBox* gbNN = new QGroupBox("Neural Net");
    gbNN->setLayout(hblNN);

    pGLayout->addWidget(gbNN, rowNumber, 0, 1, 6, Qt::AlignCenter);
    // << First row

    // >> Second row A =
    rowNumber++;
    QLabel* lblA = new QLabel("A =");
    //lblA->setFixedSize(cellSize);
    lblA->setAlignment(Qt::AlignCenter | Qt::AlignRight);
    //widgets.push_back(lblA);
    lblA->setToolTip("The learning rate of the neural network");
    QLineEdit* leA = new QLineEdit("0.1");
    leA->setToolTip("The learning rate of the neural network");
    widgets.push_back(leA);
    QLabel* lblE = new QLabel("E =");
    //widgets.push_back(lblE);
    lblE->setFixedSize(cellSize);
    lblE->setAlignment(Qt::AlignCenter | Qt::AlignRight);
    lblE->setToolTip("The learning moment of the neural network");
    QLineEdit* leE = new QLineEdit("0.05");
    leE->setToolTip("The learning moment of the neural network");
    widgets.push_back(leE);
    QLabel* lblAError = new QLabel("Acceptable\nerror");
    widgets.push_back(lblAError);
    QLineEdit* leAError = new QLineEdit("0.01");
    leAError->setToolTip("Acceptable error");
    widgets.push_back(leAError);
    QHBoxLayout* hblTrainingSet = new QHBoxLayout;
    hblTrainingSet->addWidget(lblA);
    hblTrainingSet->addWidget(leA);
    hblTrainingSet->addWidget(lblE);
    hblTrainingSet->addWidget(leE);
    hblTrainingSet->addWidget(lblAError);
    hblTrainingSet->addWidget(leAError);
    QGroupBox* gbTrainingSet = new QGroupBox("Training parameters");
    gbTrainingSet->setLayout(hblTrainingSet);

    pGLayout->addWidget(gbTrainingSet, rowNumber, 0, 1, 6, Qt::AlignCenter);
    // << Second row

    // >> Third row New weights
    rowNumber++;
    QCheckBox* cbNewWeights = new QCheckBox("New weights");
    //cbNewWeights->setCheckState(Qt::Checked);
    cbNewWeights->setToolTip("Do need to assign new random weights to synapses");
    QCheckBox* cbNewTrainingData = new QCheckBox("New training data");
    //cbNewWeights->setCheckState(Qt::Checked);
    cbNewTrainingData->setToolTip("Do need to assign new training data for neural network "
                                  "training (the existing training set is deleted)");
    QLabel* lblSnakeSpeed = new QLabel("Snake\nspeed");
    widgets.push_back(lblSnakeSpeed);
    lblSnakeSpeed->setToolTip("Snake speed in steps per second");
    QLineEdit* leSnakeSpeed = new QLineEdit("10");
    leSnakeSpeed->setToolTip("Snake speed in steps per second");
    widgets.push_back(leSnakeSpeed);

    pGLayout->addWidget(cbNewWeights, rowNumber, 0, 1, 2, Qt::AlignCenter);
    pGLayout->addWidget(cbNewTrainingData, rowNumber, 2, 1, 2, Qt::AlignCenter);
    pGLayout->addWidget(leSnakeSpeed, rowNumber, 5);
    pGLayout->addWidget(lblSnakeSpeed, rowNumber, 4);
    // << Third rowNumber

    // >> Fourth row Snake
    rowNumber++;
    m_pSnake = new Snake(false, false, this);
    m_pSnake->setWindowTitle("Snake");
    m_pSnake->setToolTip("Snake");
    m_pSnake->setFixedSize(400,400);

    pGLayout->addWidget(m_pSnake, rowNumber, 0, 1, 6, Qt::AlignCenter);
    // << Fourth row

    // Fifth row Count of starts
    rowNumber++;
    QLabel* lblCountOfSetsTitle = new QLabel("Count of\nstarts");
    widgets.push_back(lblCountOfSetsTitle);
    lblCountOfSetsTitle->setToolTip("Count of runs contained in the training set");
    QLabel* lblCountOfStepsTitle = new QLabel("Count of\nsteps");
    widgets.push_back(lblCountOfStepsTitle);
    lblCountOfStepsTitle->setToolTip("Number of steps completed by snakes in the current run");
    QLabel* lblCountOfEatenFruitsTitle = new QLabel("Count of\neaten fruits");
    widgets.push_back(lblCountOfEatenFruitsTitle);
    lblCountOfEatenFruitsTitle->setToolTip("The count of fruits eaten in the current run");
    QLabel* lblAverageCountOfSetsTitle = new QLabel("Average\nsteps count");
    widgets.push_back(lblAverageCountOfSetsTitle);
    lblAverageCountOfSetsTitle->setToolTip("The average number of steps of the snake, starting with waking up");
    QHBoxLayout* hblInfoRun1 = new QHBoxLayout;
    hblInfoRun1->addWidget(lblCountOfSetsTitle);
    hblInfoRun1->addSpacing(10);
    hblInfoRun1->addWidget(lblCountOfStepsTitle);
    hblInfoRun1->addWidget(lblCountOfEatenFruitsTitle);
    hblInfoRun1->addSpacing(10);
    hblInfoRun1->addWidget(lblAverageCountOfSetsTitle);

    QLabel* lblCountOfSets = new QLabel;
    widgets.push_back(lblCountOfSets);
    lblCountOfSets->setToolTip("Count of runs contained in the training set");
    QLabel* lblCountOfSteps = new QLabel;
    widgets.push_back(lblCountOfSteps);
    lblCountOfSteps->setToolTip("Number of steps completed by snakes in the current run");
    QLabel* lblCountOfEatenFruits = new QLabel;
    widgets.push_back(lblCountOfEatenFruits);
    lblCountOfEatenFruits->setToolTip("The number of fruits eaten in the current run");
    QLabel* lblAverageCountOfSets = new QLabel;
    widgets.push_back(lblAverageCountOfSets);
    lblAverageCountOfSets->setToolTip("The average number of steps of the snake, starting with waking up");
    QHBoxLayout* hblInfoRun2 = new QHBoxLayout;
    hblInfoRun2->addWidget(lblCountOfSets);
    hblInfoRun2->addSpacing(10);
    hblInfoRun2->addWidget(lblCountOfSteps);
    hblInfoRun2->addWidget(lblCountOfEatenFruits);
    hblInfoRun2->addSpacing(10);
    hblInfoRun2->addWidget(lblAverageCountOfSets);

    QVBoxLayout* vblInfoRun = new QVBoxLayout;
    vblInfoRun->addLayout(hblInfoRun1);
    vblInfoRun->addLayout(hblInfoRun2);

    QGroupBox* gbInfoRun = new QGroupBox;
    gbInfoRun->setLayout(vblInfoRun);

    pGLayout->addWidget(gbInfoRun, rowNumber, 0, 1, 6, Qt::AlignCenter);
    // << Fifth row

    // Next row Number of high error
    rowNumber++;
    QLabel* lblCountOfErrorHigherTitle = new QLabel("Number of\nhigh error");
    widgets.push_back(lblCountOfErrorHigherTitle);
    lblCountOfErrorHigherTitle->setToolTip("Count of cases is higher than the acceptable error");
    QLabel* lblErrorTitle = new QLabel("Current\nvalue of\ntotal error");
    lblErrorTitle->setFixedSize(cellSize.width(), cellSize.height()*2);
    lblErrorTitle->setAlignment(Qt::AlignCenter);
    lblErrorTitle->setToolTip("Current error value");

    QTextEdit* lwCountOfErrorHigher = new QTextEdit;
    lwCountOfErrorHigher->setFixedSize(cellSize.width()*2, cellSize.height()*2);
    lwCountOfErrorHigher->setToolTip("Count of cases is higher than the acceptable error and Current error value");
    lwCountOfErrorHigher->setAlignment(Qt::AlignCenter);

    pGLayout->addWidget(lblCountOfErrorHigherTitle, rowNumber, 1, Qt::AlignCenter);
    pGLayout->addWidget(lwCountOfErrorHigher, rowNumber, 2, Qt::AlignCenter);
    pGLayout->addWidget(lblErrorTitle, rowNumber, 3, 1, 2, Qt::AlignCenter);
    // << Next row

    // Next row Buttons
    rowNumber++;
    QPushButton* btnStart = new QPushButton("St&art");
    QPushButton* btnStop = new QPushButton("St&op");

    pGLayout->addWidget(btnStart, rowNumber, 0, Qt::AlignCenter);
    pGLayout->addWidget(btnStop, rowNumber, 5, Qt::AlignCenter);
    // << Next row

    for (auto it = std::begin(widgets); it != std::end(widgets); ++it) {
        (*it)->setFixedSize(cellSize);
        QLineEdit* tempLE = dynamic_cast<QLineEdit*>(*it);
        if (tempLE) tempLE->setAlignment(Qt::AlignCenter);
        QLabel* tempLbl = dynamic_cast<QLabel*>(*it);
        if (tempLbl) tempLbl->setAlignment(Qt::AlignCenter);
    }

    setLayout(pGLayout);
    //setFixedSize(470, 750);
}
