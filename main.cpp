#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("My diary");
    w.setListWidget(QDate::currentDate());

    w.readTasks("/C++/Diarys/SaveTask");
    w.show();
    return a.exec();
}

