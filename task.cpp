#include "task.h"

Task::Task()
{
    this->isComplete = false;
}

void Task::setId(int i){
    this->id = i;
}

void Task::setName(QString name){
    this->name = name;
}

void Task::setText(QString text){
    this->text = text;
}

void Task::setEndDate(QDate end_date){
    this->end_date = end_date;
}

void Task::setEndTime(QTime end_time){
    this->end_time = end_time;
}

void Task::setIsComplete(bool y){
    this->isComplete = y;
}

int Task::getId(){
    return this->id;
}

QString Task::getName(){
    return this->name;
}

QString Task::getText(){
    return this->text;
}

QDate Task::getEndDate(){
    return this->end_date;
}

QTime Task::getEndTime(){
    return this->end_time;
}

bool Task::getIsComplete(){
    return this->isComplete;
}
