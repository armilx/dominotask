#include "field.h"

Field::Field() {
    for (int i = 0; i < ROWS; ++i) { 
        for (int j = 0; j < COLS; ++j) {
            char ch = letters[i][j];
            if (ch != '*') {
                regions[ch].emplace_back(i, j);
            }
        }
    }
}

bool Field::isDominoCell(int i, int j) const {
    return layout[i][j] == '?';
}
