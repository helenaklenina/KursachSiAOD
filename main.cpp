#include "mainwindow.h"
#include "menu.h"
#include <QApplication>
#include <QDate>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
   // Menu menu;
  //  menu.setWindowTitle("My diary");
    w.setWindowTitle("My diary");
    w.setListWidget(QDate::currentDate());
    w.readTasks();
    w.show();
    return a.exec();
}

