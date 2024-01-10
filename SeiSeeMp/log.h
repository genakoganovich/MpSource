#ifndef LOG_H
#define LOG_H

#include <QtGlobal>


class Util {
public:
    static void messageToFile(QtMsgType type, const QMessageLogContext& context, const QString& msg);
};

#endif // LOG_H
