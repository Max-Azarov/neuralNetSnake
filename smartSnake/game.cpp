#include <list>
#include <QPushButton>

#include "game.h"

Game::Game(QWidget *parent) :
    QMainWindow{parent},
    ui{new Ui::MainWindow}
{
    ui->setupUi(this);
    //connect(ui->sldSnakeSpeed )
}

void Game::on_sldSnakeSpeed_sliderMoved(int speed) {
    //slider
    ui->leSnakeSpeed->setText(QString::number(speed));
}

void Game::on_leSnakeSpeed_returnPressed() {
    ui->sldSnakeSpeed->setValue(ui->leSnakeSpeed->text().toInt());
    ui->leSnakeSpeed->setText(QString::number(ui->sldSnakeSpeed->value()));
}

void Game::setSnakeSpeed(int speed) {
    int delay;
    int num_msInSec = 1000;
    delay = num_msInSec / speed;
    //ui->snake
}
