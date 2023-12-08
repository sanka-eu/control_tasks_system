#include "LoginDialog.h"
#include "ui_LoginDialog.h"

LoginDialog::LoginDialog(QWidget *parent):
    QDialog(parent),
    m_ui(std::make_shared<Ui::LoginDialog>())
{
    m_ui->setupUi(this);

    connect(m_ui->signInButton, SIGNAL(clicked()), this, SLOT(LoginSlot()));
}

void LoginDialog::LoginSlot()
{
    qDebug("LoginSlot");
}