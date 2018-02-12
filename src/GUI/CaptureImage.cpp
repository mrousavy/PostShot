#include "GUI/CaptureImage.h"

#include <QKeyEvent>
#include <functional>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVBoxLayout>

#include "GUI/Animation.h"
#include "Modules/Screenmanager.h"
#include "Modules/ImageManipulation.h"
#include "Modules/WindowHelper.h"
#include "Modules/Screenshot.h"

#include <QDebug>
#include <QGraphicsRectItem>

CaptureImage::CaptureImage(QWidget* parent)
    : QWidget(parent, Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint),
      scene(new QGraphicsScene), view(new QGraphicsView(scene, this)),
      layout(new QVBoxLayout(this)), rect(scene->addRect(0, 0, 0, 0)),
      image(Screenshot::getScreenshotFull()), windows(Helper::getAllWindows())
{
    // Window Metadata
    setWindowOpacity(0.0);
    setMouseTracking(true);
    setGeometry(ScreenManager::getVirtualDesktop()); // span across all screens

    // Events setup
    installEventFilter(this); // Handle Keys
    scene->installEventFilter(this); // Handle Mouse

    // QGraphicsScene setup
    auto pmitem = scene->addPixmap(this->image);
    rect->setZValue(pmitem->zValue() + 1);
    rect->setBrush(Qt::gray);
    rect->setPen(QPen(Qt::black));
    rect->setOpacity(0.4);

    // QGraphicsView setup
    //view->setBackgroundBrush(this->image);
    view->setFrameStyle(QFrame::NoFrame); // Disable ~1px borders
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setCacheMode(QGraphicsView::CacheBackground);
    view->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    // Layout setup
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(view);
    setLayout(layout);

    // Window opening
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
    delete rect;
}

void CaptureImage::close()
{
    auto func = std::bind(&QWidget::close, this);
    Animation::fade(this, 200, 0.4, 0.0, &func);
}

bool CaptureImage::onKeyDown(QEvent* event)
{
    auto key = static_cast<QKeyEvent*>(event);
    switch (key->key())
    {
    case Qt::Key_Escape:
        close();
        return true;
    }
    return true;
}

bool CaptureImage::onMouseDown(QMouseEvent* event)
{
    capture.setTopLeft(event->pos());
    return true;
}

bool CaptureImage::onMouseMove(QMouseEvent*)
{
    capture.setBottomRight(mapFromGlobal(QCursor::pos()));
    rect->setRect(capture);
    return true;
}

bool CaptureImage::onMouseUp(QMouseEvent*)
{
    QPixmap cropped = image.copy(capture);
    ImageManipulation::quickSaveImage(cropped);
    close();
    return true;
}

bool CaptureImage::eventFilter(QObject* obj, QEvent* event)
{
    switch (event->type())
    {
    case QEvent::KeyPress:
        return onKeyDown(event);
    case QEvent::MouseButtonPress:
    case QEvent::GraphicsSceneMousePress:
        return onMouseDown(static_cast<QMouseEvent*>(event));
    case QEvent::MouseButtonRelease:
    case QEvent::GraphicsSceneMouseRelease:
        return onMouseUp(static_cast<QMouseEvent*>(event));
    case QEvent::MouseMove:
    case QEvent::GraphicsSceneMouseMove:
        return onMouseMove(static_cast<QMouseEvent*>(event));
    default:
        return QObject::eventFilter(obj, event);
    }
}
