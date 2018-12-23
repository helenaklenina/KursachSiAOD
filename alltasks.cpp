#include "alltasks.h"
#include "ui_alltasks.h"

AllTasks::AllTasks(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AllTasks)
{
    ui->setupUi(this);
    moreAboutTask_window = new MoreAboutTask(this);
    connect(moreAboutTask_window, &MoreAboutTask::showWindow, this, &AllTasks::slot);

}

AllTasks::~AllTasks()
{
    delete ui;
}

void AllTasks::slot(){
    AllTasks::show();
    setListWidget();
}

void AllTasks::setAllTasks(std::vector <Task> *all_tasks){
    this->all_tasks = all_tasks;
    setListWidget();
}

QString AllTasks::cleanName(QString name){
    QString new_name;
    for (int i = 18; i < name.size(); i++){
        new_name += name[i];
    }
    return new_name;
}

int AllTasks::searchTrueTask (QString item){
    QString name = cleanName(item);
    for (int i = 0; i < all_tasks->size(); i++){
        if (name == (*all_tasks)[i].getName()){
            return i;
        }
    }
}

void AllTasks::setListWidget(){
    ui->completeTask->clear();
    ui->notCompleteTask->clear();
    ui->overdueTask->clear();
    for (int i = 0; i < all_tasks->size(); i++){
        if((*all_tasks)[i].getEndDate() > QDate::currentDate() && (*all_tasks)[i].getIsComplete() == false){
            QString item = (*all_tasks)[i].getEndDate().toString()  + "|   " + (*all_tasks)[i].getName();
            ui->notCompleteTask->addItem(item);
        } else if((*all_tasks)[i].getIsComplete() == true){
            QString item = (*all_tasks)[i].getEndDate().toString()  + "|   " + (*all_tasks)[i].getName();
            ui->completeTask->addItem(item);
        } else if(((*all_tasks)[i].getIsComplete() == false && (*all_tasks)[i].getEndDate() < QDate::currentDate()) ||
                  (( *all_tasks)[i].getEndDate() == QDate::currentDate() && (*all_tasks)[i].getEndTime() < QTime::currentTime())){
            QString item = (*all_tasks)[i].getEndDate().toString()  + "|   " + (*all_tasks)[i].getName();
            ui->overdueTask->addItem(item);
        }
    }
}


void AllTasks::on_pushButton_2_clicked()
{
    if(ui->overdueTask->currentItem() || ui->completeTask->currentItem() || ui->notCompleteTask->currentItem()){
        QMessageBox del(QMessageBox::Question,
                    tr("Удаление"),
                    tr("Вы действительно хотите удалить задачу?"),
                    QMessageBox::Yes | QMessageBox::No,
                    this);
            del.setButtonText(QMessageBox::Yes, tr("Да"));
            del.setButtonText(QMessageBox::No, tr("Нет"));

        if (del.exec() == QMessageBox::Yes){
            if(ui->overdueTask->currentItem()){
                QString item = ui->overdueTask->currentItem()->text();
                int i = searchTrueTask(item);
                int j = i;
                for (; j < all_tasks->size() - 1; j++){
                    (*all_tasks)[j] = (*all_tasks)[j + 1];
                }
                all_tasks->resize(j);
                setListWidget();
            } else if(ui->completeTask->currentItem()){
                QString item = ui->completeTask->currentItem()->text();
                int i = searchTrueTask(item);
                int j = i;
                for (; j < all_tasks->size() - 1; j++){
                    (*all_tasks)[j] = (*all_tasks)[j + 1];
                }
                all_tasks->resize(j);
                setListWidget();
            } else if(ui->notCompleteTask->currentItem()){
                QString item = ui->notCompleteTask->currentItem()->text();
                int i = searchTrueTask(item);
                int j = i;
                for (; j < all_tasks->size() - 1; j++){
                    (*all_tasks)[j] = (*all_tasks)[j + 1];
                }
                all_tasks->resize(j);
                setListWidget();
            }
        }
    } else {
        QMessageBox::warning(this, "Сообщение", "Вы не выбрали задачу!");
    }
}

void AllTasks::on_notCompleteTask_itemDoubleClicked(QListWidgetItem *item)
{
    Task * newTask = &((*all_tasks)[searchTrueTask((*item).text())]);
    moreAboutTask_window->setDataToForms(newTask, all_tasks);
    moreAboutTask_window->setWindowTitle("My diary");
    moreAboutTask_window->setI();
    moreAboutTask_window->show();
    this->close();
}

void AllTasks::on_completeTask_itemDoubleClicked(QListWidgetItem *item)
{
    moreAboutTask_window = new MoreAboutTask(this);
    Task * newTask = &((*all_tasks)[searchTrueTask((*item).text())]);
    moreAboutTask_window->setDataToForms(newTask, all_tasks);
    moreAboutTask_window->setWindowTitle("My diary");
    moreAboutTask_window->setI();
    moreAboutTask_window->show();
    this->close();
}

void AllTasks::on_overdueTask_itemDoubleClicked(QListWidgetItem *item)
{
    moreAboutTask_window = new MoreAboutTask(this);
    Task * newTask = &((*all_tasks)[searchTrueTask((*item).text())]);
    moreAboutTask_window->setDataToForms(newTask, all_tasks);
    moreAboutTask_window->setWindowTitle("My diary");
    moreAboutTask_window->setI();
    moreAboutTask_window->show();
    this->close();
}


