#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include <stdlib.h>
#include <time.h>

#include "celula.h"
#include "parede.h"
#include "stack.h"

enum TECLAS {CIMAl, BAIXOl, DIREITAl, ESQUERDAl, ENTERl};

int largura = 0, altura = 0;

struct Celula *matriz;
int tamanhoLabirinto = 0;

struct node *posicoesCelulas, *caminhoCelula;

void criaLabirinto(int largura, int altura, int tCel,int xIni, int yIni){

    posicoesCelulas = (struct node *) malloc(sizeof(struct node));
    caminhoCelula = (struct node *) malloc(sizeof(struct node));

    inicia(posicoesCelulas);
    inicia(caminhoCelula);

    tamanhoLabirinto = altura*largura;
    matriz = (struct Celula*) malloc(tamanhoLabirinto*sizeof(struct Celula));

    float x = xIni, y = yIni;

    int i;
    for (i = 0; i < tamanhoLabirinto; i++){

        if(i%largura == 0){
            y += tCel;
            x = 0;
        }
        x += tCel;

        matriz[i] = *newCelula(x, y, tCel);
    }

    srand((unsigned) time(NULL));
}

int randComRange( int maximo){

    return rand()% (maximo);
}

void labirintoPerfeito(){

    struct Celula *atual = (struct Celula*) malloc(sizeof (struct Celula));
    struct Celula *proximo = NULL;

    int numCelsVisitadas = 1;
    int numVizinhos = 0;
    int num = 0;
    atual = &matriz[randComRange(tamanhoLabirinto)];


    while(numCelsVisitadas < tamanhoLabirinto){

        achaVizinhos(atual);
        numVizinhos = atual->numVizinhos;

        if(atual->numVizinhos != 0){
            num = randComRange(numVizinhos);

            proximo = &atual->vizinhos[num];

            atual->paredes[achaParede(atual, proximo)].levantada = 0;
            proximo->paredes[achaParede(proximo, atual)].levantada = 0;

            atual->vizinhos = NULL;

            push(posicoesCelulas, atual);
            atual = proximo;
            numCelsVisitadas++;
        }else {
            if(!vazia(posicoesCelulas)){
                atual = pop(posicoesCelulas);
                atual->vizinhos = (struct Celula *) malloc(4*sizeof(struct Celula));
                atual->numVizinhos = 0;
            }
        }
    }
}

void achaCaminho()
{

    printf("Procurando Caminho...\n");
    struct Celula * atual = &matriz[0];
    struct Celula * proximo = NULL;
    struct Celula * anterior = NULL;
    int numVizinhos = 0;
    int num = 0;
    atual->visitada = 1;

    while(atual->x != matriz[tamanhoLabirinto-1].x && atual->y != matriz[tamanhoLabirinto-1].y)
    {
        naoVisitados(atual);
        numVizinhos = atual->numVizinhos;

        printf("Atual (%d,%d)\n", atual->x, atual->y);

        if(numVizinhos != 0)
        {
            num = randComRange(numVizinhos);
            proximo = &atual->vizinhos[num];
            proximo->visitada = 1;

            drawCaminho(atual->x +(atual->tamanho/2), atual->y +(atual->tamanho/2),
                         proximo->x+(proximo->tamanho/2), proximo->y+(proximo->tamanho/2), 255);

            atual->vizinhos = NULL;

            atual->anterior = proximo;
            push(caminhoCelula, atual);
            atual = proximo;
        }
        else
        {
            if(!vazia(caminhoCelula))
            {
                anterior = pop(caminhoCelula);
                anterior->vizinhos = (struct Celula *) malloc(4*sizeof(struct Celula));
                anterior->numVizinhos = 0;

                atual = anterior;
            }
        }
    }
}
void drawLabirinto(){
    int i = 0;
    for(i = 0; i < tamanhoLabirinto; i++){
        drawCelula(matriz[i]);
    }
}

void drawCaminho(int x, int y, int x2, int y2, int cor){

    al_draw_line(x,y,x2,y2, al_map_rgb(cor, 0 ,0), 3);

}

void achaVizinhos(struct Celula *c){
    int i;
    int j = 0;

    for(i = 0; i < tamanhoLabirinto; i++)
    {
        if(checaParedeLevantada(&matriz[i]) && matriz[i].x == c->x + c->tamanho && matriz[i].y == c->y)
        {
            c->vizinhos[j] = matriz[i];
            c->numVizinhos++;
            j++;

        }
        if(checaParedeLevantada(&matriz[i]) && matriz[i].x == c->x - c->tamanho && matriz[i].y == c->y)
        {
            c->vizinhos[j] = matriz[i];
            c->numVizinhos++;
            j++;

        }
        if(checaParedeLevantada(&matriz[i]) && matriz[i].y ==c->y + c->tamanho && matriz[i].x == c->x)
        {
            c->vizinhos[j] = matriz[i];
            c->numVizinhos++;
            j++;

        }
        if(checaParedeLevantada(&matriz[i]) && matriz[i].y ==c->y - c->tamanho && matriz[i].x == c->x)
        {
            c->vizinhos[j] = matriz[i];
            c->numVizinhos++;
            j++;

        }
    }
}

int checaParedeLevantada(struct Celula * c)
{

    if(c->paredes[0].levantada &&
        c->paredes[1].levantada &&
        c->paredes[2].levantada &&
        c->paredes[3].levantada )
    {
        return 1;
    }
    return 0;
}

int achaParede(struct Celula * a, struct Celula * b){

    if(a->x > b->x && a->y == b->y) return ESQUERDAc;
    if(a->x < b->x && a->y == b->y) return DIREITAc;
    if(a->x == b->x && a->y > b->y) return CIMAc;
    if(a->x == b->x && a->y < b->y) return BAIXOc;

    return -1;
}

void naoVisitados(struct Celula * c){

    int i;
    int j = 0;
    c->vizinhos = (struct Celula *) malloc(4*sizeof(struct Celula));

    for(i = 0; i < tamanhoLabirinto; i++)
    {
        if(!matriz[i].visitada && matriz[i].x == c->x + c->tamanho && matriz[i].y == c->y && !c->paredes[DIREITAc].levantada)
        {
            c->vizinhos[j] = matriz[i];
            c->numVizinhos++;
            j++;

        }
        if(!matriz[i].visitada && matriz[i].x == c->x - c->tamanho && matriz[i].y == c->y && !c->paredes[ESQUERDAc].levantada)
        {
            c->vizinhos[j] = matriz[i];
            c->numVizinhos++;
            j++;

        }
        if(!matriz[i].visitada && matriz[i].y ==c->y + c->tamanho && matriz[i].x == c->x && !c->paredes[BAIXOc].levantada)
        {
            c->vizinhos[j] = matriz[i];
            c->numVizinhos++;
            j++;

        }
        if(!matriz[i].visitada && matriz[i].y ==c->y - c->tamanho && matriz[i].x == c->x && !c->paredes[CIMAc].levantada)
        {
            c->vizinhos[j] = matriz[i];
            c->numVizinhos++;
            j++;
        }
    }

}

void deletaLabirinto(){

    free(matriz);
    free(posicoesCelulas);
    free(caminhoCelula);
    tamanhoLabirinto = 0;

}

struct Celula *retorna_matriz()
{
    return matriz;
}

int InsereLargura(ALLEGRO_FONT **fonte,int largura_max,int *tecla, int *f_insere,int LARGURA, int ALTURA)
{
     al_draw_text(*fonte,al_map_rgb(255,255,255),LARGURA/2,ALTURA/6,ALLEGRO_ALIGN_CENTER,"Insira a largura do labirinto:");

     if(tecla[CIMAl] == 1 && *f_insere == 0)
    {
        largura++;
        *f_insere = 1;
    }

    else if(tecla[BAIXOl] == 1 && *f_insere == 0)
    {
        largura--;
        *f_insere = 1;
    }

    if(largura >= largura_max) largura = largura_max;
    else if(largura <= 0) largura = 0;

    al_draw_rectangle(LARGURA/3.3,ALTURA/2,(LARGURA/3.3)+(LARGURA/16),(ALTURA/2)+(ALTURA/16),al_map_rgb(255,255,0),6);
    al_draw_textf(*fonte,al_map_rgb(255,255,0),LARGURA/3,ALTURA/2,ALLEGRO_ALIGN_CENTER,"%d",largura);

    if(tecla[ENTERl] == 1 && *f_insere == 0)
    {
        *f_insere = 1;
        return largura;
    }

    else    return 0;
}

int InsereAltura(ALLEGRO_FONT **fonte,int altura_max,int *tecla, int *f_insere,int LARGURA, int ALTURA)
{
     al_draw_text(*fonte,al_map_rgb(255,255,255),LARGURA/2,ALTURA/6,ALLEGRO_ALIGN_CENTER,"Insira a altura do labirinto:");

     if(tecla[CIMAl] == 1 && *f_insere == 0)
    {
        altura++;
        *f_insere = 1;
    }

    else if(tecla[BAIXOl] == 1 && *f_insere == 0)
    {
        altura--;
        *f_insere = 1;
    }

    if(altura >= altura_max) altura = altura_max;
    else if (altura <= 0) altura = 0;

    al_draw_rectangle(LARGURA/3.3,ALTURA/2,(LARGURA/3.3)+(LARGURA/16),(ALTURA/2)+(ALTURA/16),al_map_rgb(255,255,0),6);
    al_draw_textf(*fonte,al_map_rgb(255,255,0),LARGURA/3,ALTURA/2,ALLEGRO_ALIGN_CENTER,"%d",altura);

    if(tecla[ENTERl] == 1 && *f_insere == 0)
    {
        *f_insere = 1;
        return altura;
    }
    else return 0;
}

void drawFundo(ALLEGRO_BITMAP *fundo1,ALLEGRO_BITMAP *fundo2,ALLEGRO_BITMAP *fundo3,int rand,int LARGURA, int ALTURA)
{
    if(rand == 0)
        al_draw_scaled_bitmap(fundo1,0,0,1280,1024,0,ALTURA/10,LARGURA,(11/10)*ALTURA,0);
    else if(rand == 1)
        al_draw_scaled_bitmap(fundo2,0,0,1600,900,0,ALTURA/10,LARGURA,(11/10)*ALTURA,0);
    else if(rand == 2)
        al_draw_scaled_bitmap(fundo3,0,0,1024,745,0,ALTURA/10,LARGURA,(11/10)*ALTURA,0);
}
