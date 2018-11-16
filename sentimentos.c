#include "header.h"

int consultaABP(pNodoA *a, char* nome, int* comp)
{
    while (a!=NULL)
    {
        (*comp)++;
        if(strcmp(a->nome, nome) == 0)
        {
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
        strcpy(a->nome, nome);
        a->info = n;
        a->esq = NULL;
        a->dir = NULL;
    }

    else
    {
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
        printf("%s\n", a->nome);
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

pNodoA* rotacao_direita(pNodoA* p)
{
    pNodoA *u;
    u = p->esq;
    p->esq = u->dir;
    u->dir = p;
    p->FB = 0;
    p = u;
    return p;
}

pNodoA* rotacao_esquerda(pNodoA *p)
{
    pNodoA *z;
    z = p->dir;
    p->dir = z->esq;
    z->esq = p;
    p->FB = 0;
    p = z;
    return p;
}

pNodoA* rotacao_dupla_direita (pNodoA* p)
{
    pNodoA *u, *v;
    u = p->esq;
    v = u->dir;
    u->dir = v->esq;
    v->esq = u;
    p->esq = v->dir;
    v->dir = p;
    if (v->FB == 1)
        p->FB = -1;
    else
        p->FB = 0;
    if (v->FB == -1)
        u->FB = 1;
    else
        u->FB = 0;
    p = v;
    return p;
}
pNodoA* rotacao_dupla_esquerda (pNodoA *p)
{
    pNodoA *z, *y;
    z = p->dir;
    y = z->esq;
    z->esq = y->dir;
    y->dir = z;
    p->dir = y->esq;
    y->esq = p;
    if (y->FB == -1)
        p->FB = 1;
    else
        p->FB = 0;
    if (y->FB == 1)
        z->FB = -1;
    else
        z->FB = 0;
    p = y;
    return p;
}
pNodoA* Caso1 (pNodoA *a, int *ok)
{
    pNodoA *z;
    z = a->esq;
    if (z->FB == 1)
        a = rotacao_direita(a);
    else
        a = rotacao_dupla_direita(a);
    a->FB = 0;
    *ok = 0;
    return a;
}

pNodoA* Caso2 (pNodoA *a, int *ok)
{
    pNodoA *z;
    z = a->dir;
    if (z->FB == -1)
        a = rotacao_esquerda(a);
    else
        a = rotacao_dupla_esquerda(a);
    a->FB = 0;
    *ok = 0;
    return a;
}

pNodoA* InsereAVL (pNodoA *a, int n, char *nome, int *ok,  int* comp_insere)
{
    /* Insere nodo em uma árvore AVL, onde A representa a raiz da árvore,
    nome, a chave a ser inserida*/
    if (a == NULL)
    {
        a = (pNodoA*) malloc(sizeof(pNodoA));
        strcpy(a->nome, nome);
        a->info = n;
        a->esq = NULL;
        a->dir = NULL;
        a->FB = 0;
        *ok = 1;
    }
    else
    {
        (*comp_insere)++;
        if (strcmp(nome, a->nome) < 0)
        {
            a->esq = InsereAVL(a->esq, n, nome,ok, comp_insere);
            if (*ok)
            {
                switch (a->FB)
                {
                case -1:
                    a->FB = 0;
                    *ok = 0;
                    break;
                case 0:
                    a->FB = 1;
                    break;
                case 1:
                    a=Caso1(a,ok);
                    break;
                }
            }
        }
        else
        {
            a->dir = InsereAVL(a->dir, n, nome,ok, comp_insere);
            if (*ok)
            {
                switch (a->FB)
                {
                case 1:
                    a->FB = 0;
                    *ok = 0;
                    break;
                case 0:
                    a->FB = -1;
                    break;
                case -1:
                    a = Caso2(a,ok);
                    break;
                }
            }
        }
    }
    return a;
}


