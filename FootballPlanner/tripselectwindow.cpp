#include "tripselectwindow.h"
#include "ui_tripselectwindow.h"

tripselectwindow::tripselectwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tripselectwindow)
{
    ui->setupUi(this);
}

tripselectwindow::~tripselectwindow()
{
    delete ui;
}

void tripselectwindow::on_mainMenuPushButton_clicked()
{
    emit goToMainSelectWindow();
}

