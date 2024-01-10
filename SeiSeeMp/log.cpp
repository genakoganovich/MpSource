#include "log.h"
#include <QFile>
#include <QDateTime>
#include <QTextStream>


void Util::messageToFile(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
    QFile file("protocol.log");
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
        return;
    QString strDateTime = QDateTime::currentDateTime().toString("dd.MM.yy-hh:mm ");
    QTextStream out(&file);
    switch (type) {
        case QtDebugMsg:
            out << strDateTime << "Debug: " << msg << ", " << context.file << endl;
            break;
        case QtWarningMsg:
                out << strDateTime << "Warning: " << msg << ", " << context.file << endl;
                break;
        case QtCriticalMsg:
                out << strDateTime << "Critical: " << msg << ", " << context.file << endl;
                break;
        case QtFatalMsg:
            out << strDateTime << "Fatal: " << msg << ", " << context. file << endl;
            abort();
    }
}
