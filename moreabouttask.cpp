#include "moreabouttask.h"
#include "ui_moreabouttask.h"

MoreAboutTask::MoreAboutTask(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MoreAboutTask)
{
    ui->setupUi(this);
    editTask_window = new AddNewTask(this);
    connect(editTask_window, &AddNewTask::firstWindow, this, &MoreAboutTask::slot);
}

MoreAboutTask::~MoreAboutTask()
{
    delete ui;
}

void MoreAboutTask::slot(){
    emit firstWindow();
    emit showWindow();
}

void MoreAboutTask::setI(){
    this->i = 1;
}

void MoreAboutTask::closeEvent(QCloseEvent *event)
{
    if (this->i != 0){
        MoreAboutTask::close();
        emit showWindow();
    }

}

void MoreAboutTask::on_pushButton_clicked()
{
    editTask_window->editFlag = -1;
    editTask_window->setTask(this->task, this->all_tasks);
    editTask_window->setWindowTitle("My datebook");
    editTask_window->show();
    this->close();

}

void MoreAboutTask::setDataToForms(Task *task, std::vector <Task> *tasks){
    this->task = task;
    this->all_tasks = tasks;
    if((*task).getIsComplete()){
        ui->textEdit_name->setPlainText((*task).getName() + " (выполнено)");
    } else {
        ui->textEdit_name->setPlainText((*task).getName());
    }
    ui->textEdit_creatingDate->setPlainText((*task).getDate().toString());
    ui->textEdit_text->setPlainText((*task).getText());
    ui->textEdit_endDate->setPlainText((*task).getEndDate().toString());
    ui->textEdit_endTime->setPlainText((*task).getEndTime().toString());
}
