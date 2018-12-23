#include "addnewtask.h"
#include "ui_addnewtask.h"

AddNewTask::AddNewTask(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddNewTask)
{
    ui->setupUi(this);
    y = false;
}

AddNewTask::~AddNewTask()
{
    delete ui;
}

void AddNewTask::setAllTasks(std::vector <Task> *all_tasks){// при добавлении
    this->all_tasks = all_tasks;
    ui->lineEdit_4->clear();
    ui->textEdit->clear();
    ui->dateEdit_4->setDate(QDate::currentDate());
    ui->timeEdit_4->setTime(QTime::currentTime());
    ui->dateEdit_4->setMinimumDate(QDate::currentDate());
}

void AddNewTask::setTask(Task* task, std::vector <Task> * tasks){ //при редактировании
    this->task = task;
    this->all_tasks = tasks;
    y = true;
    ui->lineEdit_4->setText((*this->task).getName());
    ui->textEdit->setPlainText((*this->task).getText());
    ui->dateEdit_4->setDate((*this->task).getEndDate());
    ui->timeEdit_4->setTime((*this->task).getEndTime());
}

void AddNewTask::on_pushButton_clicked()
{
    int k = 0;
    int l = 0;
    if (y == true){
        for (int i = 0; i < all_tasks->size(); i++){ // Для редактирования существующей заметки
            if (ui->lineEdit_4->text() == (*all_tasks)[i].getName() && (*task).getId() != (*all_tasks)[i].getId()){
                l++;
                break;
            }
        }
    } else {
        for (int i = 0; i < all_tasks->size(); i++){// Для редактирования новой заметки
            if (ui->lineEdit_4->text() == (*all_tasks)[i].getName()){
                k++;
                break;
            }
        }
    }
    if(this->editFlag != 0 && ui->textEdit->toPlainText() != "" && ui->lineEdit_4->text() != "") { // Редактирование существующей заметки
        if (l == 0){
            if (ui->dateEdit_4->date() >= QDate::currentDate()){
                this->task->setName(ui->lineEdit_4->text());
                this->task->setText(ui->textEdit->toPlainText());
                this->task->setEndDate(ui->dateEdit_4->date());
                this->task->setEndTime(ui->timeEdit_4->time());
                this->close();
            } else {
                QMessageBox exit(QMessageBox::Question,
                            tr("Ошибка"),
                            tr("Дата дэдлайна установлена раньше текущей.\nХотите ввести заново?"),
                            QMessageBox::Yes | QMessageBox::No,
                            this);
                    exit.setButtonText(QMessageBox::Yes, tr("Да"));
                    exit.setButtonText(QMessageBox::No, tr("Нет"));

                if (exit.exec() == QMessageBox::No){
                    this->close();
                }
                ui->dateEdit_4->setDate(QDate::currentDate());
            }

        } else {
            QMessageBox exit(QMessageBox::Question,
                        tr("Ошибка"),
                        tr("Такое имя уже существует.\nХотите ввести заново?"),
                        QMessageBox::Yes | QMessageBox::No,
                        this);
                exit.setButtonText(QMessageBox::Yes, tr("Да"));
                exit.setButtonText(QMessageBox::No, tr("Нет"));

            if (exit.exec() == QMessageBox::No){
                this->close();
            }
            ui->lineEdit_4->setText((*this->task).getName());
        }

    }
    else if(ui->textEdit->toPlainText() != "" && ui->lineEdit_4->text() != "" && this->editFlag == 0) { // добавление новой заметки
        if (k == 0){
            Task task;
            task.setName(ui->lineEdit_4->text());
            task.setText(ui->textEdit->toPlainText());
            task.setDate(this->date);
            task.setEndDate(ui->dateEdit_4->date());
            task.setEndTime(ui->timeEdit_4->time());
            task.setId(all_tasks->size());
            all_tasks->push_back(task);
            this->close();
        } else {
            QMessageBox exit(QMessageBox::Question,
                        tr("Ошибка"),
                        tr("Такое имя уже существует.\nХотите ввести заново?"),
                        QMessageBox::Yes | QMessageBox::No,
                        this);
                exit.setButtonText(QMessageBox::Yes, tr("Да"));
                exit.setButtonText(QMessageBox::No, tr("Нет"));

            if (exit.exec() == QMessageBox::No){
                this->close();
            }
            ui->lineEdit_4->clear();
        }

    }
    else{
        QMessageBox exit(QMessageBox::Question,
                    tr("Ошибка"),
                    tr("Вы не ввели данные в текстовые поля.\nХотите ввести?"),
                    QMessageBox::Yes | QMessageBox::No,
                    this);
            exit.setButtonText(QMessageBox::Yes, tr("Да"));
            exit.setButtonText(QMessageBox::No, tr("Нет"));

        if (exit.exec() == QMessageBox::No){
            this->close();
        }
    }
    emit firstWindow();
}

void AddNewTask::on_lineEdit_textEdited(const QString &arg1){

}

void AddNewTask::setCurrentEndDateTime(QDate date){
    this->date = date;
    ui->dateEdit_4->setDate(QDate::currentDate()); // sets the current date to date edit.
    ui->timeEdit_4->setTime(QTime::currentTime());
}

