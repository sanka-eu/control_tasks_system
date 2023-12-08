#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include "ui_LoginWidget.h"

#include <src/application/changeDataBD/ChangeDataBD.h>

#include <QWidget>

class LoginWidget: public QWidget
{
    Q_OBJECT

public:
    LoginWidget(QWidget *parent = 0);

private slots:
    void LoginSlot();

private:
    Ui::LoginWidget* m_ui;

}; // class LoginWidget

#endif //LOGINWIDGET_H