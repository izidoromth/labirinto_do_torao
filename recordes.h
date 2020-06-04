#ifndef RECORDES_H_INCLUDED
#define RECORDES_H_INCLUDED

enum TECLAS {CIMA, BAIXO, DIREITA, ESQUERDA, ENTER, ESC};

struct recordista
{
    char nome[4];
    float tmp_s;
    int tmp_m;
};

char* Le_Recordistas(FILE **txt);
void Insere_Nome(ALLEGRO_FONT **fonte,int *tecla,int *f_insere,int i_nome,char *Nome_aux, int LARGURA, int ALTURA);
void Atualiza_Recordistas(FILE **txt,struct recordista novo,int tamanho,int larg_max, int alt_max);
void Limpa_Aux(struct recordista *novo, char *Nome_aux);

#endif // RECORDES_H_INCLUDED

