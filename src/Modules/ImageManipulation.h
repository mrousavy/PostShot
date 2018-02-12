#ifndef IMAGEMANIPULATION_H
#define IMAGEMANIPULATION_H
#include <QtCore>
#include <QPixmap>

namespace ImageManipulation
{
void saveImage(const QPixmap& pixelmap);
void quickSaveImage(const QPixmap& pixelmap);
bool fileExists(const QString& path);
QString desktopFolder();
}

#endif // IMAGEMANIPULATION_H
