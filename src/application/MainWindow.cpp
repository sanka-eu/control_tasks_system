#include "MainWindow.h"

MainWindow::MainWindow():
    m_ui(std::make_shared<Ui::MainWindow>())
{
    m_ui->setupUi(this);
}