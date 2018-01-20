#ifndef SCREENSHOT_H
#define SCREENSHOT_H

#include <QPixmap>

namespace Screenshot
{
    /*!
     * \brief getScreenshot Get a Screenshot from the Desktop
     * with the given coordinates
     * \param fromX The x coordinate from where the rectangle starts (top-left)
     * \param fromY The y coordinate from where the rectangle starts (top-left)
     * \param toX The x coordinate to which the rectangle goes (bottom-right)
     * \param toY The y coordinate to which the rectangle goes (bottom-right)
     */
    QPixmap getScreenshot(int fromX, int fromY, int toX, int toY);

    /*!
     * \brief getScreenshotFull Get a Screenshot from all desktops
     */
    QPixmap* getScreenshotFull();

    /*!
     * \brief getScreenshotPrimary Get a Screenshot from the Primary Screen
     */
    QPixmap getScreenshotPrimary();

    /*!
     * \brief getScreenshotWindow Get a Screenshot from the given Window ID
     * \param window The handle to the qt window
     */
    QPixmap getScreenshotWindow(const WId window);

    /*!
     * \brief getScreenshotWindow Get a Screenshot from the given Qt Widget
     * \param window The handle to the qt window
     */
    QPixmap getScreenshotWindow(const QWidget& widget);
}

#endif // SCREENSHOT_H
