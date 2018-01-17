#include "trayicon.h"
#include <QSystemTrayIcon>
#include <QAction>

TrayIcon::TrayIcon(QObject* parent, QIcon& icon)
 : QObject(parent)
{
    _trayIcon = new QSystemTrayIcon(icon, parent);
    _menu = new QMenu("QMenu text");

    auto* settingsAction = new QAction(tr("&Settings"));
    QObject::connect(settingsAction, SIGNAL(QAction::triggered(bool)), this, SLOT(settings()));
}

TrayIcon::~TrayIcon()
{
    if (_trayIcon != nullptr)
    {
        _trayIcon->hide();
        delete _trayIcon;
        delete _menu;
    }
}

void TrayIcon::show()
{
    _trayIcon->show();
}

void TrayIcon::settings()
{
    printf("Settings clicked.");
}
