#include <list>
#include <QPushButton>

#include "game.h"

Game::Game(QWidget *parent) :
    QMainWindow{parent},
    ui{ new Ui::MainWindow },
    m_bStart {false}
{
    ui->setupUi(this);
    snake = ui->snake;
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

void Game::on_leSnakeSpeed_returnPressed() {
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
        setSnakeSpeed(1000);
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
        snake->stop();
        ui->btnStart->setText("Старт");
        ui->gBoxNN->setEnabled(true);
        ui->gbTrainingSet->setEnabled(true);
        ui->cbSnakeSpeed->setEnabled(false);
    }
    else {
        // Текущее состояние "Стоп"
        m_bStart = true;
        setSnakeSpeed();
        snake->start();
        on_sldSnakeSpeed_sliderReleased();
        ui->btnStart->setText("Стоп");
        ui->gBoxNN->setEnabled(false);
        ui->gbTrainingSet->setEnabled(false);
        ui->cbSnakeSpeed->setEnabled(true);
    }
}

void Game::setSnakeSpeed(int speed) {
    int num_msInSec = 1000;
    speed = (speed <= 0) ? 1 : speed;
    m_delay = num_msInSec / speed;
    if (m_bStart) {
        snake->setDelay(m_delay);
    }
}

void Game::setSnakeSpeed() {
    int num_msInSec = 1000;
    int speed = ui->sldSnakeSpeed->value();
    m_delay = num_msInSec / speed;
    if (m_bStart) {
        snake->setDelay(m_delay);
    }
}
