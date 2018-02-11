#ifndef CAPTUREIMAGE_H
#define CAPTUREIMAGE_H

#include <QWidget>
#include <QPixmap>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "Modules/WindowHelper.h"


class CaptureImage : public QWidget
{
    Q_OBJECT
public:
    /*!
     * Create a new object of the Capture Image Window
     */
    explicit CaptureImage(QWidget* parent = nullptr);
    ~CaptureImage();

signals:

public slots:

private:
    QGraphicsScene* scene;
    QGraphicsView* view;
    QLayout* layout;
    QGraphicsRectItem* rect;
    QPixmap image;
    QList<Helper::Window> windows;
    QRect capture;

private:
    void close();

    bool onKeyDown(QEvent* event);
    bool onMouseMove(QMouseEvent* event);
    bool onMouseDown(QMouseEvent* event);
    bool onMouseUp(QMouseEvent* event);

protected:
    /*!
     * Qt event handler (key press)
     */
    bool eventFilter(QObject* obj, QEvent* event);
};

#endif // CAPTUREIMAGE_H
