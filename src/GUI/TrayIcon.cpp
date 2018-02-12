#include "TrayIcon.h"
#include <QSystemTrayIcon>
#include <QAction>

#include "Modules/Screenshot.h"
#include "Modules/ImageManipulation.h"
#include "GUI/CaptureImage.h"
#include "GUI/SettingsWindow.h"
#include "GUI/HelpWindow.h"

TrayIcon::TrayIcon(QObject* parent, QIcon& icon, QApplication& app)
 : QObject(parent), _app(app)
{
    _trayIcon = new QSystemTrayIcon(icon, parent);
    _trayIcon->setToolTip("PostShot");
    loadMenu();

    connect(_trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(cbTrayClick(QSystemTrayIcon::ActivationReason)));
}


void TrayIcon::cbTrayClick(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
    case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::DoubleClick:
        cbImage();
        break;
    case QSystemTrayIcon::MiddleClick:
        cbGif();
        break;
    default:
        break;
    }
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

void TrayIcon::hide()
{
    _trayIcon->hide();
}

void TrayIcon::loadMenu()
{
    _menu = new QMenu(tr("PostShot background service"));

    QIcon icHelp(":/res/help.png");
    QIcon icImage(":/res/image.png");
    QIcon icGif(":/res/gif.png");
    QIcon icSettings(":/res/settings.png");
    QIcon icExit(":/res/exit.png");

    actionHelp = new QAction(icHelp, tr("Help"));
    connect(actionHelp, &QAction::triggered, this, &TrayIcon::cbHelp);
    actionImage = new QAction(icImage, tr("Image"));
    actionImage->setShortcut(QKeySequence("Ctrl+Shift+I"));
    connect(actionImage, &QAction::triggered, this, &TrayIcon::cbImage);
    actionGif = new QAction(icGif, tr("GIF"));
    actionGif->setShortcut(QKeySequence("Ctrl+Shift+H"));
    connect(actionGif, &QAction::triggered, this, &TrayIcon::cbGif);
    actionSettings = new QAction(icSettings, tr("Settings"));
    connect(actionSettings, &QAction::triggered, this, &TrayIcon::cbSettings);
    actionExit = new QAction(icExit, tr("Exit"));
    connect(actionExit, &QAction::triggered, this, &TrayIcon::cbExit);

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
    (new HelpWindow)->show();
}

void TrayIcon::cbImage()
{
    (new CaptureImage)->show();
}

void TrayIcon::cbGif()
{
    // TODO: GIF Click
    printf("GIF clicked.");
    auto pixmap = Screenshot::getScreenshotFull();
    ImageManipulation::chooseSaveImage(pixmap);
}

void TrayIcon::cbSettings()
{
    (new SettingsWindow)->show();
}

void TrayIcon::cbExit()
{
    _app.exit();
}
