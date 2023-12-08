#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    m_ui(std::make_shared<Ui::MainWindow>())
{
    m_ui->setupUi(this);

    connect(m_ui->changeUser, SIGNAL(clicked()), this, SLOT(changeUserSlot()));
    connect(m_ui->changeData, SIGNAL(clicked()), this, SLOT(changeDataSlot()));
}

void MainWindow::changeUserSlot()
{
    qDebug("change user slot");
    
    std::shared_ptr<LoginDialog> loginDialog = std::make_shared<LoginDialog>();
    
    loginDialog->exec();
}

void MainWindow::changeDataSlot()
{
    qDebug("change data slot");
    
    std::shared_ptr<ChangeDataDialog> changeDataDialog = std::make_shared<ChangeDataDialog>();
    
    changeDataDialog->exec();
}

