#ifndef IMAGEMANIPULATION_H
#define IMAGEMANIPULATION_H
#include <QtCore>
#include <QPixmap>

namespace ImageManipulation
{
void chooseSaveImage(const QPixmap& pixelmap);
void quickSaveImage(const QPixmap& pixelmap);
bool fileExists(const QString& path);
QString desktopFolder();
}

#endif // IMAGEMANIPULATION_H
