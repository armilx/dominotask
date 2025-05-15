#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <random>
#include <iomanip>

using namespace std;

// Клас який описує координати клітинки 
class Cell { 
public:
    int row, col;
    // Конструктор створює клітинку за заданими координатами 
    Cell(int r = 0, int c = 0) : row(r), col(c) {}
};
// Клас доміно
class Domino { 
public:
    int a, b; // Значення на обох кінцях доміношки

    //  Конструктор, який ініціалізує доміно з двома числами
    Domino(int a = 0, int b = 0) : a(a), b(b) {}
    // Повертає впорялкований пару числе для унікальної ідентифікації 
    pair<int, int> normaliz() const { 
        return minmax(a, b);
    }
};

class Field { 
public:
    static constexpr int ROWS = 10;
    static constexpr int COLS = 19; 

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

    const string leetters[ROWS] = { 
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

    Field() { 
        for (int i = 0; i < ROWS; ++i) { 
            for (int j = 0; j < COLS; ++j) {
                char ch = letters[i][j];
                if (ch != '*') {
                    regions[ch].emplace_back(i,j);
                }
            }
        }
    }
    bool isDominoCell(int i, int j) const { 
        return layout[i][j] == '?';
    }
};
