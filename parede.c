#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <stdlib.h>
#include <stdio.h>

#include "celula.h"
#include "parede.h"

struct Parede newParede(float x,float y, float w, float h, enum Lado ladoParede, struct Celula *atual){

    struct Parede p;
    p.x = x;
    p.y = y;
    p.w = w;
    p.h = h;
    p.ladoParede = ladoParede;
    p.atual = atual;
    p.levantada = 1;
    return p;

}

void drawParede(struct Parede p){
    if(p.levantada)
        al_draw_line(p.x, p.y, p.w, p.h , al_map_rgb(255,255,255), 3);
    //fprintf(stderr, "chamei aqui... aeeeeooo\nx = %f y = %f w = %f h = %f", p.x,p.y,p.w,p.h);
}
