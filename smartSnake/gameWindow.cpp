#include "gameWindow.h"

GameWindow::GameWindow(QWidget *parent) :
    QWidget{parent}
{
    m_pSnake = new Snake(false, false, this);
    m_pSnake->setWindowTitle("Snake");
    m_pSnake->setToolTip("Snake");
    m_pSnake->setFixedSize(400,400);

    QGridLayout* pGLayout = new QGridLayout;
    QSize cellSize {60, 50};

    QLabel* lblNN = new QLabel("Neural Net");
    QLineEdit* leInNeuron = new QLineEdit("100");
    leInNeuron->setToolTip("Count of inputs neural net");
    leInNeuron->setEnabled(false);
    leInNeuron->setFixedSize(cellSize);
    QLineEdit* leFirstLayer = new QLineEdit;
    leFirstLayer->setToolTip("Count of neurons in the first hidden layer");
    leFirstLayer->setFixedSize(cellSize);
    QLineEdit* leSecondLayer = new QLineEdit;
    leSecondLayer->setToolTip("Count of neurons in the second hidden layer");
    leSecondLayer->setFixedSize(cellSize);
    QLineEdit* leOutNeuron = new QLineEdit("4");
    leOutNeuron->setToolTip("Count of outputs neural net");
    leOutNeuron->setFixedSize(cellSize);
    leOutNeuron->setEnabled(false);
    QLabel* lblAError = new QLabel("Acceptable\nerror");
    lblAError->setFixedSize(cellSize);
    QLineEdit* leAError = new QLineEdit;
    leAError->setToolTip("Acceptable error");
    leAError->setFixedSize(cellSize);

    pGLayout->addWidget(lblNN, 0, 0, 1, 6, Qt::AlignCenter);
    pGLayout->addWidget(leInNeuron, 1, 0, Qt::AlignCenter);
    pGLayout->addWidget(leFirstLayer, 1, 1, Qt::AlignCenter);
    pGLayout->addWidget(leSecondLayer, 1, 2, Qt::AlignCenter);
    pGLayout->addWidget(leOutNeuron, 1, 3, Qt::AlignCenter);
    pGLayout->addWidget(lblAError, 1, 4, Qt::AlignCenter);
    pGLayout->addWidget(leAError, 1, 5, Qt::AlignCenter);
    pGLayout->addWidget(m_pSnake, 2, 0, 1, 6, Qt::AlignCenter);

    setLayout(pGLayout);
}
