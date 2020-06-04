#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "celula.h"
#include "parede.h"

struct Celula *newCelula(int x, int y, int t){

    struct Celula *c = (struct Celula *) malloc(sizeof(struct Celula));
    c->vizinhos = (struct Celula *) malloc(4*sizeof(struct Celula));
    c->paredes = (struct Paredes *) malloc(4*sizeof(struct Parede));
    c->anterior = (struct Celula *) malloc(sizeof(struct Celula));
    c->x = x;
    c->y = y;
    c->tamanho = t;
    c->numVizinhos = 0;
    c->visitada = 0;

    c->paredes[0] = newParede(x, y, x+c->tamanho, y, CIMAc, c);
    c->paredes[1] = newParede(x, y+c->tamanho, x+c->tamanho, y+c->tamanho, BAIXOc, c);
    c->paredes[2] = newParede(x+c->tamanho, y, x+c->tamanho, y+c->tamanho, DIREITAc, c);
    c->paredes[3] = newParede(x, y+c->tamanho, x, y, ESQUERDAc, c);

    return c;
}

struct Parede getParedePorLado(enum Lado l, struct Celula c){

    struct Parede p;
    int i;
    for(i = 0; i < 4; i++){
        if(c.paredes[i].ladoParede == l)
            p = c.paredes[i];
    }

    return p;
}


void drawCelula(struct Celula c){
    int i;
    for(i = 0; i < 4; i++){
        drawParede(c.paredes[i]);
    }
}
