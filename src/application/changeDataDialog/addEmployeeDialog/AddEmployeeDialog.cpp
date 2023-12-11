#include "AddEmployeeDialog.h"
#include "ui_AddEmployeeDialog.h"

AddEmployeeDialog::AddEmployeeDialog(std::shared_ptr<ChangeDataBD> dataBase, QWidget *parent):
    QDialog(parent),
    m_ui(std::make_shared<Ui::AddEmployeeDialog>()),
    m_dataBase(dataBase)
{
    m_ui->setupUi(this);

    connect(m_ui->addEmployeeButton, SIGNAL(clicked()), this, SLOT(AddEmployeeSlot()));
}

void AddEmployeeDialog::AddEmployeeSlot()
{
    qDebug("addEmployeeSlot");

    m_dataBase->addEmployee(m_ui->fullNameLineEdit->text().toStdString(), std::stoi(m_ui->experienceLineEdit->text().toStdString()),
                            std::stoi(m_ui->departmentLineEdit->text().toStdString()), std::stoi(m_ui->positionIdLineEdit->text().toStdString()));

    this->close();

    Q_EMIT EmployeeAdded();
}