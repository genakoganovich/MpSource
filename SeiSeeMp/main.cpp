#include "mainwindow.h"
#include <QApplication>
#include "log.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qInstallMessageHandler(Util::messageToFile);
    qDebug("Hello log");
    MainWindow w;
    w.show();
    
    return a.exec();
}
