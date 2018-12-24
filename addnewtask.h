#ifndef ADDNEWTASK_H
#define ADDNEWTASK_H

#include <QMainWindow>
#include <QDebug>
#include <QDate>
#include <QTime>
#include <QMessageBox>
#include <QListWidget>
#include <functional>
#include <vector>
#include "task.h"
namespace Ui {
class AddNewTask;
}

class AddNewTask : public QDialog
{
    Q_OBJECT

public:
    int editFlag = 0;
    explicit AddNewTask(QWidget *parent = nullptr);
    ~AddNewTask();


    void setAllTasks(std::vector <Task>*);
    void setCurrentEndDateTime(QDate);
    void setTask(Task*, std::vector <Task> *);


private slots:
    void on_pushButton_clicked();

signals:
    void firstWindow();

private:
    Ui::AddNewTask *ui;
    std::vector <Task> *all_tasks;
    QDate date;
    Task *task;
    bool y;
};

#endif // ADDNEWTASK_H
