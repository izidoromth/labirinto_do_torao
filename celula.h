#ifndef _CELULA_H_INCLUDED
#define _CELULA_H_INCLUDED
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "parede.h"

struct Celula{

    struct Celula * vizinhos;
    int x, y, tamanho, numVizinhos;
    struct Parede * paredes;
    int visitada;
    struct Celula * anterior;

};

struct Celula *newCelula(int x, int y, int t);
struct Parede getParedePorLado(enum Lado l, struct Celula c);
void drawCelula();

#endif // _CELULA_H_INCLUDED
