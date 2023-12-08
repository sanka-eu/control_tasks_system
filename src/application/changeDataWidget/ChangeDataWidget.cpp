#include "ChangeDataWidget.h"
#include "ui_ChangeDataWidget.h"

ChangeDataWidget::ChangeDataWidget(QWidget *parent):
    QWidget(parent),
    m_ui(std::make_shared<Ui::ChangeDataWidget>())
{
    m_ui->setupUi(this);

    connect(m_ui->addEmployeeButton, SIGNAL(clicked()), this, SLOT(AddEmployeeSlot()));
    connect(m_ui->removeEmployeeButton, SIGNAL(clicked()), this, SLOT(RemoveEmployeeSlot()));
    connect(m_ui->changeUserByIdButton, SIGNAL(clicked()), this, SLOT(ChangeUserByIdSlot()));
    connect(m_ui->addTaskButton, SIGNAL(clicked()), this, SLOT(AddTaskSlot()));
    connect(m_ui->giveTaskButton, SIGNAL(clicked()), this, SLOT(GiveTaskSlot()));
}

std::shared_ptr<Ui::ChangeDataWidget> ChangeDataWidget::getUi()
{
    return m_ui;
}

void ChangeDataWidget::AddEmployeeSlot()
{
    qDebug("addEmployeeSlot");
}

void ChangeDataWidget::RemoveEmployeeSlot()
{
    qDebug("removeEmployeeSlot");
}

void ChangeDataWidget::ChangeUserByIdSlot()
{
    qDebug("changeUserByIdSlot");
}

void ChangeDataWidget::AddTaskSlot()
{
    qDebug("addTaskSlot");
}

void ChangeDataWidget::GiveTaskSlot()
{
    qDebug("giveTaskSlot");
}