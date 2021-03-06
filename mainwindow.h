#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QMessageBox>
#include <QDate>
#include <QListWidgetItem>
#include <QTextCharFormat>
#include <vector>
#include <QDebug>
#include <functional>
#include <QFile>
#include <QDataStream>
#include <QRect>
#include <QTextStream>
#include <QTextCodec>
#include <QDir>
#include <QCloseEvent>
#include "alltasks.h"
#include "addnewtask.h"
#include "moreabouttask.h"
#include "task.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //void setAllTasks(std::vector <Task>);
    void testFunction();
    bool isCurrentDate(QDate);
    void setListWidget(QDate);
    QString cleanName(QString);
    int searchTrueTask (QString);
    void calendar_color(QDate);
    void return_calendar_color(QDate);
    void sortAllTasks();
    void deleteCompletedTasks();
    void saveTasks(const QString &FILE_PATH);
    void readTasks(const QString &FILE_PATH);
    void setTrueId();
    bool removeDir (const QString &path);
    void closeEvent(QCloseEvent *);
    void slot();   
    void deleteDiary();

private slots:

    void on_pushButton_show_clicked();

    void on_add_clicked();

    void on_complete_clicked();

    void on_exit_2_triggered();

    void on_delete_2_clicked();

    void on_calendarWidget_clicked(const QDate &date);

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_create_Diary_2_triggered();

    void on_save_2_triggered();

    void on_clear_triggered();

private:
    Ui::MainWindow *ui;
    std::vector <Task> all_tasks;
    AddNewTask * newTask_window;
    AllTasks *allTasks_window;
    MoreAboutTask *moreAboutTask_window;
    QDate date = QDate::currentDate();
    QString file_path = "/C++/Diarys/SaveTaskNEW";
    QString DIR_NAME = "/C++/Diarys/SaveTask";
    bool isExit = false;
    bool NewDiary = true;
};

#endif // MAINWINDOW_H
