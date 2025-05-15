#ifndef FIELD_H
#define FIELD_H

#include <string>
#include <map>
#include <vector>
#include "cell.h"

using namespace std;

// Клас, який описує ігрове поле
class Field { 
public:
    static constexpr int ROWS = 10; // Рядки
    static constexpr int COLS = 19; // Стовпці

    const string layout[ROWS] = { 
        "*******?***********",
        "*******?***********",
        "****??*???*********",
        "*****?***?????*****",
        "*?**??*???*********",
        "*?**?****?*????????",
        "????????????****?*?",
        "**?********???**?*?",
        "**???******?****?**",
        "****************?**"
    };

    const string letters[ROWS] = { 
        "*******q***********",
        "*******q***********",
        "****yy*wwe*********",
        "*****u***errtt*****",
        "*o**iu*kkl*********",
        "*o**i****l*zzxxccvv",
        "ppaassddffgg****m*Q",
        "**h********bnn**m*Q",
        "**hjj******b****W**",
        "****************W**"
    };

    map<char, vector<Cell>> regions;

    // Конструктор: який будує карту регіонів за символами
    Field();
    // Перевіряє, чи клітинка призначен для доміно
    bool isDominoCell(int i, int j) const; 
};

#endif 
