#ifndef HOTKEY_H
#define HOTKEY_H

enum class Modifier
{
    Alt     = 0x0001,
    Control = 0x0002,
    Shift   = 0x0004,
    Windows = 0x0008
};

class Hotkey
{
public:
    Hotkey(Modifier modifier, char key);
    ~Hotkey();
};

#endif // HOTKEY_H
