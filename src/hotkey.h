#ifndef HOTKEY_H
#define HOTKEY_H

#include <QWidget>
#include <QAbstractNativeEventFilter>
#include <QSet>

#if defined(Q_OS_LINUX)
#include "xcb/xcb.h"
#include "xcb/xcb_keysyms.h"
#elif defined(Q_OS_MAC)
#include <Carbon/Carbon.h>
#endif

#include "keysequence.h"
#include "globals.h"

#if defined(Q_OS_LINUX)
struct HotkeyData {
    xcb_keycode_t keyCode;
    int mods;
    bool operator ==(const HotkeyData& data) const {
        return data.keyCode == this->keyCode && data.mods == this->mods;
    }
};
#endif

enum class Modifier
{
    Alt     = 0x0001,
    Control = 0x0002,
    Shift   = 0x0004,
    Windows = 0x0008
};

class HOTKEY_EXPORT Hotkey : public QWidget
        #if defined(Q_OS_LINUX)
        , public QAbstractNativeEventFilter
        #endif
{
    Q_OBJECT
public:
    explicit Hotkey(QWidget *parent, const QString& keySeq, size_t id = 1);
    void registerHotkey(const QString& keySeq, size_t id = 1);
    void registerHotkey(const KeySequence& keySeq, size_t id = 1);
    void unregisterHotkey(size_t id = 1);
    void unregisterAllHotkeys();
    ~Hotkey();
protected:
    #if defined(Q_OS_WIN)
    bool winEvent (MSG* message, long* result);
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);
    #elif defined(Q_OS_LINUX)
    bool nativeEventFilter(const QByteArray &eventType, void *message, long *result);
    bool linuxEvent(xcb_generic_event_t *message);
    void regLinuxHotkey(const KeySequence& keySeq, size_t id);
    void unregLinuxHotkey(size_t id);
    #endif
public:
    #if defined (Q_OS_MAC)
    void onHotkeyPressed(size_t id);
    #endif
signals:
    void activated(size_t id);
private:
    #if defined(Q_OS_WIN)
    QSet<size_t> Registered;
    #elif defined(Q_OS_LINUX)
    QHash<size_t, HotkeyData> Registered;
    xcb_connection_t* X11Connection;
    xcb_window_t X11Wid;
    xcb_key_symbols_t* X11KeySymbs;
    #elif defined(Q_OS_MAC)
    QHash<size_t, EventHotKeyRef> HotkeyRefs;
    #endif
};

#endif // HOTKEY_H
