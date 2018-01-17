#ifndef TRAYICON_H
#define TRAYICON_H
#include <QMenu>
#include <QObject>
#include <QSystemTrayIcon>
#include <QDialog>
#include <QApplication>

class TrayIcon : public QObject
{
    Q_OBJECT
public:
    /*!
     * \fn TrayIcon::TrayIcon(QIcon& icon, QWidget& parent)
     * Construct a new \b{tray icon} for PostShot
    */
    TrayIcon(QObject* parent, QIcon& icon, QApplication& app);

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

private slots:
    //// Callbacks  ////
    void cbHelp();
    void cbImage();
    void cbGif();
    void cbSettings();
    void cbExit();

private:
    //// Functions  ////
    void loadMenu();

    //// Properties ////
    QApplication& _app;
    QSystemTrayIcon* _trayIcon;
    QMenu* _menu;
    QAction* actionHelp;
    QAction* actionImage;
    QAction* actionGif;
    QAction* actionSettings;
    QAction* actionExit;
};

#endif // TRAYICON_H
