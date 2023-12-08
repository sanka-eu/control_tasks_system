#ifndef CHANGEDATADIALOG_H
#define CHANGEDATADIALOG_H

#include <src/application/changeDataBD/ChangeDataBD.h>

#include <QDialog>

namespace Ui {
  class ChangeDataDialog;
} //namespace Ui

class ChangeDataDialog: public QDialog
{
    Q_OBJECT

public:
    ChangeDataDialog(QWidget *parent = 0);

private slots:
    void AddEmployeeSlot();
    void RemoveEmployeeSlot();
    void ChangeUserByIdSlot();
    void AddTaskSlot();
    void GiveTaskSlot();

private:
    std::shared_ptr<Ui::ChangeDataDialog> m_ui;

}; // class ChangeDataDialog

#endif //CHANGEDATADIALOG_H