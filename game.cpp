#include "game.h"

void Game::run() {
    Field field;
    random_device rd;
    mt19937 g(rd());

    map<char, Domino> targetSolution = {
        {'q', {5, 3}}, {'y', {2, 1}}, {'w', {3, 3}}, {'u', {1, 1}}, {'e', {3, 0}},
        {'r', {0, 5}}, {'t', {5, 1}}, {'o', {1, 4}}, {'i', {1, 3}}, {'k', {1, 0}},
        {'l', {0, 0}}, {'z', {6, 2}}, {'x', {2, 5}}, {'c', {5, 5}}, {'v', {5, 4}},
        {'p', {2, 4}}, {'a', {4, 3}}, {'s', {3, 2}}, {'d', {2, 2}}, {'f', {2, 0}},
        {'g', {0, 6}}, {'m', {5, 6}}, {'Q', {4, 6}}, {'h', {4, 4}}, {'b', {6, 1}},
        {'n', {6, 3}}, {'W', {6, 6}}, {'j', {4, 0}}
    };

    if (!DominoSolver::validateTargetSolution(targetSolution, field)) {
        cout << "Знайдені помилки на ігровому полі. Завершення програми.\n";
        return;
    }

    vector<Domino> allDominoes = DominoSolver::generateAllDominoes();

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
