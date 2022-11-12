#include "mainmenu.h"
#include "ui_mainmenu.h"

mainmenu::mainmenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainmenu)
{
    ui->setupUi(this);
}

mainmenu::~mainmenu()
{
    delete ui;
}

void mainmenu::on_adminPagePushButton_clicked()
{
    emit goToAdminPage();
}


void mainmenu::on_mainMenuPushButton_clicked()
{
    emit goToMenuPage();
}

