#include <list>
#include <QPushButton>

#include "game.h"

Game::Game(QWidget *parent) : QMainWindow{parent}
  , ui{ new Ui::MainWindow }
  , m_bStart {false}
  , m_bIsInitNet { false }
  , m_settings {"monstr", "smartSnake", this }
  , m_bNewSynapseWeights { false }
{
    ui->setupUi(this);
    m_pSnake = ui->snake;
    readSettings();

    connect(m_pSnake, SIGNAL(signalRunInfo()), this, SLOT(slotRunInfo()));
    connect(m_pSnake, SIGNAL(signalErrorInfo()), this, SLOT(slotErrorInfo()));
    connect(m_pSnake, SIGNAL(signalStatusInfo(const QString&)), this, SLOT(slotStatusInfo(const QString&)));

}

Game::~Game() {
    writeSettings();
    delete ui;
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
    if (state) {
        // Qt::PartiallyChecked or Qt::Checked
        ui->sldSnakeSpeed->setEnabled(false);
        ui->leSnakeSpeed->setEnabled(false);
        setSnakeSpeed(100);
    }
    else {
        // Qt::unchecked
        ui->sldSnakeSpeed->setEnabled(true);
        ui->leSnakeSpeed->setEnabled(true);
        setSnakeSpeed(ui->sldSnakeSpeed->value());
    }
}

void Game::on_btnStart_released() {
    if (m_bStart) {
        // Текущее состояние "Старт" меняем на состояние "Стоп"
        m_bStart = false;
        m_pSnake->stop();
        ui->btnStart->setText("Старт");
        ui->gBoxNN->setEnabled(true);
        ui->gbTrainingSet->setEnabled(true);
        ui->cbNewWeights->setCheckState(Qt::Unchecked);
        ui->cbNewTrainingData->setCheckState(Qt::Unchecked);
        ui->cbFreedom->setEnabled(true);
        slotStatusInfo("stop");
    }
    else {
        // Текущее состояние "Стоп" меняем на состояние "Старт"
        m_bStart = true;
        if (!m_bIsInitNet) {
            initNet();
            m_bIsInitNet = true;
        }
        setTrainingParameters();
        setSnakeSpeed();
        m_pSnake->start(ui->cbFreedom->checkState());
        on_sldSnakeSpeed_sliderReleased();
        ui->btnStart->setText("Стоп");
        ui->gBoxNN->setEnabled(false);
        ui->gbTrainingSet->setEnabled(false);
        on_cbSnakeSpeed_stateChanged(ui->cbSnakeSpeed->checkState());

        ui->leNum1HiddenNN->setText(ui->leNum1HiddenNN->text());
        ui->cbFreedom->setEnabled(false);
        slotStatusInfo("start");
        //qDebug() << ui->leNum1HiddenNN->text();
    }
}

void Game::on_leNum1HiddenNN_editingFinished() {
    m_bIsInitNet = false;
    intValidate(ui->leNum1HiddenNN, "10");
}

void Game::on_leNum2HiddenNN_editingFinished() {
    m_bIsInitNet = false;
    intValidate(ui->leNum2HiddenNN, "10");
}

void Game::on_leNumOfHiddenLayersNN_editingFinished() {
    m_bIsInitNet = false;
    intValidate(ui->leNumOfHiddenLayersNN, "2");
}

void Game::on_cbNewWeights_stateChanged(int state) {
    if (state) {
        ui->leNum1HiddenNN->setEnabled(true);
        ui->leNum2HiddenNN->setEnabled(true);
        ui->leNumOfHiddenLayersNN->setEnabled(true);
        m_bNewSynapseWeights = true;
        m_bIsInitNet = false;
    }
    if (!state) {
        // Qt::unchecked
        ui->leNum1HiddenNN->setEnabled(false);
        ui->leNum2HiddenNN->setEnabled(false);
        ui->leNumOfHiddenLayersNN->setEnabled(false);
    }
}

void Game::initNet() {
    std::vector<size_t> vNeuron;
    vNeuron.push_back(ui->leNumInputNN->text().toUInt());
    vNeuron.push_back(ui->leNum1HiddenNN->text().toUInt());
    size_t numHiddenLayers = ui->leNumOfHiddenLayersNN->text().toUInt();
    size_t numNeuronInHiddenLayer = ui->leNum2HiddenNN->text().toUInt();
    for (size_t i = 0; i < numHiddenLayers - 1; ++i) {
        vNeuron.push_back(numNeuronInHiddenLayer);
    }
    vNeuron.push_back( ui->leNumOutputNN->text().toUInt() );

    std::vector<size_t> vSynapse(vNeuron.size() - 1, 1);
    vSynapse[0] = 10; // Особенность устройства нейросети змейки

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

void Game::readSettings(){
    m_settings.beginGroup("/Settings");
    ui->leNum1HiddenNN->setText(m_settings.value("/leNum1HiddenNN", "100").toString());
    ui->leNum2HiddenNN->setText(m_settings.value("/leNum2HiddenNN", "200").toString());
    ui->leNumOfHiddenLayersNN->setText(m_settings.value("/leNumOfHiddenLayersNN", "2").toString());
    ui->leA->setText(m_settings.value("/leA", "0.1").toString());
    ui->leE->setText(m_settings.value("/leE", "0.05").toString());
    ui->leAcceptError->setText(m_settings.value("/leAcceptError", "0.02").toString());
    m_settings.endGroup();
}

void Game::writeSettings() {
    m_settings.beginGroup("/Settings");
    m_settings.setValue("/leNum1HiddenNN", ui->leNum1HiddenNN->text());
    m_settings.setValue("/leNum2HiddenNN", ui->leNum2HiddenNN->text());
    m_settings.setValue("/leNumOfHiddenLayersNN", ui->leNumOfHiddenLayersNN->text());
    m_settings.setValue("/leA", ui->leA->text());
    m_settings.setValue("/leE", ui->leE->text());
    m_settings.setValue("/leAcceptError", ui->leAcceptError->text());
    m_settings.endGroup();
    if (m_pSnake->getNet()) m_pSnake->getNet()->training().saveWeightOfSynapses();
}

void Game::setTrainingParameters() {
    m_pSnake->getNet()->parameters().setA(ui->leA->text().toDouble());
    m_pSnake->getNet()->parameters().setE(ui->leE->text().toDouble());
    m_pSnake->setAcceptError(ui->leAcceptError->text().toDouble());
    m_pSnake->clearFiles(ui->cbNewTrainingData->checkState());
}

void Game::slotRunInfo() {
    ui->lblCountOfSets->setText(QString::number(m_pSnake->getNumTrainingSet()));
    ui->lblCountRun->setText(QString::number(m_pSnake->getNumTrainingSet() / m_pSnake->getNet()->getCountOfOutputs()));
    ui->lblCountOfSteps->setText(QString::number(m_pSnake->getStepCount()));
    ui->lblAverageCountOfSets->setText(QString::number(m_pSnake->getAverage(), 'f', 2));
    ui->lblErrorRun->setText(ui->leAcceptError->text());
    ui->lblCountOfEatenFruits->setText(QString::number(m_pSnake->getSnakeLength() - 3));
    slotStatusInfo("moving");
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
    //ui->lblStatus->setText("Змейка спит. Закончится обучение и она проснётся");
}

void Game::closeEvent(QCloseEvent* event)
{
    if (m_pSnake->getNet()) m_pSnake->stop();
    QApplication::quit();
    event->accept();
}

void Game::slotStatusInfo(const QString& status) {
    QString setStatus;
    if ( status == "learning") {
        setStatus = "Змейка спит. Закончится обучение и она проснётся";
    }
    if ( status == "moving" && ui->cbFreedom->checkState() ) {
        setStatus = "Змейка просто гуляет, опыт не получает";
    }
    if ( status == "moving" && !ui->cbFreedom->checkState() ) {
        setStatus = "Змейка получает опыт";
    }
    if ( (status == "stop") || (status == "moving" && !m_bStart) ) {
        setStatus = "Стоп";
    }
    if ( status == "start" ) {
        setStatus = "Старт";
    }

    ui->lblStatus->setText(setStatus);
}
