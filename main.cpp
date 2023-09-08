#include "mainwindow.h"
#include <QApplication>
#include <signal.h>
#include <qdebug.h>
MainWindow *w;

int stopped = 0;
void handleSigCount(int signal)
{
    w->raise();
    qDebug() << "handleSigCount:  Continue";
}

void handleSigUSR1(int signal)
{
    stopped = 1;
    qDebug() << "handleSigUSR1:  stopped. val = " << stopped;
}

void handleSigUSR2(int signal)
{
    stopped = 0;
    qDebug() << "handleSigUSR2:  started.  val = " << stopped;
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
    w = new MainWindow();
    w->show();
    signal(SIGCONT,handleSigCount);
    signal(SIGUSR1,handleSigUSR1);
    signal(SIGUSR2,handleSigUSR2);
    return a.exec();
}
