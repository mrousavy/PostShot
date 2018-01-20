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



#elif defined(Q_OS_X11)



    // Linux Xorg (X11)
    #include <X11/Xlib.h>
    #include <X11/X.h>
    #include <cstdio>
    #include <CImg.h>
    using namespace cimg_library;

void Screenshot::getScreenshot(POINT from, POINT to)
{
    Display *display = XOpenDisplay(NULL);
    Window root = DefaultRootWindow(display);

    XWindowAttributes gwa;

    XGetWindowAttributes(display, root, &gwa);
    int width = gwa.width;
    int height = gwa.height;


    XImage *image = XGetImage(display,root, 0,0 , width,height,AllPlanes, ZPixmap);

    unsigned char *array = new unsigned char[width * height * 3];

    unsigned long red_mask = image->red_mask;
    unsigned long green_mask = image->green_mask;
    unsigned long blue_mask = image->blue_mask;

    for (int x = 0; x < width; x++)
       for (int y = 0; y < height ; y++)
       {
          unsigned long pixel = XGetPixel(image,x,y);

          unsigned char blue = pixel & blue_mask;
          unsigned char green = (pixel & green_mask) >> 8;
          unsigned char red = (pixel & red_mask) >> 16;

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
