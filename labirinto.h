#ifndef _LABIRINTO_H_INCLUDED
#define _LABIRINTO_H_INCLUDED
#include "celula.h"
#include "parede.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <stdlib.h>



void criaLabirinto(int altura, int largura, int tCel, int xIni, int yIni);
int randComRange (int maximo);
void labirintoPerfeito();
void achaCaminho();
void drawLabirinto();
void drawCaminho(int x, int y, int x2, int y2, int cor);
void achaVizinhos(struct Celula * c);
int checaParedeLevantada(struct Celula c);
int achaParede(struct Celula * a, struct Celula * b);
void naoVisitados(struct Celula * c);
void deletaLabirinto();
struct Celula *retorna_matriz();
int InsereLargura(ALLEGRO_FONT **fonte,int largura_max,int *tecla,int *f_insere,int LARGURA, int ALTURA);
int InsereAltura(ALLEGRO_FONT **fonte,int altura_max, int *tecla,int *f_insere,int LARGURA, int ALTURA);
void drawFundo(ALLEGRO_BITMAP *fundo1,ALLEGRO_BITMAP *fundo2,ALLEGRO_BITMAP *fundo3,int rand,int LARGURA, int ALTURA);

#endif //_labirinto_h
