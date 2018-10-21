#include "header.h"

int comp = 0;
int comp_insere = 0;

int main(){

    FILE *dicionario;
    FILE *texto;
    pNodoA* arv = NULL;
    pNodoA* node = NULL;

    char frase[MAX];
    char *palavra;
    int contador=0;

    dicionario = fopen("lexicon_2k_shuffled.txt","r");

     while(!feof(dicionario)){
        node = (pNodoA*) malloc(sizeof(pNodoA));
        fscanf(dicionario,"%s  %d\n", node->nome, &(node->info));
        arv = InsereArvore(arv, node->info, node->nome, &comp_insere);
     }
     fclose(dicionario);

     texto = fopen("movieReviews1000.txt", "r");

     while(!feof(texto)){
        fgets(frase, MAX, texto);
        palavra = strtok(frase, "' \"´`,.-!?;\n	");
        while (palavra != NULL){
            contador = contador + consultaABP(arv, palavra, &comp);
            palavra = strtok( NULL, "' \"´`,.-!?;\n	");
        }
     }

     fclose(texto);

     printf("Contador de sentimentos: %d \n Comp: %d\nComp_insere: %d", contador, comp, comp_insere);
    // printf("\n\n-------------------Arvore----------------\n\n");
     //erd(arv);
}
