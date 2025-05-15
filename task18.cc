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
    pair<int, int> normalized() const { 
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

// Клас, який розв'язує головоломку
class DominoSolver {
public:
    // генерує всі можливі доміно 0-0 до 6-6
    static vector<Domino> generateAllDominoes(){
        vector<Domino> dominoes;
        for (int i = 0; i <= 6; ++i) {
            for (int j= i; j <= 6; ++j) { 
                dominoes.emplace_back(i, j);
            }
        }
        return dominoes;
    }
    // поле у вигляді ASCII
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

    // перевіряє правильністість розміщення доміно
    static bool validateTargetSolution(const map<char, Domino>& targetSolution, const Field& field) {
        map<pair<int, int>,int> count;
        for (const auto& [ch,dom] : targetSolution) {
            ++count[dom.normalized()];
        }
        set<pair<int, int>> expected;
        for (const auto& d : generateAllDominoes()) {
            expected.insert(d.normalized());
        }
        bool errorFound = false;
        // перевірка на дублікати 
        for (const auto& [dom, c] : count) {
            if (c > 1) {
                cout << "Помилка: доміношка {" << dom.first << ", " << dom.second << "} використовується" << c << " рази(-и)\n";

            }
        }
        // перевірка на пропущені доміношки
        for (const auto& dom : expected) {
            if (count[dom] == 0) {
                cout << "Помилка: доміношка {" << dom.first << ", " << dom.second << "} відсутня на ігровому полі\n";
                errorFound = true;
            }
        }
        // перевірки значень у певних рядках і стовпцях 
        set<int> allowed_col1 = {1, 4};
        set<int> allowed_col5 = {1, 2};
        set<int> allowed_col8 = {0, 2, 3};
        set<int> allowed_row2 = {1, 2, 3};

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
// Клас Game, курує усім процесом
class Game {
public:
     // Запускає гру та обробляє вибір користувача
    void run() {
        Field field;
        random_device rd;
        mt19937 g(rd());
    
            // Задане правильне рішення гри
        map<char, Domino> targetSolution = {
            {'q', {5, 3}}, {'y', {2, 1}}, {'w', {3, 3}}, {'u', {1, 1}}, {'e', {3, 0}},
            {'r', {0, 5}}, {'t', {5, 1}}, {'o', {1, 4}}, {'i', {1, 3}}, {'k', {1, 0}},
            {'l', {0, 0}}, {'z', {6, 2}}, {'x', {2, 5}}, {'c', {5, 5}}, {'v', {5, 4}},
            {'p', {2, 4}}, {'a', {4, 3}}, {'s', {3, 2}}, {'d', {2, 2}}, {'f', {2, 0}},
            {'g', {0, 6}}, {'m', {5, 6}}, {'Q', {4, 6}}, {'h', {4, 4}}, {'b', {6, 1}},
            {'n', {6, 3}}, {'W', {6, 6}}, {'j', {4, 0}}
        };
    
        // Перевірка правильності заданого рішення
        if (!DominoSolver::validateTargetSolution(targetSolution, field)) {
            cout << "Знайдені помилки на ігровому полі. Завершення програми.\n";
            return;
        }

        vector<Domino> allDominoes = DominoSolver::generateAllDominoes();

        // Основний цикл гри
        while (true) {
            cout << "\nОберіть дію:\n";
            cout << "1 - Скласти доміно\n";
            cout << "0 - Вийти\n> ";
    
            int choice;
            cin >> choice;
    
            if (!cin) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Некоректне введення. Введіть 1 або 0.\n";
                continue;
            }
    
            if (choice == 0) break;
            if (choice != 1) {
                cout << "Невірна команда. Введіть 1 або 0.\n";
                continue;
            }
    
            vector<Domino> shuffled;
            map<char, Domino> finalSolution;
            bool found = false;
    
            // Пошук правильного розміщення доміношок
            while (!found) {
                shuffled = allDominoes;
                shuffle(shuffled.begin(), shuffled.end(), g);
    
                if (DominoSolver::canPlaceSolution(shuffled, targetSolution, finalSolution)) {
                    found = true;
                    int grid[Field::ROWS][Field::COLS];
                    for (int i = 0; i < Field::ROWS; ++i)
                        for (int j = 0; j < Field::COLS; ++j)
                            grid[i][j] = -1;
    
                    for (const auto& [region, dom] : finalSolution) {
                        const auto& cells = field.regions[region];
                        grid[cells[0].row][cells[0].col] = dom.a;
                        grid[cells[1].row][cells[1].col] = dom.b;
                    }
    
                    DominoSolver::printGridAscii(grid, field);
                }
            }
        }
    
        cout << "Завершення програми. До побачення!\n";
    }
};
    
// точка входу
int main() {
    Game game;
    game.run();
    return 0;
}