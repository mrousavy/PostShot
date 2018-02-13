#ifndef CAPTUREIMAGE_H
#define CAPTUREIMAGE_H

#include <QWidget>
#include <QPixmap>
#include <QLabel>
#include <QShortcut>

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

    void showNormal() = delete;
    void showMinimized() = delete;
    void showMaximized() = delete;
    void showFullScreen() = delete;
    void show();
    void close();
signals:

public slots:

private:
    QLabel* label;
    QShortcut* shortcut;
    QList<WindowHelper::WindowSpec> windows;
    QPoint start, end;
    QRect capture;
    QPixmap image;

private:
    bool onKeyDown(QEvent* event);
    bool onMouseMove(QMouseEvent* event);
    bool onMouseDown(QMouseEvent* event);
    bool onMouseUp(QMouseEvent* event);

    void updateCapture();
    void captureFinish();
    void captureAll();

protected:
    void paintEvent(QPaintEvent *event);
    bool eventFilter(QObject* obj, QEvent* event);
};

#endif // CAPTUREIMAGE_H
