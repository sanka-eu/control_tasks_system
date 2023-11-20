#ifndef CHANGEDATAWIDGET_H
#define CHANGEDATAWIDGET_H

#include <QWidget>
#include "ui_ChangeDataWidget.h"

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