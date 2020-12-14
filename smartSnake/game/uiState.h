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

    // читает индекс и параметр типа обучения из UI, вызывает displayDefaultParameters(), создает нужный объект способа обучения в snake,
    virtual void readTypeOfLearning();
    virtual void setTypeOfLearning();
    virtual void cbNewWeightsStateChanged(int state);
    virtual void cbSnakeSpeedStateChanged(int state);
    virtual void displayDefaultParameters();

protected:
    Game* m_game;
    QSettings m_settings;
    Ui::MainWindow* ui;

protected:
    virtual void loadSettings();
    virtual void saveSettings();

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
};

// ==================== UIStateStart ==================
class UIStateStart : public IUIState {
public:
    UIStateStart(Game* game);
    ~UIStateStart() {
        LogOut::messageOut("delete UIStateStart");
    }

    void setUIStateStop() override;
};

#endif // GAMESTATE_H
