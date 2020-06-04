#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include <stdio.h>
#include <stdlib.h>

#include "personagem.h"

int celatual = 0;


int Move_Personagem(struct personagem *Personagem,int *tecla, struct Celula *Labirinto, int larg, int tam_lab, int tam_cel,int *f_move)
{
    if(tecla[DIREITAp] == 1 && !(Labirinto[celatual].paredes[DIREITAc].levantada) && *f_move == 0)
    {
       (*Personagem).pos_x = (Labirinto[celatual+1].x + tam_cel/5);
       celatual++;
       *f_move = 1;
    }
    if(tecla[ESQUERDAp] == 1 && !(Labirinto[celatual].paredes[ESQUERDAc].levantada) &&*f_move ==0)
    {
        (*Personagem).pos_x = (Labirinto[celatual-1].x + tam_cel/5);
        celatual--;
        *f_move = 1;
    }
    if(tecla[CIMAp] == 1 && !(Labirinto[celatual].paredes[CIMAc].levantada) && *f_move ==0)
    {
        (*Personagem).pos_y = (Labirinto[celatual-larg].y  + tam_cel/5);
        celatual -= larg;
        *f_move = 1;
    }
    if(tecla[BAIXOp] == 1 && !(Labirinto[celatual].paredes[BAIXOc].levantada) && *f_move ==0)
    {
        (*Personagem).pos_y = (Labirinto[celatual+larg].y + tam_cel/5);
        celatual += larg;
        *f_move = 1;
    }
    if(celatual == (tam_lab-1))
    {
        celatual = 0;
        return 5;
    }
    else return 1;
}

 void Mostra_Personagem(struct personagem Personagem,ALLEGRO_BITMAP *personagem,int razao_pers)
{
    al_draw_scaled_bitmap(personagem,0,0,138,118,Personagem.pos_x,Personagem.pos_y,razao_pers,razao_pers,0);
    //al_draw_bitmap(personagem,Personagem.pos_x,Personagem.pos_y,0);
}
