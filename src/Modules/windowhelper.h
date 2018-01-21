#ifndef WINDOWHELPER_H
#define WINDOWHELPER_H

//#include <QObject>
#include <QtCore>
#include <QDebug>

#if defined(Q_OS_WIN)
#include <Windows.h>

BOOL CALLBACK enumWindowsCallback(
  __in  HWND hWnd,
  __in  LPARAM lParam
) {
  QList<QRect>& windows = reinterpret_cast<QList<QRect>&>(lParam);
  QRect rect;
  windows.append(rect);

  return TRUE;
}

QList<QRect> getAllWindows()
{
    qDebug() << "Get windows..\n";
    QList<QRect> windows;
    BOOL success = EnumWindows(&enumWindowsCallback, reinterpret_cast<LPARAM>(&windows));
    qDebug() << "Enuming windows..\n";
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

#endif // WINDOWHELPER_H
