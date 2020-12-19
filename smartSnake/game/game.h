#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <memory>

#include <QtWidgets>
#include <QSettings>
#include <QValidator>
#include "snake/snake.h"
#include "ui_mainWindow.h"
#include "about.h"
#include "uiState.h"

class IUIState;

class Game : public QMainWindow
{
    Q_OBJECT
private:
    std::unique_ptr<Ui::MainWindow> ui;
    std::unique_ptr<About> m_pAbout;

    Snake* m_pSnake;
    bool m_bStart;
    int m_delay;
    bool m_bIsInitNet;
    QStringList m_infoCount;
    QStringList m_infoError;
    bool m_bNewSynapseWeights;
    bool m_clearFiles;

public:
    Game(QWidget *parent = nullptr);
    virtual ~Game();// { writeSettings(); delete ui; }

    std::unique_ptr<IUIState> pUIState;
    Ui::MainWindow* getUI() const { return ui.get(); }
    Snake* getSnake() const { return  (m_pSnake ? m_pSnake : nullptr); }

private slots:
    void on_sldSnakeSpeed_valueChanged(int);
    void on_sldSnakeSpeed_sliderReleased();
    //void on_sldSnakeSpeed_sliderPressed();
    void on_btnStart_released();

    void on_leSnakeSpeed_editingFinished();
    void on_cbSnakeSpeed_stateChanged(int state);

    void on_leNum1HiddenNN_editingFinished();
    void on_leNum2HiddenNN_editingFinished();
    void on_leNumOfHiddenLayersNN_editingFinished();
    void on_leLearningParam_editingFinished();
    void on_cbNewWeights_stateChanged(int state);
    void on_cbNewTrainingData_stateChanged(int state);
    void on_cboLearningType_currentIndexChanged(int index);
    void on_cboLearningType_activated(int index);
    void slotRunInfo();
    void slotErrorInfo();

public slots:
    void slotStatusInfo(const QString&);

private:
    void setSnakeSpeed(int);
    void setSnakeSpeed();
    void initNet();
    void setTrainingParameters();
    void intValidate(QLineEdit* const le, const QString& valueForInvalid);

    void setUIStateStop();
    void setUIStateStart();

//public slots:


protected:
    void closeEvent(QCloseEvent* event);
};

#endif // GAMEWINDOW_H
