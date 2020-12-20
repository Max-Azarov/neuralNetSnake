#include "about.h"


About::About(Game* game) : QDialog(nullptr, Qt::WindowTitleHint | Qt::WindowSystemMenuHint)
  , uiAbout { new Ui::About }
  , m_pGame { game }
{
    LogOut::messageOut("create About");

    uiAbout->setupUi(this);
    this->show();
}

void About::on_btnOk_released() {
    m_pGame->closeAbout();
}
