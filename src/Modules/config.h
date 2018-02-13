#ifndef CONFIG_H
#define CONFIG_H
#include <QString>

struct Config
{
public:
    static void readConfig();

    /*!
     * \brief imageHotkey The hotkey to instantly
     * open Image mode
     */
    static QString imageHotkey;
    /*!
     * \brief gifHotkey The hotkey to instantly
     * open GIF mode
     */
    static QString gifHotkey;
    /*!
     * \brief askSave Ask for file path after
     * cropping an image
     */
    static bool askSave;
};

#endif // CONFIG_H
