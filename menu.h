#ifndef MENU_H
#define MENU_H

#include <QDialog>
#include <QListWidgetItem>
#include "mainwindow.h"

namespace Ui {
class Menu;
}

class Menu : public QDialog
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr);
    ~Menu();

private slots:
    void menu_slot();
    void on_pushButton_clicked();

private:
    Ui::Menu *ui;
    MainWindow *main_window;
};

#endif // MENU_H
