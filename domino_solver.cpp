#include "domino_solver.h"

vector<Domino> DominoSolver::generateAllDominoes(){
    vector<Domino> dominoes;
    for (int i = 0; i <= 6; ++i)
        for (int j= i; j <= 6; ++j)
            dominoes.emplace_back(i, j);
    return dominoes;
}

void DominoSolver::printGridAscii(const int grid[Field::ROWS][Field::COLS], const Field& field) {
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
                        cout << (val != -1 ? "| " + to_string(val) + " |" : "|   |");
                    } else {
                        cout << "+---+";
                    }
                }
            }
            if (line == 1 && row == 2)
                cout << "   ← [1,2,3]";
            cout << '\n';
        }
    }
    cout << "      ↑                   ↑               ↑\n";
    cout << "    [1,4]               [1,2]          [0,2,3]\n";
}

bool DominoSolver::validateTargetSolution(const map<char, Domino>& targetSolution, const Field& field) {
    map<pair<int, int>, int> count;
    for (const auto& [ch, dom] : targetSolution) {
        ++count[dom.normalized()];
    }

    set<pair<int, int>> expected;
    for (const auto& d : generateAllDominoes())
        expected.insert(d.normalized());

    bool errorFound = false;
    for (const auto& [dom, c] : count) {
        if (c > 1)
            cout << "Помилка: доміношка {" << dom.first << ", " << dom.second << "} використовується" << c << " рази(-и)\n";
    }
    for (const auto& dom : expected) {
        if (count[dom] == 0) {
            cout << "Помилка: доміношка {" << dom.first << ", " << dom.second << "} відсутня на ігровому полі\n";
            errorFound = true;
        }
    }

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

bool DominoSolver::canPlaceSolution(const vector<Domino>& dominoes, const map<char, Domino>& targetSolution, map<char, Domino>& result) {
    set<pair<int, int>> available;
    for (const auto& d : dominoes)
        available.insert(d.normalized());

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
