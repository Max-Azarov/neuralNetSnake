#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>
#include <QDebug>

#include "ui_about.h"
#include "logOut.h"

#include <memory>

class About : public QDialog {
    Q_OBJECT
public:
    About();
    ~About() { LogOut::messageOut("delete About"); }

private slots:
    void on_btnOk_released();

private:
    std::unique_ptr<Ui::Dialog> uiDialog;

};

#endif // ABOUT_H
