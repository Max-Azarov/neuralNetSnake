#include "uiState.h"

// ==================== IUIState ==================
IUIState::IUIState(Game* game) : m_game { game }
  , m_settings {"monstr", "smartSnake", game }
{
    LogOut::messageOut("create IUIState");

    ui = m_game->getUI();
}

IUIState::~IUIState()
{
    saveSettings();
    LogOut::messageOut("delete IUIState");
}

void IUIState::loadSettings() {
    m_settings.beginGroup("/Settings");
    m_game->getUI()->leNumInputNN->setText(m_settings.value("/leNumInputNN", "-").toString());
    m_game->getUI()->leNumOutputNN->setText(m_settings.value("/leNumOutputNN", "-").toString());
    m_game->getUI()->leNum1HiddenNN->setText(m_settings.value("/leNum1HiddenNN", "100").toString());
    m_game->getUI()->leNum2HiddenNN->setText(m_settings.value("/leNum2HiddenNN", "200").toString());
    m_game->getUI()->leNumOfHiddenLayersNN->setText(m_settings.value("/leNumOfHiddenLayersNN", "2").toString());
    m_game->getUI()->leA->setText(m_settings.value("/leA", "0.1").toString());
    m_game->getUI()->leE->setText(m_settings.value("/leE", "0.05").toString());
    m_game->getUI()->leAcceptError->setText(m_settings.value("/leAcceptError", "0.02").toString());
    m_game->getUI()->cboLearningType->setCurrentIndex(m_settings.value("/cboLearningType", "0").toInt());
    m_game->getUI()->leLearningParam->setText(m_settings.value("/leParamLearning", "3").toString());
    m_game->getUI()->lblLearningParam->setText(m_settings.value("/lblParamLearning", "Размер области зрения вокруг головы").toString());
    m_settings.endGroup();
}

void IUIState::saveSettings() {
    m_settings.beginGroup("/Settings");
    m_settings.setValue("/leNumInputNN", m_game->getUI()->leNumInputNN->text());
    m_settings.setValue("/leNumOutputNN", m_game->getUI()->leNumOutputNN->text());
    m_settings.setValue("/leNum1HiddenNN", m_game->getUI()->leNum1HiddenNN->text());
    m_settings.setValue("/leNum2HiddenNN", m_game->getUI()->leNum2HiddenNN->text());
    m_settings.setValue("/leNumOfHiddenLayersNN", m_game->getUI()->leNumOfHiddenLayersNN->text());
    m_settings.setValue("/leA", m_game->getUI()->leA->text());
    m_settings.setValue("/leE", m_game->getUI()->leE->text());
    m_settings.setValue("/leAcceptError", m_game->getUI()->leAcceptError->text());
    m_settings.setValue("/cboLearningType", m_game->getUI()->cboLearningType->currentIndex());
    m_settings.setValue("/leParamLearning", m_game->getUI()->leLearningParam->text());
    m_settings.setValue("/lblParamLearning", m_game->getUI()->lblLearningParam->text());
    m_settings.endGroup();
    if ( m_game->getUI()->snake->getNet() ) m_game->getUI()->snake->getNet()->training().saveWeightOfSynapses();
}

void IUIState::readTypeOfLearning() {
    int index = ui->cboLearningType->currentIndex();
    int learningParam = ui->leLearningParam->text().toInt();
    switch (index) {
    case 0 :
        ui->snake->setLearningState1(learningParam);
        break;
    case 1:
        ui->snake->setLearningState2(learningParam);
        break;
    default:
        return;
    }
}

void IUIState::setTypeOfLearning() {
    int index = ui->cboLearningType->currentIndex();
    int learningParam = ui->leLearningParam->text().toInt();
    switch (index) {
    case 0 :
        ui->lblLearningParam->setText("Размер области зрения вокруг головы");
        ui->snake->setLearningState1(learningParam);
        break;
    case 1:
        ui->lblLearningParam->setText("Дальность зрения в каждую сторону");
        ui->snake->setLearningState2(learningParam);
        break;
    default:
        return;
    }

    displayDefaultParameters();
    ui->cbNewTrainingData->setCheckState(Qt::Checked);
    ui->cbNewWeights->setCheckState(Qt::Checked);
}

void IUIState::displayDefaultParameters() {
    size_t numOfInput = ui->snake->getNumOfInputsNN(); // валидно после вызова setLearningState
    size_t numOfOutput = ui->snake->getNumOfOutputsNN(); // валидно после вызова setLearningState
    ui->leNumInputNN->setText(QString::number(numOfInput)); // Записываем число входов в ячейку пользовательского окна
    ui->leNumOutputNN->setText(QString::number(numOfOutput)); // Записываем число выходов в ячейку пользовательского окна
    ui->leNum1HiddenNN->setText(QString::number(numOfInput + 2));
    ui->leNum2HiddenNN->setText(QString::number(numOfInput + 4));
    ui->leNumOfHiddenLayersNN->setText(QString::number(2));
}

void IUIState::cbNewWeightsStateChanged(int state) {
    if (state) {
        // Qt::checked
        ui->leNum1HiddenNN->setEnabled(true);
        ui->leNum2HiddenNN->setEnabled(true);
        ui->leNumOfHiddenLayersNN->setEnabled(true);
    }
    if (!state) {
        // Qt::unchecked
        ui->leNum1HiddenNN->setEnabled(false);
        ui->leNum2HiddenNN->setEnabled(false);
        ui->leNumOfHiddenLayersNN->setEnabled(false);
    }
}

void IUIState::cbSnakeSpeedStateChanged(int state) {
    ui->sldSnakeSpeed->setEnabled(!((bool)state));
    ui->leSnakeSpeed->setEnabled(!((bool)state));
}

void IUIState::statusInfo(const QString& status) {
    QString setStatus;
    if ( status == "learning") {
        setStatus = "Змейка спит. Закончится обучение и она проснётся";
    }
    if ( status == "moving" ) {
        setStatus = "Змейка получает опыт";
    }
    if ( status == "stop" ) {
        setStatus = "Стоп";
    }
    if ( status == "start" ) {
        setStatus = "Старт";
    }

    ui->lblStatus->setText(setStatus);
}

// <<  ==================== IUIState ==================


// ==================== UIStateBegin ==================
UIStateBegin::UIStateBegin(Game* game) : IUIState(game)
{
    LogOut::messageOut("create UIStateBegin");

    ui->setupUi(game);
    loadSettings();

    readTypeOfLearning();
}

void UIStateBegin::setUIStateStart() {
    m_game->pUIState.reset(new UIStateStart(m_game));
}

void UIStateBegin::setUIStateStop() {
    m_game->pUIState.reset(new UIStateStop(m_game));
}

// ==================== UIStateStop ==================
UIStateStop::UIStateStop(Game* game) : IUIState(game)
{
    LogOut::messageOut("create UIStateStop");

    ui->btnStart->setText("Старт");
    ui->gBoxNN->setEnabled(true);
    ui->gbTrainingSet->setEnabled(true);
    ui->cbNewWeights->setCheckState(Qt::Unchecked);
    ui->cbNewTrainingData->setCheckState(Qt::Unchecked);
    ui->cbFreedom->setEnabled(true);
    statusInfo("stop");
}

void UIStateStop::setUIStateStart() {
    m_game->pUIState.reset(new UIStateStart(m_game));
}

void UIStateStop::statusInfo(const QString& status) {
    QString setStatus;
    if ( status == "stop" ) {
        setStatus = "Стоп";
    }

    ui->lblStatus->setText(setStatus);
}

// ==================== UIStateStart ==================
UIStateStart::UIStateStart(Game* game) : IUIState(game)
{
    LogOut::messageOut("create UIStateStart");

    m_game->getUI()->btnStart->setText("Стоп");
    m_game->getUI()->gBoxNN->setEnabled(false);
    m_game->getUI()->gbTrainingSet->setEnabled(false);
    m_game->getUI()->leNum1HiddenNN->setText(m_game->getUI()->leNum1HiddenNN->text());
    m_game->getUI()->cbFreedom->setEnabled(false);
    statusInfo("start");
}

void UIStateStart::setUIStateStop() {
    m_game->pUIState.reset(new UIStateStop(m_game));
}

void UIStateStart::statusInfo(const QString& status) {
    QString setStatus;
    if ( status == "learning") {
        setStatus = "Змейка спит. Закончится обучение и она проснётся";
    }
    if ( status == "moving" ) {
        setStatus = "Змейка получает опыт";
    }
    if ( status == "start" ) {
        setStatus = "Старт";
    }

    ui->lblStatus->setText(setStatus);
}
