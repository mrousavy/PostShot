#include "HelpWindow.h"
#include "ui_HelpWindow.h"

HelpWindow::HelpWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HelpWindow)
{
    ui->setupUi(this);
}

HelpWindow::~HelpWindow()
{
    delete ui;
}
