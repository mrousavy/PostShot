#include "SettingsWindow.h"
#include <QQuickView>
#include "ui_SettingsWindow.h"

SettingsWindow::SettingsWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsWindow)
{
    ui->setupUi(this);
    // TODO: make ui->quickWidget fill window
    ui->quickWidget->setSource(QUrl("qrc:/GUI/SettingsWindow.qml"));
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}
