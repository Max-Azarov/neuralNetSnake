#ifndef CONSOLEMESSAGE_H
#define CONSOLEMESSAGE_H

#include <QString>
#include <QStringList>
#include <QDebug>

class LogOut {
private:
    static bool m_bShowConsole;
    static bool m_bPushToLogFile;
    LogOut() =delete;

public:
    enum TARGET {
        CONSOLE ,
        LOGFILE ,
        ALL
    };
private:

public:
    static void consoleLogOn() { m_bShowConsole = true; }
    static void consoleLogOff() { m_bShowConsole = false; }
    static void fileLogOn() { m_bPushToLogFile = true; }
    static void fileLogOff() { m_bPushToLogFile = false; }
    static void messageOut(const QString& message, bool bVisible = true, LogOut::TARGET target = CONSOLE);
    static void messageOut(const QString& message, LogOut::TARGET target);
};

#endif // CONSOLEMESSAGE_H
