#ifndef CAPTUREIMAGE_H
#define CAPTUREIMAGE_H

#include <QWidget>

class CaptureImage : public QWidget
{
    Q_OBJECT
public:
    /*!
     * \brief fadeIn Create a new object of the Capture Image Window
     */
    explicit CaptureImage(QWidget *parent = nullptr);

signals:

public slots:

private:

protected:
    /*!
     * \brief eventFilter Qt event handler (key press)
     */
    bool eventFilter(QObject* obj, QEvent* event);
};

#endif // CAPTUREIMAGE_H
