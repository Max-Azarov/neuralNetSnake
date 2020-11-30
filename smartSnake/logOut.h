#ifndef CONSOLEMESSAGE_H
#define CONSOLEMESSAGE_H

#include <QString>
#include <QStringList>
#include <QDebug>

class LogOut {
public:
    void messageOut(const void* const p, const QStringList&, const QString& target = "console");
};

#endif // CONSOLEMESSAGE_H
