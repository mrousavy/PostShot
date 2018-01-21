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
#endif
#endif // WINDOWHELPER_H
