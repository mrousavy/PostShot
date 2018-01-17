#include "trayicon.h"
#include <QSystemTrayIcon>
#include <QAction>

TrayIcon::TrayIcon(QObject* parent, QIcon& icon, QApplication& app)
 : QObject(parent), _app(app)
{
    _trayIcon = new QSystemTrayIcon(icon, parent);
    loadMenu();
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

    QIcon icHelp(":/res/help.png");
    QIcon icImage(":/res/image.png");
    QIcon icGif(":/res/gif.png");
    QIcon icSettings(":/res/settings.png");
    QIcon icExit(":/res/exit.png");

    actionHelp = new QAction(icHelp, tr("Help"));
    connect(actionHelp, &QAction::triggered, this, &cbHelp);
    actionImage = new QAction(icImage, tr("Image"));
    connect(actionImage, &QAction::triggered, this, &cbImage);
    actionGif = new QAction(icGif, tr("GIF"));
    connect(actionGif, &QAction::triggered, this, &cbGif);
    actionSettings = new QAction(icSettings, tr("Settings"));
    connect(actionSettings, &QAction::triggered, this, &cbSettings);
    actionExit = new QAction(icExit, tr("Exit"));
    connect(actionExit, &QAction::triggered, this, &cbExit);

    _menu->addAction(actionHelp);
    _menu->addSeparator();
    _menu->addAction(actionImage);
    _menu->addAction(actionGif);
    _menu->addSeparator();
    _menu->addAction(actionSettings);
    _menu->addAction(actionExit);

    _trayIcon->setContextMenu(_menu);
}

void TrayIcon::cbHelp()
{
    printf("Settings clicked.");
}

void TrayIcon::cbImage()
{
    printf("Settings clicked.");
}

void TrayIcon::cbGif()
{
    printf("Settings clicked.");
}

void TrayIcon::cbSettings()
{
    printf("Settings clicked.");
}

void TrayIcon::cbExit()
{
    _app.exit();
}
