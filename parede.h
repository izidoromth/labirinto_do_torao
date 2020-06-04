#ifndef _PAREDE_H_INCLUDED
#define _PAREDE_H_INCLUDED

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <stdlib.h>

struct Celula;

enum Lado{

    CIMAc = 0,
    BAIXOc,
    DIREITAc,
    ESQUERDAc
};

struct Parede;

struct Parede{

    struct Celula *atual;
    float x, y, w, h;
    enum Lado ladoParede;
    int levantada;
};

struct Parede newParede(float x, float y, float w, float h, enum Lado ladoParede, struct Celula *atual);
void drawParede(struct Parede p);

#endif // _parede_h

