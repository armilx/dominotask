#ifndef CELL_H
#define CELL_H

// Клас який описує координати клітинки 
class Cell { 
public:
    int row, col;
    // Конструктор створює клітинку за заданими координатами 
    Cell(int r = 0, int c = 0) : row(r), col(c) {}
};

#endif 
