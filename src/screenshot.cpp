#include "screenshot.h"

// TODO: REMOVE Q_OS_WIN
#define Q_OS_WIN

// OS Specific include directive
#ifdef Q_OS_WIN
    // Windows
    #include <Windows.h>
    #pragma comment(lib,"user32.lib")
    #pragma comment(lib,"Gdi32.lib")
#elif defined(Q_OS_X11)
    // Linux Xorg (X11)
    #include <X11/Xlib.h>
    #include <X11/X.h>
    #include <cstdio>
    #include <CImg.h>
    using namespace cimg_library;
#elif defined(Q_OS_MACX)
    // Mac OS X
#endif

// OS Specific Screenshot implementations
#ifdef Q_OS_WIN
void Screenshot::getScreenshot(int fromX, int fromY, int toX, int toY)
{
    // copy screen to bitmap
    HDC     hScreen = GetDC(NULL);
    HDC     hDC     = CreateCompatibleDC(hScreen);
    HBITMAP hBitmap = CreateCompatibleBitmap(hScreen, abs(toX-fromX), abs(toY-fromY));
    HGDIOBJ old_obj = SelectObject(hDC, hBitmap);
    BOOL    bRet    = BitBlt(hDC, 0, 0, abs(toX-fromX), abs(toY-fromY), hScreen, fromX, fromY, SRCCOPY);

    // save bitmap to clipboard
    OpenClipboard(NULL);
    EmptyClipboard();
    SetClipboardData(CF_BITMAP, hBitmap);
    CloseClipboard();

    // clean up
    SelectObject(hDC, old_obj);
    DeleteDC(hDC);
    ReleaseDC(NULL, hScreen);
    DeleteObject(hBitmap);
}
#elif defined(Q_OS_X11)
#endif
