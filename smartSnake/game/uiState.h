#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "game/game.h"
#include "logOut.h"
#include "ui_mainWindow.h"

#include <QSettings>

class Game;

// ==================== IUIState ==================
class IUIState {

private:
    IUIState(const IUIState&) = delete;
    IUIState& operator= (const IUIState&) = delete;
    IUIState(IUIState&&) = delete;
    IUIState& operator= (IUIState&&) = delete;

public:
    IUIState(Game* game);
    virtual ~IUIState();

public:
    virtual void setUIStateStop() {}
    virtual void setUIStateStart() {}


    virtual void readTypeOfLearning();// читает индекс и параметр типа обучения из UI создает нужный объект способа обучения в snake
    virtual void setTypeOfLearning();// читает индекс и параметр типа обучения из UI, вызывает displayDefaultParameters(), создает нужный объект способа обучения в snake
    virtual void cbNewWeightsStateChanged(int state);
    virtual void cbSnakeSpeedStateChanged(int state);

    virtual void statusInfo(const QString& status);

protected:
    Game* m_game;
    QSettings m_settings;
    Ui::MainWindow* ui;

protected:
    virtual void loadSettings();
    virtual void saveSettings();
    virtual void displayDefaultParameters();

};

// ==================== UIStateBegin ==================
class UIStateBegin : public IUIState {
public:
    UIStateBegin(Game* game);
    ~UIStateBegin() {
        LogOut::messageOut("delete UIStateBegin");
    }

    void setUIStateStop() override;
    void setUIStateStart() override;
};

// ==================== UIStateStop ==================
class UIStateStop : public IUIState {
public:
    UIStateStop(Game* game);
    ~UIStateStop() {
        LogOut::messageOut("delete UIStateStop");
    }

    void setUIStateStart() override;
    void statusInfo(const QString& status) override;
};

// ==================== UIStateStart ==================
class UIStateStart : public IUIState {
public:
    UIStateStart(Game* game);
    ~UIStateStart() {
        LogOut::messageOut("delete UIStateStart");
    }

    void setUIStateStop() override;
    void statusInfo(const QString& status) override;
};

#endif // GAMESTATE_H
