#include "MainWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    srand(time(NULL));
    
    QApplication app(argc, argv);

    std::shared_ptr<MainWindow> mainWindow = std::make_shared<MainWindow>();
    mainWindow->show();

    return app.exec();
}
