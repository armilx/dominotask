#ifndef DOMINO_H
#define DOMINO_H

#include <utility>
using namespace std;

// Клас доміно
class Domino { 
public:
    int a, b; // Значення на обох кінцях доміношки

    //  Конструктор, який ініціалізує доміно з двома числами
    Domino(int a = 0, int b = 0) : a(a), b(b) {}

    // унікальна ідентифікації 
    pair<int, int> normalized() const { 
        return minmax(a, b);
    }
};

#endif 
