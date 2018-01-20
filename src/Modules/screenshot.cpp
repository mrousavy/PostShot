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
    QList<QPixmap> scrs;
    int w = 0, h = 0, p = 0;
    foreach (auto scr, screens)
    {
        QPixmap pix = scr->grabWindow(0);
        w += pix.width();
        if (h < pix.height()) h = pix.height();
        scrs << pix;
    }
    QPixmap* final = new QPixmap(w, h);
    QPainter painter(final);
    final->fill(Qt::transparent);
    foreach (auto scr, scrs)
    {
        painter.drawPixmap(QPoint(p, 0), scr);
        p += scr.width();
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
