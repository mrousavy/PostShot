#ifndef TRAYICON_H
#define TRAYICON_H
#include <qsystemtrayicon.h>
#include <qmenu.h>

class TrayIcon
{
public:
    /*!
     * \fn TrayIcon::TrayIcon(QIcon& icon, QWidget& parent)
     * Construct a new \b{tray icon} for PostShot
    */
    TrayIcon(QIcon& icon, QWidget* parent = nullptr);

    /*!
     * \fn TrayIcon::~TrayIcon()
     * Deconstruct and dispose the \b{tray icon
    */
    ~TrayIcon();

    /*!
     * \title Show the tray icon
     * \brief Show the \b{tray icon}
    */
    void show();
private:
    QSystemTrayIcon* _trayIcon;
    QMenu* _menu;
};

#endif // TRAYICON_H
