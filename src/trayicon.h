#ifndef TRAYICON_H
#define TRAYICON_H
#include <QMenu>
#include <QObject>
#include <QSystemTrayIcon>
#include <QDialog>

class TrayIcon : public QObject
{
    Q_OBJECT
public:
    /*!
     * \fn TrayIcon::TrayIcon(QIcon& icon, QWidget& parent)
     * Construct a new \b{tray icon} for PostShot
    */
    TrayIcon(QObject* parent, QIcon& icon);

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

public slots:
    void settings();

private:
    QSystemTrayIcon* _trayIcon;
    QMenu* _menu;
};

#endif // TRAYICON_H
