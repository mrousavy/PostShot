#include "screenshot.h"

#include <QtCore>
#include <QtWidgets>
#include <QList>


QPixmap Screenshot::getScreenshot(int fromX, int fromY, int toX, int toY)
{
    QScreen *screen = QGuiApplication::primaryScreen();
    if (!screen)
        throw std::exception("Could not get primary screen!");

    return screen->grabWindow(0);
}

QPixmap* Screenshot::getScreenshotFull()
{
    auto screens = QGuiApplication::screens();
    if (screens.length() < 1)
        throw std::exception("No screens were found!");
    QList<QPixmap> pixmaps;
    int w = 0, h = 0, p = 0;
    foreach (auto scr, screens)
    {
        QPixmap pixmap = scr->grabWindow(0);
        w += pixmap.width();
        if (h < pixmap.height()) h = pixmap.height();
        pixmaps << pixmap;
    }

    QPixmap* final = new QPixmap(w, h);
    final->fill(Qt::transparent);
    QPainter painter(final);
    foreach (auto pixmap, pixmaps)
    {
        painter.drawPixmap(QPoint(p, 0), pixmap);
        p += pixmap.width();
    }
    return final;
}

QPixmap Screenshot::getScreenshotPrimary()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    if (!screen)
        throw std::exception("Could not get primary screen!");

    return screen->grabWindow(0);
}

QPixmap Screenshot::getScreenshotWindow(const WId window)
{
    QScreen *screen = QGuiApplication::primaryScreen();
    if (!screen)
        throw std::exception("Could not get primary screen!");

    return screen->grabWindow(window);
}

QPixmap Screenshot::getScreenshotWindow(const QWidget& widget)
{
    return getScreenshotWindow(widget.winId());
}
