#include "logOut.h"

bool LogOut::m_bShowConsole = true;
bool LogOut::m_bPushToLogFile = true;

void LogOut::messageOut( const QString& message, bool bVisible, LogOut::TARGET target) {
    if (bVisible) {
        messageOut(message, target);
    }
}

void LogOut::messageOut( const QString& message, LogOut::TARGET target) {
    switch (target) {
    case CONSOLE :
        if (m_bShowConsole) qDebug() << message;
        break;
    case LOGFILE :
        if (m_bPushToLogFile) qDebug() << message; // Необходимо поменять на вывод в файл
        break;
    case ALL :
        if (m_bShowConsole) qDebug() << message;
        if (m_bPushToLogFile) qDebug() << message; // Необходимо поменять на вывод в файл
        break;
    default:;
    }
}
