#include <list>
#include <QPushButton>

#include "game.h"

Game::Game(QWidget *parent) :
    QMainWindow{parent},
    ui{ new Ui::MainWindow }
{
    ui->setupUi(this);
    snake = ui->snake;
    //connect(ui->sldSnakeSpeed )
}

void Game::on_sldSnakeSpeed_valueChanged(int value) {
    //slider
    ui->leSnakeSpeed->setText(QString::number(value));
    setSnakeSpeed(value);
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
        ui->sldSnakeSpeed->setEnabled(true);
        ui->leSnakeSpeed->setEnabled(true);
        setSnakeSpeed(ui->sldSnakeSpeed->value());
    }
}

void Game::setSnakeSpeed(int speed) {
    int delay;
    int num_msInSec = 1000;
    speed = (speed <= 0) ? 1 : speed;
    delay = num_msInSec / speed;
    snake->setDelay(delay);
}
