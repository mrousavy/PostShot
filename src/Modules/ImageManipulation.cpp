#include "ImageManipulation.h"
#include <QtCore>
#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QImageWriter>
#include <QPainter>
#include <QColor>
#include <QGraphicsDropShadowEffect>
#include <QGraphicsEffect>

#define BLUR_DISTANCE 15

QT_BEGIN_NAMESPACE
    extern Q_WIDGETS_EXPORT void qt_blurImage(QPainter *p, QImage &blurImage, qreal radius, bool quality, bool alphaOnly, int transposed = 0 );
QT_END_NAMESPACE

namespace ImageManipulation
{
    QImage drawWindowShadow(const QImage& image)
    {
        // Create new Img with same Size
        QSize fullSize(image.size().width() + 2 * BLUR_DISTANCE, image.size().height() + 2 * BLUR_DISTANCE);

        QImage scaled = image.scaled(fullSize);

        QImage temp(fullSize, QImage::Format_ARGB32_Premultiplied);
        temp.fill(0);
        QPainter tempPainter(&temp);
        tempPainter.setCompositionMode(QPainter::CompositionMode_Source);
        tempPainter.drawImage(QPointF(BLUR_DISTANCE, BLUR_DISTANCE), scaled);
        tempPainter.end();

        QImage shadowImage(fullSize, QImage::Format_ARGB32_Premultiplied);
        QImage blurred(shadowImage.size(), QImage::Format_ARGB32_Premultiplied);
        blurred.fill(0);
        QPainter blurPainter(&blurred);
        qt_blurImage(&blurPainter, temp, 5.0, true, false);
        blurPainter.end();


        return blurred;

        return shadowImage;
    }

    void chooseSaveImage(const QImage& image)
    {
        const QString format = "png";
        QString initialPath = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
        if (initialPath.isEmpty())
            initialPath = QDir::currentPath();
        initialPath += QObject::tr("/untitled.") + format;

        QFileDialog fileDialog(nullptr, QObject::tr("Save As"), initialPath);
        fileDialog.setAcceptMode(QFileDialog::AcceptSave);
        fileDialog.setFileMode(QFileDialog::AnyFile);
        fileDialog.setDirectory(initialPath);
        QStringList mimeTypes;
        foreach (const QByteArray &bf, QImageWriter::supportedMimeTypes())
            mimeTypes.append(QLatin1String(bf));
        fileDialog.setMimeTypeFilters(mimeTypes);
        fileDialog.selectMimeTypeFilter("image/" + format);
        fileDialog.setDefaultSuffix(format);
        if (fileDialog.exec() != QDialog::Accepted)
            return;
        const QString filename = fileDialog.selectedFiles().first();
        if (!image.save(filename)) {
            QMessageBox::critical(nullptr, QObject::tr("Save Error"),
                                  QObject::tr("The image could not be saved to \"%1\".")
                                  .arg(QDir::toNativeSeparators(filename)));
        }
    }

    bool fileExists(const QString& path)
    {
        const QFileInfo check_file(path);
        return check_file.exists() && check_file.isFile();
    }

    QString desktopFolder()
    {
        auto path = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
        return path.isEmpty() ? "." : path;
    }

    QString quickPath(const int number = 1)
    {
        return desktopFolder() + "/Screenshot" + QString::number(number) + ".png";
    }

    void quickSaveImage(const QImage& image)
    {
        int i = 1;
        for (; fileExists(quickPath(i)); i++) {}
        QString filename = quickPath(i);

        if (!image.save(filename)) {
            QMessageBox::critical(nullptr, QObject::tr("Save Error"),
                                  QObject::tr("The image could not be saved to \"%1\".")
                                  .arg(QDir::toNativeSeparators(filename)));
        }
    }
}
