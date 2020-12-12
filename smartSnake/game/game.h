#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QtWidgets>
#include <QSettings>
#include <QValidator>
#include "snake/snake.h"
#include "ui_mainWindow.h"

class Game : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow* ui;
    Snake* m_pSnake;
    bool m_bStart;
    int m_delay;
    bool m_bIsInitNet;
    QSettings m_settings;
    QStringList m_infoCount;
    QStringList m_infoError;
    bool m_bNewSynapseWeights;
    bool m_load; // Закончилось ли выполнение конструктора (загрузка объекта)

public:
    Game(QWidget *parent = nullptr);
    virtual ~Game();// { writeSettings(); delete ui; }

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
    void on_leParamLearning_editingFinished();
    void on_cbNewWeights_stateChanged(int state);
    void on_cbNewTrainingData_stateChanged(int state);
    void on_cboLearningType_currentIndexChanged(int index);
    void slotRunInfo();
    void slotErrorInfo();
    void slotStatusInfo(const QString&);

private:
    void setSnakeSpeed(int);
    void setSnakeSpeed();
    void initNet();
    void loadSettings();
    void saveSettings();
    void setTrainingParameters();
    void intValidate(QLineEdit* const le, const QString& valueForInvalid);
    void displayDefaultParameters();
    void changeTypeOfLearning(int index, int learningParam);

//public slots:


protected:
    void closeEvent(QCloseEvent* event);
};

#endif // GAMEWINDOW_H
