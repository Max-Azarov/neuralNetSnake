#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QtWidgets>
#include <QSettings>
#include <QValidator>
#include "snake.h"
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

public:
    Game(QWidget *parent = nullptr);
    virtual ~Game() { writeSettings(); delete ui; }

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
    void on_cbNewWeights_stateChanged(int state);

private:
    void setSnakeSpeed(int);
    void setSnakeSpeed();
    void initNet();
    void readSettings();
    void writeSettings();
    void setTrainingParameters();
    void intValidate(QLineEdit* const le, const QString& valueForInvalid);

public slots:
    void slotRunInfo();
    void slotErrorInfo();
};

#endif // GAMEWINDOW_H
