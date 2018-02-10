#include "GUI/captureimage.h"

#include <QKeyEvent>
#include <functional>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVBoxLayout>

#include "GUI/animation.h"
#include "Modules/screenmanager.h"
#include "Modules/windowhelper.h"
#include "Modules/screenshot.h"

#include <QDebug>

CaptureImage::CaptureImage(QWidget* parent)
    : QWidget(parent, Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint),
      scene(new QGraphicsScene), view(new QGraphicsView(scene, this)),
      layout(new QVBoxLayout(this)),
      image(Screenshot::getScreenshotFull()), windows(Helper::getAllWindows())
{
    setWindowOpacity(0.0);

    installEventFilter(this); // Key press handler

    setGeometry(ScreenManager::getVirtualDesktop()); // span across all screens

    scene->addPixmap(this->image);
    //view->setBackgroundBrush(this->image);
    view->setFrameStyle(QFrame::NoFrame); // Disable ~1px borders
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setCacheMode(QGraphicsView::CacheBackground);

    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(view);
    setLayout(layout);

    show();
    activateWindow();
    setCursor(Qt::CrossCursor);
    Animation::fade(this, 200, 0.0, 0.4); // fade in
}

CaptureImage::~CaptureImage()
{
    delete scene;
    delete view;
    delete layout;
}


bool CaptureImage::eventFilter(QObject* obj, QEvent* event)
{
    if (event->type() == QEvent::KeyPress)
    {
        auto key = static_cast<QKeyEvent*>(event);
        if ((key->key() == Qt::Key_Escape))
        {
            auto func = std::bind(&CaptureImage::close, this);
            Animation::fade(this, 200, 0.4, 0.0, &func);
            return true;
        }
    }

    return QObject::eventFilter(obj, event);
}
