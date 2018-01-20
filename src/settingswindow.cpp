#include "settingswindow.h"
#include "ui_settingswindow.h"
#include "hotkey.h"
#include "keysequence.h"

SettingsWindow::SettingsWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsWindow)
{
    ui->setupUi(this);
    Hotkey key(this, "Ctrl+Shift+X", 1);
    connect(key, &Hotkey::Activated, [=](size_t id)
    {
        qDebug() << "Activated: " << QString::number(id);
    });
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}
