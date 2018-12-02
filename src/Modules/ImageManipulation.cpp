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

QT_BEGIN_NAMESPACE
    extern Q_WIDGETS_EXPORT void qt_blurImage(QPainter *p, QImage &blurImage, qreal radius, bool quality, bool alphaOnly, int transposed = 0 );
QT_END_NAMESPACE

namespace ImageManipulation
{
    QImage drawWindowShadow(const QImage& image)
    {
        // Create new Img with same Size
        QSize fullSize(image.size().width() + 30, image.size().height() + 30);
        QImage shadowImage(fullSize, QImage::Format_ARGB32_Premultiplied);

        // Fill it with transparency
        QPainter painter(&shadowImage);
        QPen pen;
        pen.setStyle(Qt::NoPen);
        painter.setPen(pen);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.fillRect(QRect(0, 0, fullSize.width(), fullSize.height()), QColor(255, 255, 255, 0));

        // Draw Rounded Rectangle as Shadow
        QPainterPath path;
        path.addRoundedRect(QRect(0, 0, fullSize.width(), fullSize.height()), 15, 15);
        painter.fillPath(path, QColor(110, 152, 226));
        painter.drawPath(path);
        painter.end();

        QImage blurred(shadowImage.size(), QImage::Format_ARGB32_Premultiplied);
        blurred.fill(0);
        QPainter blurPainter(&blurred);
        qt_blurImage(&blurPainter, blurred, 5.0, true, false);
        blurPainter.end();


        return blurred;



        // Draw Original Img over background
        painter.drawImage(0, 0, blurred);
        painter.drawImage(15, 15, image);

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
