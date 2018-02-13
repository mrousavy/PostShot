#include "Modules/WindowHelper.h"

#include <QtCore>
#include <QDebug>
#include <string>
#include "Modules/Screenmanager.h"

namespace WindowHelper
{

#ifdef Q_OS_WIN
#include <Windows.h>
    int rw(RECT rect)
    {
        return rect.left - rect.right;
    }
    int rh(RECT rect)
    {
        return rect.top - rect.bottom;
    }


    inline BOOL CALLBACK enumWindowsProc(__in  HWND hWnd, __in  LPARAM lParam)
    {
#ifdef IGNORE_HIDDEN
        if (!IsWindowVisible(hWnd))
            return TRUE;
#endif
        auto tlength = GetWindowTextLength(hWnd);
#ifdef IGNORE_NOTITLE
        if (tlength == 0)
            return TRUE;
#endif

        auto windows = reinterpret_cast<QList<WindowSpec>*>(lParam);
        RECT rect;
        GetWindowRect(hWnd, &rect);
#ifdef IGNORE_NULLS
        if (rw(rect) < 1 || rh(rect) < 1)
            return TRUE;
#endif
#ifdef IGNORE_OVERLAYS
        QRect desktop = ScreenManager::getVirtualDesktop();
        if (rw(rect) >= desktop.width() && rh(rect) >= desktop.height())
            return TRUE;
#endif

        wchar_t title[256];
        GetWindowText(hWnd, title, 256);
        WindowSpec window;
        window.rect = QRect(rect.left, rect.top, rect.right, rect.bottom);
        window.z = currz++;
        window.name = QString::fromWCharArray(title);

        windows->append(window);

        return TRUE;
    }

    QList<WindowSpec> getAllWindows()
    {
        currz = 0;
        QList<WindowSpec> windows;
        BOOL success = EnumWindows(enumWindowsProc, reinterpret_cast<LPARAM>(&windows));
        if (!success) throw std::runtime_error("Could not enumerate windows!");
        return windows;
    }

#elif defined(Q_OS_LINUX)
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>

    static Display* display;

    inline QList<WindowSpec> getAllWindows()
    {
        if (display == nullptr) display = XOpenDisplay(NULL);

        Atom clients = XInternAtom(display, "_NET_CLIENT_LIST" , true);
        Atom actualType;
        int format;
        unsigned long numItems, bytesAfter;
        unsigned char* data = 0;
        int status = XGetWindowProperty(display, DefaultRootWindow(display),
                                        clients, 0L, (~0L), false, AnyPropertyType,
                                        &actualType, &format, &numItems,
                                        &bytesAfter, &data);
        QList<WindowSpec> windows;
        if (status >= Success && numItems) {
            Q_ASSERT(format == 32);
            quint32* array = (quint32*) data;
            for (quint32 k = 0; k < numItems; k++) {
                Window wId = (Window) array[k];
                Window* root = nullptr;
                int x, y;
                unsigned int w, h, bw, d;
                XGetGeometry(display, wId, root, &x, &y, &w, &h, &bw, &d);
                WindowSpec window(QRect(x, y, w, h), 5, "TEST");
                windows.append(window); // TODO: Build QRect
            }
            XFree(data);
        }
        return windows;
    }
#endif

}
