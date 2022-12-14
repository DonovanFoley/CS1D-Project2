/*****************************************************************//**
 * \file   mainmenu.h
 * \brief  main menu displayed to the user
 * 
 * \author Admin
 * \date   December 2022
 *********************************************************************/

#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>

namespace Ui {
class mainmenu;
}

class mainmenu : public QWidget
{
    Q_OBJECT

public:
    explicit mainmenu(QWidget *parent = nullptr);
    ~mainmenu();

signals:
     void goToAdminPage();
     void goToMenuPage();

private slots:
    void on_adminPagePushButton_clicked();

    void on_mainMenuPushButton_clicked();

private:
    Ui::mainmenu *ui;
};

#endif // MAINMENU_H
