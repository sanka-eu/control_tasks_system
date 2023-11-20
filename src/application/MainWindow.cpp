#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    m_ui(std::make_shared<Ui::MainWindow>())
{
    m_ui->setupUi(this);

    connect(m_ui->changeData, &QPushButton::clicked, this, changeDataSlot);
}

void MainWindow::changeDataSlot()
{
    qDebug("change data slot");
    
    QDialog *changeDataWidget = new QDialog(this);
    
    std::shared_ptr<Ui::ChangeDataWidget> changeDataUi = std::make_shared<Ui::ChangeDataWidget>();
    changeDataUi->setupUi(changeDataWidget);
    
    changeDataWidget->show();
}