#include "screenshot.h"

#include <QtCore>
#include <QtWidgets>
#include <QList>

#include "Modules/screenmanager.h"


QPixmap Screenshot::getScreenshot(int fromX, int fromY, int toX, int toY)
{
    QScreen *screen = QGuiApplication::primaryScreen();
    if (!screen)
        throw std::exception("Could not get primary screen!");

    return screen->grabWindow(0);
}

QPixmap Screenshot::getScreenshotFull()
{
    auto screens = QGuiApplication::screens();
    if (screens.length() < 1)
        throw std::exception("No screens were found!");

    QRect rect = ScreenManager::getVirtualDesktop();

    int offsetX = - rect.left(); // e.g. -1920 if screen#2 is left of #1
    int offsetY = - rect.top();

    QPixmap final(rect.width(), rect.height());
    final.fill(Qt::transparent);
    QPainter painter(&final);

    foreach (QScreen* screen, screens)
    {
        QRect position = screen->availableGeometry();
        position.setLeft(position.left() + offsetX);
        position.setTop(position.top() + offsetY);
        position.setRight(position.right() + offsetX);
        position.setBottom(position.bottom() + offsetY);

        painter.drawPixmap(position,
                           screen->grabWindow(0));
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
