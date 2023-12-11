#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <src/application/changeDataBD/ChangeDataBD.h>

#include <src/application/loginDialog/LoginDialog.h>
#include <src/application/changeDataDialog/ChangeDataDialog.h>

#include <QString>
#include <QMessageBox>
#include <QTableWidget>

#include <QMainWindow>


namespace Ui {
  class MainWindow;
} //namespace Ui

class MainWindow: public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

private slots:
    void LoginUser(int positionUserId);
    void ChangeUserSlot();
    void ChangeDataSlot();
    void ShowAllTasksSlot();
    void AddEmployeeSlot();

private:
    int m_positionUserId;

    std::shared_ptr<Ui::MainWindow> m_ui;
    std::shared_ptr<ChangeDataBD> m_dataBase;
    std::shared_ptr<LoginDialog> m_loginDialog;
    std::shared_ptr<ChangeDataDialog> m_changeDataDialog;

}; // class MainWindow

#endif //MAINWINDOW_H