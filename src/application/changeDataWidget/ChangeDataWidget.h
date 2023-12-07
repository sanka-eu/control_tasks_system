#ifndef CHANGEDATAWIDGET_H
#define CHANGEDATAWIDGET_H

#include <src/application/changeDataBD/ChangeDataBD.h>

#include <QWidget>

namespace Ui {
  class ChangeDataWidget;
} //namespace Ui

class ChangeDataWidget: public QWidget
{
    Q_OBJECT

public:
    ChangeDataWidget(QWidget *parent = 0);
    std::shared_ptr<Ui::ChangeDataWidget> getUi();

private slots:
    void AddEmployeeSlot();
    void RemoveEmployeeSlot();
    void ChangeUserByIdSlot();
    void AddTaskSlot();
    void GiveTaskSlot();

private:
    std::shared_ptr<Ui::ChangeDataWidget> m_ui;

}; // class ChangeDataWidget

#endif //CHANGEDATAWIDGET_H