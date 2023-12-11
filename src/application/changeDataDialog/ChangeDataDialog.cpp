#include "ChangeDataDialog.h"
#include "ui_ChangeDataDialog.h"

ChangeDataDialog::ChangeDataDialog(std::shared_ptr<ChangeDataBD> dataBase, QWidget *parent):
    QDialog(parent),
    m_ui(std::make_shared<Ui::ChangeDataDialog>()),
    m_dataBase(dataBase),
    m_addEmployeeDialog(std::make_shared<AddEmployeeDialog>(m_dataBase))
{
    m_ui->setupUi(this);

    connect(m_ui->addEmployeeButton, SIGNAL(clicked()), this, SLOT(AddEmployeeSlot()));
    connect(m_ui->removeEmployeeButton, SIGNAL(clicked()), this, SLOT(RemoveEmployeeSlot()));
    connect(m_ui->changeUserByIdButton, SIGNAL(clicked()), this, SLOT(ChangeUserByIdSlot()));
    connect(m_ui->addTaskButton, SIGNAL(clicked()), this, SLOT(AddTaskSlot()));
    connect(m_ui->giveTaskButton, SIGNAL(clicked()), this, SLOT(GiveTaskSlot()));
}

void ChangeDataDialog::AddEmployeeSlot()
{
    qDebug("addEmployeeSlot");

    m_addEmployeeDialog->exec();

    Q_EMIT EmployeeAdded();
}

void ChangeDataDialog::RemoveEmployeeSlot()
{
    qDebug("removeEmployeeSlot");
}

void ChangeDataDialog::ChangeUserByIdSlot()
{
    qDebug("changeUserByIdSlot");
}

void ChangeDataDialog::AddTaskSlot()
{
    qDebug("addTaskSlot");
}

void ChangeDataDialog::GiveTaskSlot()
{
    qDebug("giveTaskSlot");
}