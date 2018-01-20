#include "hotkey.h"

#define Q_OS_WIN


#ifdef Q_OS_WIN
    #include <Windows.h>
    #include <exception>

Hotkey::Hotkey(Modifier modifier, char key)
{
    //if (!RegisterHotKey(NULL, 1, modifier, key))
   // {
    //    throw std::exception("Could not register hotkey!");
    //}
}

Hotkey::~Hotkey()
{

}

#endif
