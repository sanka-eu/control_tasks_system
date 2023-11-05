#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    m_ui(std::make_shared<Ui::MainWindow>())
{
    m_ui->setupUi(this);
}