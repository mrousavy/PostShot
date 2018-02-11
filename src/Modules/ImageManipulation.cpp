#include "ImageManipulation.h"
#include <QtCore>
#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QImageWriter>


namespace ImageManipulation
{
    void saveImage(QPixmap& pixelmap)
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
        const QString fileName = fileDialog.selectedFiles().first();
        if (!pixelmap.save(fileName)) {
            QMessageBox::warning(NULL, QObject::tr("Save Error"), QObject::tr("The image could not be saved to \"%1\".")
                                 .arg(QDir::toNativeSeparators(fileName)));
        }
    }
}
