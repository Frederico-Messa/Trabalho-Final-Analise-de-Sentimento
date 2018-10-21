struct TNodoA{
    int info;
    char nome[20];
    struct TNodoA *esq;
    struct TNodoA *dir;
};

typedef struct TNodoA pNodoA;

int consultaABP(pNodoA *a, char* nome, int* comp);
pNodoA* InsereArvore(pNodoA *a, int n, char* nome, int* comp_insere);
void erd(pNodoA *a);
int numero_nodos(pNodoA *a);
void imprime(pNodoA *a, int n);
int numero_nodos(pNodoA *a);
