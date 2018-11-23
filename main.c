#include "header.h"

    int comp_consulta_ABP = 0;
    int comp_insere_ABP = 0;
    int comp_consulta_AVL = 0;
    int comp_insere_AVL = 0;

int main (int argc, char* argv[]) {
    FILE *dicionario;
    FILE *texto;
    FILE *arq_saida_abp;
    FILE *arq_saida_avl;
    pNodoA* abp = NULL;
    pNodoA* avl = NULL;
    pNodoA* node = NULL;

    char frase[MAX];
    char frase_copia[MAX];
    char *palavra;
    int contador = 0;
    int ok = 1;
    int i = 0;

    deffend();

    dicionario = fopen(argv[1],"r");

     while(!feof(dicionario)){
        node = (pNodoA*) malloc(sizeof(pNodoA));
        fscanf(dicionario,"%s  %d\n", node->nome, &(node->info));
        abp = InsereArvore(abp, node->info, node->nome, &comp_insere_ABP);
        avl = InsereAVL(avl, node->info, node->nome, &ok, &comp_insere_AVL);
     }

     fclose(dicionario);

     texto = fopen(argv[2], "r");
     arq_saida_abp = fopen(argv[3], "w");
     frase_copia[0] = '\0';
     while(1){

        fprintf(arq_saida_abp, "%s",frase_copia);
        contador = 0;
        fgets(frase, MAX, texto);
        strcpy(frase_copia, frase);
        palavra = strtok(frase, " ");
        while (palavra != NULL){

            for (i = 0; i < strlen(palavra); i++)
                palavra[i] = tolower (palavra[i]);
            contador = contador + consultaABP(abp, palavra, &comp_consulta_AVL);
            palavra = strtok( NULL, " ");
        }
        if (feof(texto))
            break;
        fprintf(arq_saida_abp, "%d ",contador);
     }

     fclose(texto);
     fclose(arq_saida_abp);

     texto = fopen("movieReviews1000.txt", "r");
     arq_saida_avl = fopen("saida.txt", "w");
     frase_copia[0] = '\0';
     while(1){

        fprintf(arq_saida_avl, "%s",frase_copia);
        contador = 0;
        fgets(frase, MAX, texto);
        strcpy(frase_copia, frase);
        palavra = strtok(frase, " ");
        while (palavra != NULL){

            for (i = 0; i < strlen(palavra); i++)
                palavra[i] = tolower (palavra[i]);
            contador = contador + consultaABP(avl, palavra, &comp_consulta_AVL);
            palavra = strtok( NULL, " ");
        }
        if (feof(texto))
            break;
        fprintf(arq_saida_avl, "%d ",contador);
     }

     fclose(texto);
     fclose(arq_saida_avl);

     printf("\nContador de sentimentos: %d \n Comp: %d\nComp_insere: %d\n", contador, comp_consulta_ABP, comp_insere_ABP);
     printf("\nContador de sentimentos: %d \n Comp: %d\nComp_insere: %d", contador, comp_consulta_AVL, comp_insere_AVL);
}
