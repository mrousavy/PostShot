#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include <QtCore>
#include <QScreen>
#include <QApplication>

namespace ScreenManager
{
QPoint getTopLeft()
{
    int lX = 0, lY = 0;
    foreach(auto screen, QApplication::screens())
    {
        int cX = screen->geometry().x();
        int cY = screen->geometry().y();
        if (cX < lX)
            lX = cX;
        if (cY < lY)
            lY = cY;
    }
    return QPoint(lX, lY);
}

QPoint getBottomRight()
{
    int hX = 0, hY = 0;
    foreach(auto screen, QApplication::screens())
    {
        int cX = screen->geometry().x() + screen->geometry().width();
        int cY = screen->geometry().y() + screen->geometry().height();
        if (cX > hX)
            hX = cX;
        if (cY > hY)
            hY = cY;
    }
    return QPoint(hX, hY);
}

QRect getVirtualDesktop()
{
    QPoint start = getTopLeft();
    QPoint end = getBottomRight();
    return QRect(start, end);
}
}

#endif // SCREENMANAGER_H
