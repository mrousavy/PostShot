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
        delete actionHelp;
        delete actionImage;
        delete actionGif;
        delete actionSettings;
        delete actionExit;
    }
}

void TrayIcon::show()
{
    _trayIcon->show();
}


void TrayIcon::loadMenu()
{
    _menu = new QMenu("QMenu text");

    actionHelp = new QAction(tr("Help"));
    connect(actionHelp, QAction::triggered, this, cbHelp);
    actionImage = new QAction(tr("Image"));
    connect(actionImage, QAction::triggered, this, cbImage);
    actionGif = new QAction(tr("GIF"));
    connect(actionGif, QAction::triggered, this, cbGif);
    actionSettings = new QAction(tr("Settings"));
    connect(actionSettings, QAction::triggered, this, cbSettings);
    actionExit = new QAction(tr("Exit"));
    connect(actionExit, QAction::triggered, this, cbExit);

    _menu->addAction(actionHelp);
    _menu->addAction(actionImage);
    _menu->addAction(actionGif);
    _menu->addAction(actionSettings);
    _menu->addAction(actionExit);

    _trayIcon->setContextMenu(_menu);
}

void TrayIcon::cbHelp()
{
    printf("Settings clicked.");
}
