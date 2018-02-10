#include <QApplication>
#include <QWidget>
#include <QScreen>
#include <QKeyEvent>
#include <QWindow>
#include <functional>

#include "GUI/animation.h"
#include "GUI/captureimage.h"
#include "Modules/screenmanager.h"
#include "Modules/windowhelper.h"
#include "Modules/screenshot.h"

#include <QList>
#include <Windows.h>
#include <QColor>
#include <QPalette>

#include <QGraphicsScene>
#include <QGraphicsView>

CaptureImage::CaptureImage(QWidget* parent)
    : QMainWindow(parent, Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint),
      scene(new QGraphicsScene), view(new QGraphicsView(scene, this)),
      image(Screenshot::getScreenshotFull()), label(new QLabel), windows(Helper::getAllWindows())
{
//    setAttribute(Qt::WA_NoSystemBackground);
    setWindowOpacity(0.0);

    installEventFilter(this); // Key press handler

    setGeometry(ScreenManager::getVirtualDesktop()); // span across all screens

//    label->setBackgroundRole(QPalette::Base);
//    label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
//    label->setScaledContents(true);
//    label->setAttribute(Qt::WA_TranslucentBackground);
    label->setPixmap(image);

    // TODO: SET LABEL TRANSPARENT FOR OPACITY ANIMATION

//    QPalette palette = label->palette();
//    QColor color = palette.color(QPalette::Window);
//    color.setAlpha(130);
//    palette.setColor(QPalette::Text, color);
//    label->setPalette(palette);

    scene->addPixmap(Screenshot::getScreenshotFull());
    scene->setBackgroundBrush(Qt::red);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->show();
    view->setBackgroundBrush(Qt::red);

    setCentralWidget(view);

    show();
    activateWindow();
    QApplication::setOverrideCursor(Qt::CrossCursor);
    Animation::fade(this, 200, 0.0, 1.0); // fade in
}


bool CaptureImage::eventFilter(QObject* obj, QEvent* event)
{
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent* key = static_cast<QKeyEvent*>(event);
        if ((key->key() == Qt::Key_Escape))
        {
            QApplication::restoreOverrideCursor();
            auto func = std::bind(&CaptureImage::close, this);
            Animation::fade(this, 200, 0.4, 0.0, &func);
            return true;
        }
    }

    return QObject::eventFilter(obj, event);
}
