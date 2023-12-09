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
    LoginDialog(std::shared_ptr<ChangeDataBD> dataBase, QWidget *parent = 0);

signals:
    void UserLoggedIn(int positionUserId);

private slots:
    void LoginSlot();

private:
    std::shared_ptr<Ui::LoginDialog> m_ui;
    std::shared_ptr<ChangeDataBD> m_dataBase;

}; // class LoginDialog

#endif //LOGINDIALOG_H