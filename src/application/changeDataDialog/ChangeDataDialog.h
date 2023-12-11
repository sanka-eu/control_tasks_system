#ifndef CHANGEDATADIALOG_H
#define CHANGEDATADIALOG_H

#include <src/application/changeDataDialog/addEmployeeDialog/AddEmployeeDialog.h>

#include <src/application/changeDataBD/ChangeDataBD.h>

#include <QDialog>

namespace Ui {
  class ChangeDataDialog;
} //namespace Ui

class ChangeDataDialog: public QDialog
{
    Q_OBJECT

public:
    ChangeDataDialog(std::shared_ptr<ChangeDataBD> dataBase, QWidget *parent = 0);

signals:
    EmployeeAdded();

private slots:
    void AddEmployeeSlot();
    void RemoveEmployeeSlot();
    void ChangeUserByIdSlot();
    void AddTaskSlot();
    void GiveTaskSlot();

private:
    std::shared_ptr<Ui::ChangeDataDialog> m_ui;
    std::shared_ptr<ChangeDataBD> m_dataBase;
    std::shared_ptr<AddEmployeeDialog> m_addEmployeeDialog;

}; // class ChangeDataDialog

#endif //CHANGEDATADIALOG_H