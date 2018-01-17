#include "mainwindow.h"
#include "trayicon.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QIcon icon("test.png");
    TrayIcon tray(icon);
    tray.show();

    MainWindow w;
    w.resize(500, 500);
    w.show();
    w.setWindowTitle(QApplication::translate("toplevel", "Top-level widget"));

    return a.exec();
}
