#include <QApplication>
#include <QResource>
#include <QMessageBox>
#include <QObject>

#include <qhotkey.h>
#include "GUI/CaptureImage.h"
#include "GUI/TrayIcon.h"

#include <QDebug>

void imageCallback()
{
    qDebug() << "Image!";
    (new CaptureImage)->show();
}
void gifCallback()
{
    qDebug() << "GIF!";
}

int main(int argc, char *argv[])
{
    // Create the application
    QApplication app(argc, argv);
    app.setQuitOnLastWindowClosed(false);

    // Register hotkeys
    qDebug() << "registering";

    QHotkey hotkey(QKeySequence("Ctrl+Shift+I"), true);
    QObject::connect(&hotkey, &QHotkey::activated, &imageCallback);

    qDebug() << "registered.";
    //Qt::QHotkey gifHotkey(Qt::ModifierKey::Control, Qt::Key_H, [](const Qt::QHotkey&) { (new CaptureImage)->show(); });

    // Register resources
    QResource::registerResource("../res/camera-icon.png");
    QResource::registerResource("../res/help.png");
    QResource::registerResource("../res/image.png");
    QResource::registerResource("../res/gif.png");
    QResource::registerResource("../res/settings.png");
    QResource::registerResource("../res/exit.png");

    // Create App Icon
    QIcon appIcon(":/res/camera-icon.png");

    // Check if Tray Icons are available
    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        // Show error messagebox
        QMessageBox::critical(0, QObject::tr("PostShot - System Tray"),
                              QObject::tr("No System Tray detected "
                                          "on this System."));
        return -1;
    }

    // Create a Tray Icon
    TrayIcon tray(nullptr, appIcon, app);
    tray.show();

    // Execute Application
    return app.exec();
}
