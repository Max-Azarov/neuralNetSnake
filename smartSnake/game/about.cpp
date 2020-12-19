#include "about.h"


About::About() : QDialog(nullptr, Qt::WindowTitleHint | Qt::WindowSystemMenuHint)
    ,  uiDialog { new Ui::Dialog }
{
    LogOut::messageOut("create About");
    uiDialog->setupUi(this);
    QString info {"Hello!"};
    uiDialog->lblInfo->setText(info);
}

void About::on_btnOk_released() {
    this->close();
}
