#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>
#include <QDebug>

#include "ui_about.h"
#include "logOut.h"
#include "game.h"

#include <memory>

class Game;

class About : public QDialog {
    Q_OBJECT
public:
    About(Game* game);
    ~About() { LogOut::messageOut("delete About"); }

private slots:
    void on_btnOk_released();

private:
    std::unique_ptr<Ui::About> uiAbout;
    Game* m_pGame;

};

#endif // ABOUT_H
