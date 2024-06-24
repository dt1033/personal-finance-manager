#include <QApplication>
#include "login.h"
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    Login loginWindow;
    if (loginWindow.exec() == QDialog::Accepted) {
        MainWindow mainWindow;
        mainWindow.show();
        return app.exec();
    }

    return 0;
}
