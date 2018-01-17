#include "trayicon.h"
#include <qsystemtrayicon.h>

TrayIcon::TrayIcon(QIcon& icon, QWidget* parent)
{
    _trayIcon = new QSystemTrayIcon(icon, parent);
    _menu = new QMenu("QMenu text", parent);
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
