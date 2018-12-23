#ifndef DIARY_H
#define DIARY_H
#include <QString>

class Diary
{
private:
    int idDiary;
    QString nameDiary;
public:
    Diary();
    void setIdDiary(int);
    void setNameDiary(QString);
    int getIdDiary();
    QString getNameDiary();
};

#endif // DIARY_H
