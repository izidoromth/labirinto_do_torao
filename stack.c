#include "celula.h"
#include "stack.h"
#include <stdlib.h>

int tam;

void inicia(struct node *PILHA)
{
    PILHA->prox = NULL;
    tam=0;
}

void libera(struct node *PILHA)
{
    if(!vazia(PILHA))
    {
        struct node *proxNode,
             *atual;

        atual = PILHA->prox;
        while(atual != NULL)
        {
            proxNode = atual->prox;
            free(atual);
            atual = proxNode;
        }
    }
}

int vazia(struct node *PILHA)
{
    if(PILHA->prox == NULL)
        return 1;
    else
        return 0;
}

struct node *aloca(struct Celula *c)
{
    struct node *novo=(struct node *) malloc(sizeof(struct node));
    if(!novo)
    {
        printf("Sem memoria disponivel!\n");
        exit(1);
    }
    else
    {
        novo->c = c;
        return novo;
    }
}

void push(struct node *PILHA, struct Celula * c)
{
    struct node *novo = aloca(c);
    novo->prox = NULL;

    if(vazia(PILHA))
        PILHA->prox=novo;
    else
    {
        struct node *tmp = PILHA->prox;

        while(tmp->prox != NULL)
            tmp = tmp->prox;

        tmp->prox = novo;
    }
    tam++;
}


struct Celula *pop(struct node *PILHA)
{
    if(PILHA->prox == NULL)
    {
        printf("PILHA ja vazia\n\n");
        return NULL;
    }
    else
    {
        struct node *ultimo = PILHA->prox,
              *penultimo = PILHA;

        while(ultimo->prox != NULL)
        {
            penultimo = ultimo;
            ultimo = ultimo->prox;
        }

        penultimo->prox = NULL;
        tam--;
        return ultimo->c;
    }
}

void exibe(struct node *PILHA)
{
    if(vazia(PILHA))
    {
        printf("PILHA vazia!\n\n");
        return ;
    }

    struct node *tmp;
    tmp = PILHA->prox;
    printf("PILHA:");
    while( tmp != NULL)
    {
        printf("(%d, %d)", tmp->c->x, tmp->c->y);
        tmp = tmp->prox;
    }
    printf("\n        ");
    /*int count;
    for(count=0 ; count < tam ; count++)
        printf("  ^  ");
    printf("\nOrdem:");
    for(count=0 ; count < tam ; count++)
        printf("%5d", count+1);

*/
    printf("\n\n");
}
