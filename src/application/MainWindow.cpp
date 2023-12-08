#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    m_ui(std::make_shared<Ui::MainWindow>()),
    m_dataBase(std::make_shared<ChangeDataBD>())
{
    m_ui->setupUi(this);

    connect(m_ui->changeUser, SIGNAL(clicked()), this, SLOT(ChangeUserSlot()));
    connect(m_ui->changeData, SIGNAL(clicked()), this, SLOT(ChangeDataSlot()));
    connect(m_ui->showAllTasks, SIGNAL(clicked()), this, SLOT(ShowAllTasksSlot()));
}

void MainWindow::ChangeUserSlot()
{
    qDebug("change user slot");
    
    std::shared_ptr<LoginDialog> loginDialog = std::make_shared<LoginDialog>();
    
    loginDialog->exec();
}

void MainWindow::ChangeDataSlot()
{
    qDebug("change data slot");
    
    std::shared_ptr<ChangeDataDialog> changeDataDialog = std::make_shared<ChangeDataDialog>();
    
    changeDataDialog->exec();
}

void MainWindow::ShowAllTasksSlot()
{
    qDebug("show all tasks slot");

    std::vector<std::vector<std::string>> tasksTable = m_dataBase->getTasks();
    
    if(tasksTable.empty() || (!tasksTable.empty() && tasksTable.at(0).empty()))
    {
        QMessageBox errorMessage;
        errorMessage.critical(0,"Error","Список задач пуст!");
        errorMessage.setFixedSize(500,200);
    }
    else
    {
        m_ui->tableWidget->setRowCount(tasksTable.size());
        m_ui->tableWidget->setColumnCount(tasksTable.at(0).size());
    }
    
    int rowNumber = 0;
    while(!tasksTable.empty())
    {
        std::vector<std::string> row = tasksTable.at(tasksTable.size() - 1);
        tasksTable.pop_back();

        for(int i = 0; i < row.size(); ++i)
        {
            m_ui->tableWidget->setItem(rowNumber, i, new QTableWidgetItem(QString::fromStdString(row.at(i))));
        }
        
        rowNumber++;
    }
    
}
