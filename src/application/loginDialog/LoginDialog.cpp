#include "LoginDialog.h"
#include "ui_LoginDialog.h"

LoginDialog::LoginDialog(std::shared_ptr<ChangeDataBD> dataBase, QWidget *parent):
    QDialog(parent),
    m_ui(std::make_shared<Ui::LoginDialog>()),
    m_dataBase(dataBase)
{
    m_ui->setupUi(this);

    connect(m_ui->signInButton, SIGNAL(clicked()), this, SLOT(LoginSlot()));
}

void LoginDialog::LoginSlot()
{
    qDebug("LoginSlot");

    Q_EMIT UserLoggedIn(m_dataBase->getEmployeePositionId(m_ui->loginLineEdit->text().toStdString(), m_ui->passwordLineEdit->text().toStdString()));
}