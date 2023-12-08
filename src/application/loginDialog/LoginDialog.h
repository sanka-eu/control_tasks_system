#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <src/application/changeDataBD/ChangeDataBD.h>

#include <QDialog>

namespace Ui {
  class LoginDialog;
} //namespace Ui

class LoginDialog: public QDialog
{
    Q_OBJECT

public:
    LoginDialog(QWidget *parent = 0);

private slots:
    void LoginSlot();

private:
    std::shared_ptr<Ui::LoginDialog> m_ui;

}; // class LoginDialog

#endif //LOGINDIALOG_H