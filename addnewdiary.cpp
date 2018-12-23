#include "addnewdiary.h"
#include "ui_addnewdiary.h"

AddNewDiary::AddNewDiary(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddNewDiary)
{
    ui->setupUi(this);
}

AddNewDiary::~AddNewDiary()
{
    delete ui;
}
