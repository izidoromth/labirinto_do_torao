#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "celula.h"

struct node
{
    struct Celula *c;
    struct node *prox;
};

void inicia(struct node *PILHA);
void libera(struct node *PILHA);
int vazia(struct node *PILHA);
struct node *aloca(struct Celula *c);
void push(struct node *PILHA, struct Celula * c);
struct Celula *pop(struct node *PILHA);
void exibe(struct node *PILHA);

#endif // STACK_H_INCLUDED
