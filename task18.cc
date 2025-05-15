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
    // Конструктор: який будує карту регіонів за символами
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
    // Перевіряє, чи клітинка призначеною для доміно
    bool isDominoCell(int i, int j) const { 
        return layout[i][j] == '?';
    }
};

class DominoSolver {
public:
    static vector<Domino> generateDominoes(){
        vector<Domino> dominoes;
        for (int i = 0; i <= 6; ++i) {
            for (int j= i; j <= 6; ++j) { 
                dominoes.emplace_back(i, j);
            }
        }
        return dominoes;
    }

    static void printGridAscii(const int grid[Field::ROWS][Field::COLS], const Field& field) { 
        const int cellHeight = 3;
        const int cellWidth = 5;

        for (int row = 0; row < Field::ROWS; ++row) { 
            for (int line = 0; line < cellHeight; ++line) { 
                for (int col = 0; col < Field::COLS; ++col) { 
                    if (!field.isDominoCell(row, col)) {
                        cout << string(cellWidth, ' ');
                    } else {
                        int val = grid[row][col];
                        if (line == 0) {
                            cout << "+---+";
                        } else if (line == 1) {
                            if (val != -1) {
                                cout << "| " << val << " |";
                            } else {
                                cout << "|   |";
                            }
                        } else if (line == 2) {
                            cout << "+---+";
                        }
                    }
                }
                if (line == 1 && row == 2) {
                    cout << "   ← [1,2,3]";
                }
                cout << '\n';
            }   
        }
        cout << "      ↑                   ↑               ↑\n";
        cout << "    [1,4]               [1,2]          [0,2,3]\n";
    }

    static bool validataTargetSolution(const map<char, Domino>& targetSolution, const Field& field) {
        map<pair<int, int>,int> count;
        for (const auto& [ch,dom] : targetSolution) {
            ++count[dom.normalized()];
        }
        set<pair<int, int>> expected;
        for (const auto& d : generateAllDominoes()) {
            expected.insert(d.normalized());
        }
        bool errorFound = false;

        for (const auto& [dom, c] : count) {
            if (c > 1) {
                cout << "Помилка: доміношка {" << dom.first << ", " << dom.second << "} використовується" << c << " рази(-и)\n";

            }
        }
        for (const auto& dom : expected) {
            if (count[dom] == 0) {
                cout << "Помилка: доміношка {" << dom.first << ", " << dom.second << "} відсутня на ігровому полі\n";
                errorFound = true;
            }
        }
        set<int> allowed_col1 = {1, 4};
        set<int> allowed_col2 = {1, 2};
        set<int> allowed_col3 = {0, 2, 3};
        set<int> allowed_col4 = {1, 2, 3};

        for (const auto& [ch, dom] : targetSolution) {
            const auto& cells = field.regions.at(ch);
            for (int i = 0; i < 2; ++i) {
                const Cell& cell = cells[i];
                int value = (i == 0 ? dom.a : dom.b);

                if (cell.col == 1 && allowed_col1.count(value) == 0) {
                    cout << "Помилка: у стовпці 2 (позиція [" << cell.row << "][1]) не може бути значення " << value << "\n";
                    errorFound = true;
                }
                if (cell.col == 5 && allowed_col5.count(value) == 0) {
                    cout << "Помилка: у стовпці 6 (позиція [" << cell.row << "][5]) не може бути значення " << value << "\n";
                    errorFound = true;
                }
                if (cell.col == 8 && allowed_col8.count(value) == 0) {
                    cout << "Помилка: у стовпці 9 (позиція [" << cell.row << "][8]) не може бути значення " << value << "\n";
                    errorFound = true;
                }
                if (cell.row == 2 && allowed_row2.count(value) == 0) {
                    cout << "Помилка: у рядку 3 (позиція [2][" << cell.col << "]) не може бути значення " << value << "\n";
                    errorFound = true;
                }
            }
        }

        return !errorFound;
    }

    // Перевіряє, чи можна скласти рішення з наявних доміношок
    static bool canPlaceSolution(const vector<Domino>& dominoes, const map<char, Domino>& targetSolution, map<char, Domino>& result) {
        set<pair<int, int>> available;
        for (const auto& d : dominoes) {
            available.insert(d.normalized());
        }

        result.clear();
        for (const auto& [letter, target] : targetSolution) {
            auto norm = target.normalized();
            if (available.count(norm)) {
                result[letter] = target;
                available.erase(norm);
            } else {
                return false;
            }
        }
        return true;
    }
};

