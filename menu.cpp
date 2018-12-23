#include "menu.h"
#include "ui_menu.h"

Menu::Menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
   /* main_window = new MainWindow(this);
    connect(main_window, &MainWindow::menuWindow, this, &Menu::menu_slot);
*/
}

Menu::~Menu()
{
    delete ui;
}

void Menu::menu_slot(){
    Menu::activateWindow();
   // on_calendarWidget_clicked(this->date);
}

void Menu::on_pushButton_clicked()
{
   //main_window = new AllTasks(this);
    //main_window->setAllTasks(&all_tasks);
    main_window->setWindowTitle("My diary");
    main_window->show();
}
