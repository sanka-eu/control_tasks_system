#ifndef ADDEMPLOYEEDIALOG_H
#define ADDEMPLOYEEDIALOG_H

#include <src/application/changeDataBD/ChangeDataBD.h>

#include <QDialog>

namespace Ui {
  class AddEmployeeDialog;
} //namespace Ui

class AddEmployeeDialog: public QDialog
{
    Q_OBJECT

public:
    AddEmployeeDialog(std::shared_ptr<ChangeDataBD> dataBase, QWidget *parent = 0);

signals:
    EmployeeAdded();

private slots:
    void AddEmployeeSlot();

private:
    std::shared_ptr<Ui::AddEmployeeDialog> m_ui;
    std::shared_ptr<ChangeDataBD> m_dataBase;

}; // class AddEmployeeDialog

#endif //ADDEMPLOYEEDIALOG_H