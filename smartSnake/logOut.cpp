#include "logOut.h"

void LogOut::messageOut(const void* const p, const QStringList& message, const QString& target) {
    if (target == "console") {
        qDebug() << p << message;
    }
}
