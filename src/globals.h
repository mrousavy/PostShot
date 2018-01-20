#ifndef GLOBALS_H
#define GLOBALS_H

#include <QtCore/QtGlobal>

#if defined(UGLOBALHOTKEY_LIBRARY)
#  define HOTKEY_EXPORT Q_DECL_EXPORT
#elif defined(HOTKEY_NOEXPORT)
#  define HOTKEY_EXPORT
#else
#  define HOTKEY_EXPORT Q_DECL_IMPORT
#endif

#endif // GLOBALS_H
