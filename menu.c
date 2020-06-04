#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
#include <stdlib.h>

#include "menu.h"
#include "recordes.h"

void Mostra_Menu(ALLEGRO_FONT **fonte,int LARGURA, int ALTURA){
    al_draw_text(*fonte,al_map_rgb(250,150,0), LARGURA/2, ALTURA/4, ALLEGRO_ALIGN_CENTRE,"Labirinto do Minotauro");
    al_draw_text(*fonte,al_map_rgb(250,150,0), LARGURA/2, ALTURA/1.94, ALLEGRO_ALIGN_CENTRE,"Jogar");
    al_draw_text(*fonte,al_map_rgb(250,150,0), LARGURA/2, ALTURA/1.62, ALLEGRO_ALIGN_CENTRE,"Instrucoes");
    al_draw_text(*fonte,al_map_rgb(250,150,0), LARGURA/2, ALTURA/1.4, ALLEGRO_ALIGN_CENTRE,"Recordes");
    al_draw_text(*fonte,al_map_rgb(250,150,0), LARGURA/2, ALTURA/1.22, ALLEGRO_ALIGN_CENTRE,"Sair");
}

void Atualiza_Menu(int cursor, ALLEGRO_FONT **fonte,int LARGURA, int ALTURA){
    if(cursor == 1)
     al_draw_text(*fonte,al_map_rgb(255,55,50), LARGURA/2, ALTURA/1.94, ALLEGRO_ALIGN_CENTRE,"Jogar");
    else if(cursor == 2)
        al_draw_text(*fonte,al_map_rgb(255,55,50), LARGURA/2, ALTURA/1.62, ALLEGRO_ALIGN_CENTRE,"Instrucoes");
    else if(cursor == 3)
        al_draw_text(*fonte,al_map_rgb(255,55,50), LARGURA/2, ALTURA/1.4, ALLEGRO_ALIGN_CENTRE,"Recordes");
    else if(cursor == 4)
        al_draw_text(*fonte,al_map_rgb(255,55,50), LARGURA/2, ALTURA/1.22, ALLEGRO_ALIGN_CENTRE,"Sair");
}

int Sai_Menu(int cursor, int enter){
    if (cursor == 1 && enter == 1)
        return 1;
    else if (cursor == 2 && enter == 1)
        return 2;
    else if (cursor == 3 && enter == 1)
        return 3;
    else if (cursor == 4 && enter == 1)
        return 4;
    else return 0;

}

void Mostra_Recordistas(ALLEGRO_BITMAP **fundorecordes,FILE **txt,ALLEGRO_FONT **fonte,int LARGURA,int ALTURA){

    FILE *txt_aux = *txt;

    char *recordista = NULL;
    int i = 1, y_aux = 0;

    al_draw_scaled_bitmap(*fundorecordes,0,0,1280,1222,0,0,LARGURA,ALTURA,0);
    al_draw_text(*fonte,al_map_rgb(235,55,0), LARGURA/2, ALTURA/8, ALLEGRO_ALIGN_CENTER,"Recordistas:");

    rewind(txt_aux);
    while(!feof(txt_aux))
    {
        recordista = Le_Recordistas(&txt_aux);

        al_draw_textf(*fonte,al_map_rgb(235,235,50),LARGURA/2.75,(ALTURA/3)+y_aux,0,"%d. %s",i,recordista);
        y_aux += 50;
        i++;
    }

    rewind(txt_aux);
}

