#ifndef ADDNEWDIARY_H
#define ADDNEWDIARY_H

#include <QDialog>

namespace Ui {
class AddNewDiary;
}

class AddNewDiary : public QDialog
{
    Q_OBJECT

public:
    explicit AddNewDiary(QWidget *parent = nullptr);
    ~AddNewDiary();

private:
    Ui::AddNewDiary *ui;
};

#endif // ADDNEWDIARY_H
