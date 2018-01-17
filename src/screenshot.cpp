#include "screenshot.h"

// TODO: REMOVE Q_OS_WIN
#define Q_OS_WIN

// OS Specific include directive
#ifdef Q_OS_WIN
    // Windows
    #include <Windows.h>
    #pragma comment(lib,"user32.lib")
    #pragma comment(lib,"Gdi32.lib")
#elif defined(Q_OS_X11)
    // Linux Xorg (X11)
    #include <X11/Xlib.h>
    #include <X11/X.h>
    #include <cstdio>
    #include <CImg.h>
    using namespace cimg_library;
#elif defined(Q_OS_MACX)
    // Mac OS X
#endif

#endif
