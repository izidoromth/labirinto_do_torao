#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "recordes.h"


char c = 65;
int i = 0, j = 0,ra = 0;
struct recordista atual[6];


char* Le_Recordistas(FILE **txt){
    char *aux = (char *) malloc(50*sizeof(char));
            fgets(aux,49,*txt);
    return aux;
}

void Insere_Nome(ALLEGRO_FONT **fonte,int *tecla,int *f_insere,int i_nome,char *Nome_aux, int LARGURA, int ALTURA)
{
    al_draw_text(*fonte,al_map_rgb(255,255,255),LARGURA/2,ALTURA/6,ALLEGRO_ALIGN_CENTER,"Insira seu nome:");

    if(tecla[CIMA] == 1 && *f_insere == 0)
    {
        c++;
        *f_insere = 1;
    }

    else if(tecla[BAIXO] == 1 && *f_insere == 0)
    {
        c--;
        *f_insere = 1;
    }


    if(c > 90) c = 65;
    else if(c < 65) c=90;

    al_draw_rectangle(LARGURA/3.3,ALTURA/2,(LARGURA/3.3)+(LARGURA/16),(ALTURA/2)+(ALTURA/16),al_map_rgb(255,255,0),6);
    al_draw_textf(*fonte,al_map_rgb(255,255,0),LARGURA/3,ALTURA/2,ALLEGRO_ALIGN_CENTER,"%c",c);

        if(tecla[ENTER] == 1 && *f_insere == 0 && i_nome<=2)
            Nome_aux[i_nome] = c;

}
void Atualiza_Recordistas(FILE **txt,struct recordista novo,int tamanho,int larg_max, int alt_max)
{
    ra = 0;
    int f_regist = tamanho;
    struct recordista aux;
    rewind(*txt);

    if(f_regist == (larg_max * alt_max))
    {
        while(!feof(*txt))
        {
         fscanf(*txt,"%s %d:%f\n",atual[ra].nome,&atual[ra].tmp_m,&atual[ra].tmp_s);
         if(atual[ra].tmp_m == 0 && atual[ra].tmp_s == 0 )
         {
             atual[ra].tmp_m = 59;
             atual[ra].tmp_s = 59;

             if(ra>0)ra--;
             else ra = 0;
         }
         else if(ra<4) ra++;
        }

        atual[ra+1] = novo;

            for(i=(ra+1); i >= 0;i--)
            {
                for(j=i;j>=0;j--)
                {
                    if(atual[i].tmp_m < atual[j].tmp_m)
                    {
                        aux = atual[j];
                        atual[j] = atual[i];
                        atual[i] = aux;
                    }else if((atual[i].tmp_s < atual[j].tmp_s)&&(atual[j].tmp_m == atual[i].tmp_m))
                    {
                        aux = atual[j];
                        atual[j] = atual[i];
                        atual[i] = aux;
                    }
                }
            }
            freopen("recordes.txt","w",*txt);
            j = 0;
            while(j<=ra)
            {
                if(j == ra) fprintf(*txt,"%s %d:%.0f",atual[j].nome,atual[j].tmp_m,atual[j].tmp_s);
                else fprintf(*txt,"%s %d:%.0f\n",atual[j].nome,atual[j].tmp_m,atual[j].tmp_s);
                j++;
            }
            freopen("recordes.txt","r+",*txt);
            rewind(*txt);

    }
}

void Limpa_Aux(struct recordista *novo, char *Nome_aux)
{
    (*novo).tmp_s = 0;
    (*novo).tmp_m = 0;
    (*novo).nome[0] = ' ';
    (*novo).nome[1] = ' ';
    (*novo).nome[2] = ' ';
    Nome_aux[0] = ' ';
    Nome_aux[1] = ' ';
    Nome_aux[2] = ' ';
}

