#ifndef TASK_H
#define TASK_H
#include <QString>
#include <QDate>
#include <QTime>

class Task{
private:
    int id;
    QString name;
    QString text;
    QDate end_date;
    QTime end_time;
    bool isComplete;
public:
    Task();
    void setId(int);
    void setName(QString);
    void setText(QString);
    void setEndDate(QDate);
    void setEndTime(QTime);
    void setIsComplete(bool);
    int getId();
    QString getName();
    QString getText();
    QDate getEndDate();
    QTime getEndTime();
    bool getIsComplete();
};

#endif // TASK_H
