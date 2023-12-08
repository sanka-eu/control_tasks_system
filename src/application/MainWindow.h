#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <src/application/loginDialog/LoginDialog.h>
#include <src/application/changeDataDialog/ChangeDataDialog.h>

namespace Ui {
  class MainWindow;
} //namespace Ui

class MainWindow: public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

private slots:
    void changeUserSlot();
    void changeDataSlot();

private:
    std::shared_ptr<Ui::MainWindow> m_ui;

}; // class MainWindow

#endif //MAINWINDOW_H