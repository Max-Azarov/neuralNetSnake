#include <list>
#include <QPushButton>

#include "game/game.h"

Game::Game(QWidget *parent) : QMainWindow{parent}
  , ui{ new Ui::MainWindow }
  , m_pAbout { nullptr }
  , m_bStart {false}
  , m_bIsInitNet { false }
  , m_bNewSynapseWeights { false }
  , m_clearFiles { false }
  , pUIState { new UIStateBegin(this) }
{
    setUIStateStop();
    m_pSnake = ui->snake;

    connect(ui->snake, SIGNAL(signalRunInfo()), this, SLOT(slotRunInfo()));
    connect(ui->snake, SIGNAL(signalErrorInfo()), this, SLOT(slotErrorInfo()));
    connect(ui->snake, SIGNAL(signalStatusInfo(const QString&)), this, SLOT(slotStatusInfo(const QString&)));
}

Game::~Game() {
}

void Game::on_sldSnakeSpeed_valueChanged(int value) {
    //slider
    ui->leSnakeSpeed->setText(QString::number(value));
}

void Game::on_sldSnakeSpeed_sliderReleased() {
    //slider
    int speed = ui->sldSnakeSpeed->value();
    ui->leSnakeSpeed->setText(QString::number(speed));
    setSnakeSpeed(speed);
}

void Game::on_leSnakeSpeed_editingFinished() {
    ui->sldSnakeSpeed->setValue(ui->leSnakeSpeed->text().toInt());
    int speed = ui->sldSnakeSpeed->value();
    ui->leSnakeSpeed->setText(QString::number(speed));
    setSnakeSpeed(speed);
}

void Game::on_cbSnakeSpeed_stateChanged(int state) {
    pUIState->cbSnakeSpeedStateChanged(state);
    if (state) {
        // Qt::PartiallyChecked or Qt::Checked
        setSnakeSpeed(1000);
    }
    else {
        // Qt::unchecked
        setSnakeSpeed(ui->sldSnakeSpeed->value());
    }
}


void Game::on_btnStart_released() {
    if (m_bStart) {
        // Текущее состояние "Старт" меняем на состояние "Стоп"
        setUIStateStop();
        m_bStart = false;
        m_pSnake->stop();
    }
    else {
        // Текущее состояние "Стоп" меняем на состояние "Старт"
        setUIStateStart();
        m_bStart = true;
        m_pSnake->clearFiles(m_clearFiles);
        if (!m_bIsInitNet) {
            pUIState->readTypeOfLearning();
            initNet();
            m_bIsInitNet = true;
        }
        setTrainingParameters();
        setSnakeSpeed();
        m_pSnake->start(ui->cbFreedom->checkState());
        on_sldSnakeSpeed_sliderReleased();
        on_cbSnakeSpeed_stateChanged(ui->cbSnakeSpeed->checkState());
    }
}

void Game::on_leNum1HiddenNN_editingFinished() {
    m_bIsInitNet = false;
    intValidate(ui->leNum1HiddenNN, "4");
}

void Game::on_leNum2HiddenNN_editingFinished() {
    m_bIsInitNet = false;
    intValidate(ui->leNum2HiddenNN, "4");
}

void Game::on_leNumOfHiddenLayersNN_editingFinished() {
    m_bIsInitNet = false;
    intValidate(ui->leNumOfHiddenLayersNN, "2");
}

void Game::on_cbNewWeights_stateChanged(int state) {
    pUIState->cbNewWeightsStateChanged(state);
    if (state) {
        // Qt::checked
        m_bNewSynapseWeights = true;
        m_bIsInitNet = false;
    }
}

void Game::on_cbNewTrainingData_stateChanged(int state) {
    m_clearFiles = (bool)state;
}

void Game::on_cboLearningType_currentIndexChanged(int ) {
    //Q_UNUSED(index)
}

void Game::on_cboLearningType_activated(int ) {
    //Q_UNUSED(index)
    pUIState->setTypeOfLearning();
    m_bIsInitNet = false;
}

void Game::on_leLearningParam_editingFinished() {
    intValidate(ui->leLearningParam, "1"); // Валидация ввода
    pUIState->setTypeOfLearning();
    m_bIsInitNet = false;
}

void Game::on_actAbout_triggered() {
    m_pAbout.reset(new About(this));
}

void Game::closeAbout() {
    m_pAbout.reset(nullptr);
}

void Game::initNet() {
    size_t numOfInput = m_pSnake->getNumOfInputsNN();
    size_t numOfOutput = m_pSnake->getNumOfOutputsNN();
    std::vector<size_t> vNeuron;
    vNeuron.push_back(numOfInput); // Формируем слой входов в зависимости от выбора способа формирования входных данных class WriteField
    vNeuron.push_back(ui->leNum1HiddenNN->text().toUInt());
    size_t numHiddenLayers = ui->leNumOfHiddenLayersNN->text().toUInt();
    size_t numNeuronInHiddenLayer = ui->leNum2HiddenNN->text().toUInt();
    for (size_t i = 0; i < numHiddenLayers - 1; ++i) {
        vNeuron.push_back(numNeuronInHiddenLayer);
    }
    vNeuron.push_back( numOfOutput ); // Формируем слой выходов в зависимости от выбора способа формирования выходных данных class ChoiseDirection

    std::vector<size_t> vSynapse(vNeuron.size() - 1, 1);

    m_pSnake->setNN(vNeuron, vSynapse, m_bNewSynapseWeights);
}

void Game::setSnakeSpeed(int speed) {
    int num_msInSec = 1000;
    speed = (speed <= 0) ? 1 : speed;
    m_delay = num_msInSec / speed;
    if (m_bStart) {
        m_pSnake->setDelay(m_delay);
    }
}

void Game::setSnakeSpeed() {
    int num_msInSec = 1000;
    int speed = ui->sldSnakeSpeed->value();
    m_delay = num_msInSec / speed;
    if (m_bStart) {
        m_pSnake->setDelay(m_delay);
    }
}

void Game::setTrainingParameters() {
    m_pSnake->getNet()->parameters().setA(ui->leA->text().toDouble());
    m_pSnake->getNet()->parameters().setE(ui->leE->text().toDouble());
    m_pSnake->setAcceptError(ui->leAcceptError->text().toDouble());
}

void Game::slotRunInfo() {
    ui->lblCountOfSets->setText(QString::number(m_pSnake->getNumTrainingSet()));
    ui->lblCountOfSteps->setText(QString::number(m_pSnake->getStepCount()));
    ui->lblAverageCountOfSets->setText(QString::number(m_pSnake->getAverage(), 'f', 2));
    ui->lblCountOfEatenFruits->setText(QString::number(m_pSnake->getNumFruitEaten()));
}

void Game::intValidate(QLineEdit* const le, const QString& valueForInvalid ) {
    QIntValidator intValidator;
    intValidator.setBottom(valueForInvalid.toInt());
    QString text = le->text();
    int pos = le->cursorPosition();
    if ( !(intValidator.validate(text, pos) == QValidator::Acceptable) ) {
        le->setText(QString::number(intValidator.bottom()));
    }
}

void Game::slotErrorInfo() {
    m_infoCount.push_front(QString::number(m_pSnake->getInfoCount()));
    if (m_infoCount.size() > 5) {
        m_infoCount.removeLast();
    }
    ui->lblCountOfErrorHigher->setText(m_infoCount.join('\n'));
    m_infoError.push_front(QString::number(m_pSnake->getSummError(), 'f', 6));
    if (m_infoError.size() > 5) {
        m_infoError.removeLast();
    }
    ui->lblError->setText(m_infoError.join('\n'));
}

void Game::closeEvent(QCloseEvent* event)
{
    if (m_pSnake->getNet()) m_pSnake->stop();
    QApplication::quit();
    event->accept();
}

void Game::slotStatusInfo(const QString& status) {
    pUIState->statusInfo(status);
}

void Game::setUIStateStop() {
    pUIState->setUIStateStop();
}

void Game::setUIStateStart() {
    pUIState->setUIStateStart();
}
