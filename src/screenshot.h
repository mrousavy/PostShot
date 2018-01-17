#ifndef SCREENSHOT_H
#define SCREENSHOT_H

namespace Screenshot
{
    /*!
     * \brief Get a Screenshot from the Desktop
     * with the given coordinates
     * \param fromX The x coordinate from where the rectangle starts (top-left)
     * \param fromY The y coordinate from where the rectangle starts (top-left)
     * \param toX The x coordinate to which the rectangle goes (bottom-right)
     * \param toY The y coordinate to which the rectangle goes (bottom-right)
     */
    void getScreenshot(int fromX, int fromY, int toX, int toY);
}

#endif // SCREENSHOT_H
