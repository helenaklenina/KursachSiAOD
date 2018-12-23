#include "diary.h"

void Diary::setIdDiary(int id){
    this->idDiary = id;
}
void Diary::setNameDiary(QString named){
    this->nameDiary = named;
}

int Diary::getIdDiary(){
    return this->idDiary;
}

QString Diary::getNameDiary(){
    return this->nameDiary;
}
