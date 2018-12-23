#ifndef ALLTASKS_H
#define ALLTASKS_H

#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include "moreabouttask.h"
#include "task.h"
#include <vector>

namespace Ui {
class AllTasks;
}

class AllTasks : public QDialog
{
    Q_OBJECT

public:
    explicit AllTasks(QWidget *parent = 0);
    ~AllTasks();
    void setAllTasks(std::vector <Task>*);
    QString cleanName(QString);
    int searchTrueTask (QString);
    void setListWidget();
    void slot();

private slots:
    void on_pushButton_2_clicked();

    void on_completeTask_itemDoubleClicked(QListWidgetItem *item);

    void on_overdueTask_itemDoubleClicked(QListWidgetItem *item);

    void on_notCompleteTask_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::AllTasks *ui;
    std::vector <Task> *all_tasks;
    MoreAboutTask *moreAboutTask_window;
};

#endif // ALLTASKS_H
