#ifndef MOREABOUTTASK_H
#define MOREABOUTTASK_H

#include <QDialog>
#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QDebug>
#include <vector>
#include "addnewtask.h"
#include "task.h"

namespace Ui {
class MoreAboutTask;
}

class MoreAboutTask : public QDialog
{
    Q_OBJECT

public:
    explicit MoreAboutTask(QWidget *parent = 0);
    ~MoreAboutTask();
    void setDataToForms(Task*, std::vector <Task> *);
    void setI();
    void slot();
    void closeEvent(QCloseEvent *);

private slots:
    void on_pushButton_clicked();

signals:
    void firstWindow();
    void showWindow();

private:
    Ui::MoreAboutTask *ui;
    Task *task;
    std::vector <Task> * all_tasks;
    AddNewTask *editTask_window;
    int i = 0;
};

#endif // MOREABOUTTASK_H
