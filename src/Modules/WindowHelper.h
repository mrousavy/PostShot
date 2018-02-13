#ifndef WINDOWHELPER_H
#define WINDOWHELPER_H

#include <QtCore>

// Ignore hidden windows
#define IGNORE_HIDDEN
// Ignore windows with {0,0,0,0} coords
//#define IGNORE_NULLS
// Ignore windows without titles
#define IGNORE_NOTITLE
// Ignore fullscreen overlays
#define IGNORE_OVERLAYS

namespace WindowHelper
{
    struct WindowSpec
    {
    public:
        WindowSpec() {}
        WindowSpec(QRect wrect, int wz, QString wname)
            : rect(wrect), z(wz), name(wname) {}

        QRect rect;
        int z;
        QString name;
    };

    static int currz;
    QList<WindowSpec> getAllWindows();
}

#endif // WINDOWHELPER_H
