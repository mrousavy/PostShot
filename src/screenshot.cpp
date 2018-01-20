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

QPixmap Screenshot::getScreenshotFull()
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
    QPixmap final(w, h);
    QPainter painter(&final);
    final.fill(Qt::black);
    foreach (auto scr, scrs)
    {
        painter.drawPixmap(QPoint(p, 0), scr);
        p += scr.width();
    }
    return final;
}

          array[(x + width * y) * 3] = red;
          array[(x + width * y) * 3+1] = green;
          array[(x + width * y) * 3+2] = blue;
       }

    CImg<unsigned char> pic(array,width,height,1,3);
    pic.save_png("blah.png");
}



#elif defined(Q_OS_MACX)
    // Mac OS X

#endif
