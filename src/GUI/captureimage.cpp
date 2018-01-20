#include <QApplication>
#include <QWidget>
#include <QScreen>
#include <QKeyEvent>
#include <QWindow>
#include <functional>

#include "GUI/animation.h"
#include "GUI/captureimage.h"
#include "GUI/screenmanager.h"

CaptureImage::CaptureImage(QWidget *parent) : QWidget(parent, Qt::Window | Qt::FramelessWindowHint)
{
    setAttribute(Qt::WA_NoSystemBackground);
    setWindowOpacity(0.0);

    auto const screen(QGuiApplication::primaryScreen());
    setGeometry(screen->availableVirtualGeometry()); // Make fullscreen

    installEventFilter(this); // Key press handler

    setGeometry(ScreenManager::getVirtualDesktop()); // span across all screens
    show();
    activateWindow();
    Animation::fade(this, 200, 0.0, 0.3); // fade in
}


bool CaptureImage::eventFilter(QObject* obj, QEvent* event)
{
    if (event->type()==QEvent::KeyPress)
    {
        QKeyEvent* key = static_cast<QKeyEvent*>(event);
        if ((key->key()==Qt::Key_Escape))
        {
            std::function<bool(void)> func = std::bind(&CaptureImage::close, this);
            Animation::fade(this, 200, 0.3, 0.0, &func);
            return true;
        }
    }

    return QObject::eventFilter(obj, event);
}
