#ifndef SETTING_H_INCLUDED
#define SETTING_H_INCLUDED

#include <string>

enum MenuType {
    EMPTY_MENU, PLAYGAME, HIGHSCORE, HELP, INFORMATION, EXIT
};

class Setting {
public:

    Setting();
    virtual ~Setting();
    static const char* FONT;

};

#endif // SETTING_H_INCLUDED

