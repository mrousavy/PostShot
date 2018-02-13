#include "ImageManipulation.h"
#include <QtCore>
#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QImageWriter>

namespace ImageManipulation
{
    void chooseSaveImage(const QPixmap& pixelmap)
    {
        const QString format = "png";
        QString initialPath = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
        if (initialPath.isEmpty())
            initialPath = QDir::currentPath();
        initialPath += QObject::tr("/untitled.") + format;

        QFileDialog fileDialog(NULL, QObject::tr("Save As"), initialPath);
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
        if (!pixelmap.save(filename)) {
            QMessageBox::critical(NULL, QObject::tr("Save Error"),
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

    void quickSaveImage(const QPixmap& pixelmap)
    {
        int i = 1;
        for (; fileExists(quickPath(i)); i++) {}
        QString filename = quickPath(i);

        if (!pixelmap.save(filename)) {
            QMessageBox::critical(NULL, QObject::tr("Save Error"),
                                  QObject::tr("The image could not be saved to \"%1\".")
                                  .arg(QDir::toNativeSeparators(filename)));
        }
    }
}
