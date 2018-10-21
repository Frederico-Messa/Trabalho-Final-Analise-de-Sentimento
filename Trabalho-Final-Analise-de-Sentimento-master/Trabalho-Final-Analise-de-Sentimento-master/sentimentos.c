#include "header.h"

int consultaABP(pNodoA *a, char* nome, int* comp)
{
    while (a!=NULL)
    {
        if(strcmp(a->nome, nome) == 0)
        {
            (*comp)++;
            return a->info; //achou retorna o ponteiro para o nodo
        }
        else
        {
           (*comp)++;
            if(strcmp(a->nome, nome) > 0)
                a = a->esq;
            else
                a = a->dir;
        }
    }

    return 0; //não achou, retorna null
}

pNodoA* InsereArvore(pNodoA *a, int n, char* nome, int* comp_insere)
{
    if (a == NULL)
    {
        a = (pNodoA*) malloc(sizeof(pNodoA));
        a->info = n;
        strcpy(a->nome,nome);
        a->esq = NULL;
        a->dir = NULL;
    }

    else{
        (*comp_insere)++;
        if (strcmp(nome, a->nome) < 0)
            a->esq = InsereArvore(a->esq, n, nome, comp_insere);
        else
            a->dir = InsereArvore(a->dir, n, nome, comp_insere);
    }
    return a;
}

void erd(pNodoA *a)
{

    if (a != NULL)
    {
        printf("%s    %d\n", a->nome, a->info);
        erd(a->esq);
        erd(a->dir);
    }
}

void imprime(pNodoA *a, int n)
{
    int aux=0;

    if (a != NULL)
    {
        for(aux=0 ; aux<n ; aux++)
            printf("=");
        printf("%d\n", a->info);
        imprime(a->esq, n+1);
        imprime(a->dir, n+1);
    }
}

int numero_nodos(pNodoA *a)
{

    int nos=0;

    if (a != NULL)
    {
        nos++;
        nos = numero_nodos(a->esq) + nos;
        nos = numero_nodos(a->dir) + nos;
    }
    return nos;
}

