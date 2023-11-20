#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_MainWindow.h"

class MainWindow: public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

private slots:
    void changeDataSlot();

private:
    std::shared_ptr<Ui::MainWindow> m_ui;

}; // class MainWindow

#endif //MAINWINDOW_H