#ifndef PERSONAGEM_H_INCLUDED
#define PERSONAGEM_H_INCLUDED

#include "celula.h"

enum TECLA {CIMAp, BAIXOp, DIREITAp, ESQUERDAp};

struct personagem{
    int pos_x;
    int pos_y;
};

int Move_Personagem(struct personagem *Personagem,int *tecla,struct Celula *Labirinto, int larg, int tam_lab,int tam_cel, int *f_move);
void Mostra_Personagem(struct personagem Personagem,ALLEGRO_BITMAP *personagem,int razao_pers);


#endif // PERSONAGEM_H_INCLUDED
