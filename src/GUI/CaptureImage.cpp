#include "GUI/CaptureImage.h"

#include <QKeyEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QGraphicsRectItem>
#include <algorithm>
#include <functional>

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
      scene(new QGraphicsScene), view(new QGraphicsView(scene, this)),
      layout(new QVBoxLayout(this)), rect(scene->addRect(0, 0, 0, 0)),
      windows(WindowHelper::getAllWindows()), capture(0, 0, 0, 0),
      image(Screenshot::getScreenshotFull())
{
    // Window Metadata
    setMouseTracking(true);
    setGeometry(ScreenManager::getVirtualDesktop()); // span across all screens

    // Events setup
    installEventFilter(this); // Handle Keys
    scene->installEventFilter(this); // Handle Mouse
    shortcut = new QShortcut(QKeySequence("Ctrl+A"), this);
    connect(shortcut, &QShortcut::activated, this, &CaptureImage::captureAll);

    // QGraphicsScene setup
    scene->addPixmap(this->image);
    rect->setZValue(1);
    rect->setBrush(Qt::gray);
    rect->setPen(QPen(Qt::black, 2));
    rect->setOpacity(0.3);
    rect->setRect(capture);

    // QGraphicsView setup
    //view->setBackgroundBrush(this->image);
    view->setFrameStyle(QFrame::NoFrame); // Disable ~1px borders
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setCacheMode(QGraphicsView::CacheBackground);
    view->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    // Layout setup
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(view);
    setLayout(layout);

    setCursor(Qt::CrossCursor);
#ifdef FADE
    setWindowOpacity(0.0);
#endif

    for (auto window : windows) {
        qDebug() << window.name << window.z << window.rect;
    }
}

CaptureImage::~CaptureImage()
{
    delete scene;
    delete view;
    delete layout;
    delete rect;
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
    rect->setRect(capture);
}

void CaptureImage::captureFinish()
{
    setCursor(Qt::WaitCursor);
    QPixmap cropped = image.copy(capture);
    ImageManipulation::quickSaveImage(cropped);
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
