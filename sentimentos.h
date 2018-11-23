struct TNodoA{
    int info;
    char nome[20];
    struct TNodoA* esq;
    struct TNodoA* dir;
    int FB;
};

typedef struct TNodoA pNodoA;

void deffend (void);
int menu (void);
int consultaABP(pNodoA* a, char* nome, int* comp);
pNodoA* InsereABP(pNodoA* a, int n, char* nome, int* comp_insere);
pNodoA* InsereAVL (pNodoA* a, int n, char* nome, int* ok, int* comp_insere);
void imprimir(pNodoA* a);
int numero_nodos(pNodoA* a);
pNodoA* rotacao_direita(pNodoA* p);
pNodoA* rotacao_esquerda(pNodoA* p);
pNodoA* rotacao_dupla_direita (pNodoA* p);
pNodoA* rotacao_dupla_esquerda (pNodoA* p);
pNodoA* Caso1 (pNodoA* a, int* ok);
pNodoA* Caso2 (pNodoA* a, int* ok);
