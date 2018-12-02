#ifndef IMAGEMANIPULATION_H
#define IMAGEMANIPULATION_H
#include <QtCore>
#include <QPixmap>
#include <QColor>

namespace ImageManipulation
{
QImage drawWindowShadow(const QImage& image);
void chooseSaveImage(const QImage& image);
void quickSaveImage(const QImage& image);
bool fileExists(const QString& path);
QString desktopFolder();
}

#endif // IMAGEMANIPULATION_H
