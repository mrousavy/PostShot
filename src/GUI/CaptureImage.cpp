#include "GUI/CaptureImage.h"

#include <QKeyEvent>
#include <QVBoxLayout>
#include <algorithm>
#include <functional>
#include <QLabel>
#include <QPainter>

#include "GUI/Animation.h"
#include "Modules/Screenmanager.h"
#include "Modules/ImageManipulation.h"
#include "Modules/WindowHelper.h"
#include "Modules/Screenshot.h"

#include <QDebug>

// Fade window opening and closing?
//#define FADE
// ..if yes, to/from what opacity?
#define OPACITY 1.0

CaptureImage::CaptureImage(QWidget* parent)
    : QWidget(parent, Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint),
      windows(WindowHelper::getAllWindows()), capture(0, 0, 0, 0),
      image(Screenshot::getScreenshotFull())
{
    // Window Metadata
    setMouseTracking(true);
    setGeometry(ScreenManager::getVirtualDesktop()); // span across all screens

    // Events setup
    installEventFilter(this); // Handle Keys
    shortcut = new QShortcut(QKeySequence("Ctrl+A"), this);
    connect(shortcut, &QShortcut::activated, this, &CaptureImage::captureAll);

    setCursor(Qt::CrossCursor);
#ifdef FADE
    setWindowOpacity(0.0);
#endif

//    for (auto window : windows) {
//        QRectF rect(mapFromGlobal(window.rect.topLeft()),
//                    mapFromGlobal(window.rect.bottomRight()));

//        // TODO: Do we really need that? Overlays are last-z-index anyway
//        if (rect.height() + 5 < this->height() &&
//                rect.width() + 5 < this->width()) {
//            qDebug() << window.name << window.z << window.rect;
//            scene->addRect(rect, QPen(Qt::red), Qt::blue);
//        }
//    }
}

CaptureImage::~CaptureImage()
{
    delete label;
    delete shortcut;
}

void CaptureImage::show()
{
    QWidget::show();
    activateWindow();
#ifdef FADE
    Animation::fade(this, 200, 0.0, OPACITY);
#endif
}

void CaptureImage::close()
{
#ifdef FADE
    auto func = std::bind(&QWidget::close, this);
    Animation::fade(this, 200, OPACITY, 0.0, &func);
#else
    QWidget::close();
#endif
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
    start = event->pos();
    return true;
}

bool CaptureImage::onMouseMove(QMouseEvent*)
{
    end = mapFromGlobal(QCursor::pos());
    updateCapture();
    update();
    return true;
}

bool CaptureImage::onMouseUp(QMouseEvent*)
{
    if (capture.width() > 7 && capture.height() > 7)
        captureFinish();
    return true;
}

void CaptureImage::updateCapture()
{
    using namespace std;
    capture.setLeft(min(start.x(), end.x()));
    capture.setTop(min(start.y(), end.y()));
    capture.setRight(max(start.x(), end.x()));
    capture.setBottom(max(start.y(), end.y()));
    // TODO: draw rect
}

void CaptureImage::captureFinish()
{
    setCursor(Qt::WaitCursor);
    QPixmap cropped = image.copy(capture);
    QImage shadowImage = ImageManipulation::drawWindowShadow(cropped.toImage());
    ImageManipulation::quickSaveImage(shadowImage);
    setCursor(Qt::ArrowCursor);
    close();
}

void CaptureImage::captureAll()
{
    start = QPoint(0, 0);
    end = QPoint(width(), height());
    updateCapture();
    qApp->processEvents();
    captureFinish();
}

void CaptureImage::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, width(), height(), image);

    QColor color(Qt::gray);
    color.setAlphaF(0.3);
    painter.fillRect(capture, color);
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
