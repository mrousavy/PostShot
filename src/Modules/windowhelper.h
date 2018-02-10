#ifndef WINDOWHELPER_H
#define WINDOWHELPER_H

//#include <QObject>
#include <QtCore>
#include <QDebug>

// Ignore {0,0,0,0} windows
#define IGNORE_NULLS

namespace Helper {

#if defined(Q_OS_WIN)
#include <Windows.h>

struct Window
{
    QRect rect;
    int z;
};

static int currz;

inline BOOL CALLBACK enumWindowsProc(
        __in  HWND hWnd,
        __in  LPARAM lParam)
{
  QList<Window>* windows = reinterpret_cast<QList<Window>*>(lParam);
  RECT rect;
  GetWindowRect(hWnd, &rect);

#ifdef IGNORE_NULLS
  if (rect.left == 0  && rect.top == 0 &&
      rect.right == 0 && rect.bottom == 0)
      return TRUE;
#endif

  QRect qrect(rect.left, rect.top, rect.right, rect.bottom);

  Window window;
  window.rect = qrect;
  window.z = currz++;
  windows->append(window);

  return TRUE;
}

inline QList<Window> getAllWindows()
{
    currz = 0;
    QList<Window> windows;
    BOOL success = EnumWindows(enumWindowsProc, reinterpret_cast<LPARAM>(&windows));
    if (!success) throw std::exception("Could not enumerate windows!");
    return windows;
}

#elif defined(Q_OS_X11)
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>

QList<QRect> getAllWindows()
{
    Atom a = XInternAtom(m_pDisplay, "_NET_CLIENT_LIST" , true);
    Atom actualType;
    int format;
    unsigned long numItems, bytesAfter;
    unsigned char *data =0;
    int status = XGetWindowProperty(m_pDisplay,
                                    rootWindow,
                                    a,
                                    0L,
                                    (~0L),
                                    false,
                                    AnyPropertyType,
                                    &actualType,
                                    &format,
                                    &numItems,
                                    &bytesAfter,
                                    &data);
    QList<QRect> windows;
    if (status >= Success && numItems)
    {
        Q_ASSERT(format == 32);
        quint32 *array = (quint32*) data;
        for (quint32 k = 0; k < numItems; k++)
        {
            Window w = (Window) array[k];

            windows.append(w); // TODO: Build QRect
        }
        XFree(data);
    }
    return windows;
}
#endif

}

#endif // WINDOWHELPER_H
