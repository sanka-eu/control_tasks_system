#ifndef CHANGEDATAWIDGET_H
#define CHANGEDATAWIDGET_H

#include "ui_ChangeDataWidget.h"

#include <src/application/changeDataBD/ChangeDataBD.h>

#include <QWidget>

class ChangeDataWidget: public QWidget
{
    Q_OBJECT

public:
    ChangeDataWidget(QWidget *parent = 0);

private slots:
    void ChangeUsersSlot();
    void ChangeAssigmentsSlot();

private:
    std::shared_ptr<Ui::ChangeDataWidget> m_ui;

}; // class ChangeDataWidget

#endif //CHANGEDATAWIDGET_H