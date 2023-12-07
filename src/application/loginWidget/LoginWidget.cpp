#include "LoginWidget.h"

LoginWidget::LoginWidget(QWidget *parent):
    QWidget(parent),
    m_ui(std::make_shared<Ui::LoginWidget>())
{
    m_ui->setupUi(this);

    connect(m_ui->signInButton, SIGNAL(clicked()), this, SLOT(LoginSlot()));
}

void LoginWidget::LoginSlot()
{
    qDebug("LoginSlot");
}