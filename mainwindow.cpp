#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    newTask_window = new AddNewTask(this);
    connect(newTask_window, &AddNewTask::firstWindow, this, &MainWindow::slot);
    moreAboutTask_window = new MoreAboutTask(this);
    connect(moreAboutTask_window, &MoreAboutTask::firstWindow, this, &MainWindow::slot);
    //moreAboutTask_window = new MoreAboutTask(this);
   // connect(this, on_createDiary_clicked(), this, show()));
    this->DIR_NAME = "/C++/Diarys/SaveTask";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot(){
    MainWindow::activateWindow();
    on_calendarWidget_clicked(this->date);
}

void MainWindow::testFunction(){
    qDebug() << all_tasks[0].getName() << "     " << all_tasks[0].getEndDate().toString() << "     " << all_tasks[1].getName() << "     " << all_tasks[1].getEndDate().toString() ;
}

QString MainWindow::cleanName(QString name){
    int i = 0;
    for (;i < name.size(); i ++){
        if(name[i] == '.'){
            break;
        }
    }

    QString new_name(name[i + 4]);
    QString check_name = " ";
    if (name.size() > 12){
         for(int k = name.size() - 11; k < name.size(); k++){
             check_name += name[k];
         }
    }
    if (check_name == " (выполнено)"){
        for (int j = i + 5; j < name.size() - 12; j++){
            new_name += name[j];
        }
    } else{
        for (int j = i + 5; j < name.size(); j++){
            new_name += name[j];
        }
    }
    return new_name;
}

int MainWindow::searchTrueTask (QString item){
    QString name = cleanName(item);
    for (int i = 0; i < all_tasks.size(); i++){
        if ((this->date == all_tasks[i].getEndDate()) && (name == all_tasks[i].getName())){
            return i;
        }
    }
}

bool MainWindow::isCurrentDate(QDate date){
    for (int i = 0; i < all_tasks.size(); i++){
        if(all_tasks[i].getEndDate() == date){
            return true;
        }
    }
    return false;
}

void MainWindow::setListWidget(QDate date){
    ui->listWidget->clear();
    sortAllTasks();
    int k = 0;
    for (int i = 0; i < all_tasks.size(); i++){
        if(all_tasks[i].getEndDate() == date && all_tasks[i].getIsComplete() == false){
            k++;
            QString item = QString::number(k) + ".   " + all_tasks[i].getName();
            ui->listWidget->addItem(item);

        } else if (all_tasks[i].getEndDate() == date && all_tasks[i].getIsComplete() == true){
            k++;
            QString item = QString::number(k) + ".   " + all_tasks[i].getName() + " (выполнено)";
            ui->listWidget->addItem(item);

        }
    }
    if (k > 0){
        calendar_color(date);
    } else if (k == 0){
         return_calendar_color(date);
    }
}

void MainWindow::calendar_color(QDate d) { // календарь будет закрашивать дату последней созданной заметки
    QTextCharFormat format = ui->calendarWidget->dateTextFormat(d); // закрашивание ячейки календаря
    format.setBackground(QBrush(QColor (200,244,99), Qt::SolidPattern));
    ui->calendarWidget->setDateTextFormat(d, format);
}

void MainWindow::return_calendar_color(QDate d) { // календарь будет убирать закрашивание
    QTextCharFormat format = ui->calendarWidget->dateTextFormat(d);
    format.clearBackground();
    ui->calendarWidget->setDateTextFormat(d, format);
}

void MainWindow::sortAllTasks(){
    for (int i = 0; i < all_tasks.size(); i++) {
            for (int j = 0; j < all_tasks.size() - 1; j++) {
                if (all_tasks[j].getEndDate() > all_tasks[j + 1].getEndDate()) {
                    Task temp;
                    temp = all_tasks[j];
                    all_tasks[j] = all_tasks[j + 1];
                    all_tasks[j + 1] = temp;
                }
            }
     }
}

void MainWindow::setTrueId(){
    for (int i = 0; i < all_tasks.size(); i++){
        all_tasks[i].setId(i + 1);
    }
}

void MainWindow::deleteCompletedTasks(){
    int size = all_tasks.size();
    bool y = true;
    for (int i = 0; i < size; i++){
        if (all_tasks[i].getIsComplete() == y){
            for (int j = i; j < size - 1; j++){
                all_tasks[j] = all_tasks[j + 1];
            }
            i--;
            size--;
        }
    }
    all_tasks.resize(size);
    sortAllTasks();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
     on_exit_2_triggered();
     if (this->isExit) {
        event->accept();
     } else {
        event->ignore();
     }
}

void MainWindow::on_pushButton_show_clicked()
{
    sortAllTasks();
    allTasks_window = new AllTasks(this);
    allTasks_window->setAllTasks(&all_tasks);
    allTasks_window->setWindowTitle("My diary");
    allTasks_window->show();
    ui->listWidget->clear();
}

void MainWindow::on_add_clicked()
{
    newTask_window->setWindowTitle("My diary");
    newTask_window->setAllTasks(&all_tasks);
    newTask_window->setCurrentEndDateTime(this->date);
    newTask_window->show();
    newTask_window->activateWindow();
    on_calendarWidget_clicked(this->date);
}


void MainWindow::on_complete_clicked()
{
    if(ui->listWidget->currentItem()){
        QString name = ui->listWidget->currentItem()->text();
        QString check_name = " ";
        if (name.size() > 12){
             for(int k = name.size() - 11; k < name.size(); k++){
                 check_name += name[k];
             }
        }
        if (check_name == " (выполнено)"){
            QString item = ui->listWidget->currentItem()->text();
            int i = searchTrueTask(item);
            all_tasks[i].setIsComplete(false);
            setListWidget(this->date);
        } else{
            QString item = ui->listWidget->currentItem()->text();
            int i = searchTrueTask(item);
            all_tasks[i].setIsComplete(true);
            setListWidget(this->date);
        }
    } else {
        QMessageBox::warning(this, "Сообщение", "Вы не выбрали задачу!");
    }
}

void MainWindow::on_exit_2_triggered()
{
    QMessageBox exit(QMessageBox::Question,
                tr("Выход"),
                tr("Вы действительно хотите выйти?"),
                QMessageBox::Yes | QMessageBox::No,
                this);
        exit.setButtonText(QMessageBox::Yes, tr("Да"));
        exit.setButtonText(QMessageBox::No, tr("Нет"));

    if (exit.exec() == QMessageBox::Yes){
        QMessageBox del(QMessageBox::Question,
                    tr("Удаление"),
                    tr("Удалить выполненные задачи?"),
                    QMessageBox::Yes | QMessageBox::No,
                    this);
            del.setButtonText(QMessageBox::Yes, tr("Да"));
            del.setButtonText(QMessageBox::No, tr("Нет"));

        if (del.exec() == QMessageBox::Yes){
            ui->listWidget->clear();
            deleteCompletedTasks();
        }

        if(NewDiary == false) {
            saveTasks(this->DIR_NAME);
        }else if(NewDiary == true){
            saveTasks(this->file_path);
        }
        this->isExit = true;
        QApplication::exit();
    }
}


void MainWindow::on_delete_2_clicked()
{
    if(ui->listWidget->currentItem()){
        QMessageBox del(QMessageBox::Question,
                    tr("Удаление"),
                    tr("Вы действительно хотите удалить задачу?"),
                    QMessageBox::Yes | QMessageBox::No,
                    this);
            del.setButtonText(QMessageBox::Yes, tr("Да"));
            del.setButtonText(QMessageBox::No, tr("Нет"));

        if (del.exec() == QMessageBox::Yes){
            QString item = ui->listWidget->currentItem()->text();
            int i = searchTrueTask(item);
            int j = i;
            for (; j < all_tasks.size() - 1; j++){
                all_tasks[j] = all_tasks[j + 1];
            }
            all_tasks.resize(j);
            setListWidget(this->date);
        }
    } else {
        QMessageBox::warning(this, "Сообщение", "Вы не выбрали задачу!");
    }
}

void MainWindow::on_calendarWidget_clicked(const QDate &date)
{
    this->date = date;
    setListWidget(date);
}

void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{

    Task * newTask = &all_tasks[searchTrueTask((*item).text())];
    moreAboutTask_window->setDataToForms(newTask, &all_tasks);
    moreAboutTask_window->setWindowTitle("My diary");
    moreAboutTask_window->show();
}

void MainWindow::deleteDiary()
{
    ui->listWidget->clear();
    if(NewDiary == false) {
        QMessageBox del(QMessageBox::Question,
                    tr("Очистка"),
                    tr("Вы действительно хотите очистить ежедневник?"),
                    QMessageBox::Yes | QMessageBox::No,
                    this);
            del.setButtonText(QMessageBox::Yes, tr("Да"));
            del.setButtonText(QMessageBox::No, tr("Нет"));

        if (del.exec() == QMessageBox::Yes){
            for (int i = 0; i < all_tasks.size(); i ++){
                return_calendar_color(all_tasks[i].getEndDate());
            }
        }
    }else if(NewDiary == true){
        for (int i = 0; i < all_tasks.size(); i ++){
            return_calendar_color(all_tasks[i].getEndDate());
        }
    }

        this->all_tasks.resize(0);

}

bool MainWindow::removeDir (const QString &path){
    QDir dir (path);

    const QFileInfoList fileList = dir.entryInfoList (QDir::AllEntries | QDir::NoDotAndDotDot);

    bool result = true;
    QFile file;

    for (QFileInfoList::const_iterator it = fileList.constBegin(),
            end = fileList.constEnd(); result && it != end; ++it) {
        const QString fileName = it->absoluteFilePath();
        file.setFileName (fileName);

        result = it->isDir() ? removeDir(fileName) : file.remove();
    }
    return result && dir.rmdir(path);
}

void MainWindow::saveTasks(const QString &FILE_PATH){
    sortAllTasks();
    setTrueId();
    QTextCodec::setCodecForLocale(QTextCodec::codecForName( "UTF-8" ));
    QDir dir;
    if(NewDiary == false) {
        this->DIR_NAME = FILE_PATH;
    }else if(NewDiary == true){
        this->file_path = FILE_PATH;
    }
    dir.mkpath(FILE_PATH);
    QString FILE_NAME;
    for (int i = 0; i < all_tasks.size(); i ++){
        FILE_NAME = FILE_PATH + "/" + QString::number(all_tasks[i].getId()) + ".txt";
        QFile file(FILE_NAME);
        if(file.open( QIODevice::WriteOnly)){
            QTextStream stream(&file);
            QString isCom;
            if (all_tasks[i].getIsComplete() == true){
                isCom = "1";
            } else {
                isCom = "0";
            }
            QString str = QString::number(all_tasks[i].getId()) + "\r\n" + all_tasks[i].getName() + "\r\n" + all_tasks[i].getText() + "\r\n" +
                                                     isCom + "\r\n" + all_tasks[i].getEndDate().toString() + "\r\n" + all_tasks[i].getEndTime().toString() +"\r\n" ;
            stream << str;
            file.close();
        }
    }
}

void MainWindow::readTasks(const QString &FILE_PATH){
    int i = 1;
    QTextCodec::setCodecForLocale( QTextCodec::codecForName( "UTF-8" ) );
    QDir dir;
    if(NewDiary == false) {
        this->DIR_NAME = FILE_PATH;
    }else if(NewDiary == true){
        this->file_path = FILE_PATH;
    }
    if(dir.exists(FILE_PATH)){
        QString FILE_NAME;
        FILE_NAME = FILE_PATH + "/" + QString::number(i) + ".txt";
        while (QFile(FILE_NAME).exists()){
            FILE_NAME = FILE_PATH + "/" + QString::number(i) + ".txt";
            QFile file(FILE_NAME);
            Task task;
            if (file.open( QIODevice::ReadOnly)){
                QTextStream stream(&file);
                QDate endDate;
                QTime endTime;
                if(!file.atEnd()){
                   task.setId(stream.readLine().toInt());
                   task.setName(stream.readLine());
                   task.setText(stream.readLine());
                   if (stream.readLine().toInt() == 1){
                       task.setIsComplete(true);
                   } else {
                       task.setIsComplete(false);
                   }
                   endDate = QDate::fromString(stream.readLine());
                   task.setEndDate(endDate);
                   endTime = QTime::fromString(stream.readLine());
                   task.setEndTime(endTime);

                }
                file.close();
            all_tasks.push_back(task);
            on_calendarWidget_clicked(all_tasks[i - 1].getEndDate());
            i++;
            }
        }
    }
    on_calendarWidget_clicked(QDate::currentDate());
}

void MainWindow::on_create_Diary_2_triggered()
{
    QMessageBox create(QMessageBox::Question,
                tr("Новый Ежедневник"),
                tr("Вы действительно хотите закрыть этот ежедневник и создать новый?"),
                QMessageBox::Yes | QMessageBox::No,
                this);
        create.setButtonText(QMessageBox::Yes, tr("Да"));
        create.setButtonText(QMessageBox::No, tr("Нет"));

    if (create.exec() == QMessageBox::Yes){
        this->NewDiary = true;
        deleteDiary();
        this->file_path = "/C++/Diarys/SaveTaskNEW";
        readTasks(file_path);
    }
}

void MainWindow::on_save_2_triggered(){
    if(NewDiary == false) {
        saveTasks(this->DIR_NAME);
    }else if(NewDiary == true){
        saveTasks(this->file_path);
    }

}

void MainWindow::on_clear_triggered(){

    deleteDiary();
    removeDir(DIR_NAME);

}
