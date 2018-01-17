#include "mainwindow.h"
#include "trayicon.h"
#include <QApplication>
#include <QResource>


int main(int argc, char *argv[])
{
    // Create the application
    QApplication a(argc, argv);

    // Register resources
    QResource::registerResource("../res/camera-icon.png");

    // Create a Tray Icon
    QIcon icon(":/res/camera-icon.png");
    TrayIcon tray(nullptr, icon, a);
    tray.show();

    // Start the Main Window
    MainWindow w;
    w.resize(500, 500);
    w.show();
    w.setWindowTitle(QApplication::translate("toplevel", "Top-level widget"));

    // Execute Application
    return a.exec();
}
