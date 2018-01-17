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
     * \brief Construct a new \b{tray icon} for PostShot
    */
    TrayIcon(QObject* parent, QIcon& icon, QApplication& app);

    /*!
     * \fn TrayIcon::~TrayIcon()
     * \brief Deconstruct and dispose the \b{tray icon}
    */
    ~TrayIcon();

    /*!
     * \brief Show the \b{tray icon}
    */
    void show();

    /*!
     * \brief Hide the tray icon (this
     * does \b{not} free any resources)
    */
    void hide();

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
