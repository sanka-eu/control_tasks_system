#include "ChangeDataWidget.h"

ChangeDataWidget::ChangeDataWidget(QWidget *parent):
    QWidget(parent),
    m_ui(std::make_shared<Ui::ChangeDataWidget>())
{
    m_ui->setupUi(this);

    connect(m_ui->changeUserDataButton, &QPushButton::clicked, this, ChangeUsersSlot);
    connect(m_ui->changeAssigmentsDataButton, &QPushButton::clicked, this, ChangeDataWidget::ChangeAssigmentsSlot);
}

void ChangeDataWidget::ChangeUsersSlot()
{
    qDebug("change users slot");
}

void ChangeDataWidget::ChangeAssigmentsSlot()
{
    qDebug("change assigments slot");
}