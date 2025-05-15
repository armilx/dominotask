#ifndef DOMINOSOLVER_H
#define DOMINOSOLVER_H

#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include "field.h"
#include "domino.h"

using namespace std;

// Клас, який розв'язує головоломку
class DominoSolver {
public:
    static vector<Domino> generateAllDominoes();
    static void printGridAscii(const int grid[Field::ROWS][Field::COLS], const Field& field);
    static bool validateTargetSolution(const map<char, Domino>& targetSolution, const Field& field);
    static bool canPlaceSolution(const vector<Domino>& dominoes, const map<char, Domino>& targetSolution, map<char, Domino>& result);
};

#endif // DOMINOSOLVER_H
