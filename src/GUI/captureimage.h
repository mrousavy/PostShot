#ifndef CAPTUREIMAGE_H
#define CAPTUREIMAGE_H

#include <QWidget>
#include <QPixmap>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "Modules/windowhelper.h"


class CaptureImage : public QWidget
{
    Q_OBJECT
public:
    /*!
     * \brief fadeIn Create a new object of the Capture Image Window
     */
    explicit CaptureImage(QWidget* parent = nullptr);
    ~CaptureImage();

signals:

public slots:

private:
    QGraphicsScene* scene;
    QGraphicsView* view;
    QLayout* layout;
    QPixmap image;
    QList<Helper::Window> windows;

protected:
    /*!
     * \brief eventFilter Qt event handler (key press)
     */
    bool eventFilter(QObject* obj, QEvent* event);
};

#endif // CAPTUREIMAGE_H
