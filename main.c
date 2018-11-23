#include "header.h"

int main (int argc, char* argv[])
{
    setlocale(LC_ALL, ""); // Define o idioma local como o idioma do programa.

    FILE *arq_dicionario; // Ponteiro para o arquivo com o dicion�rio do valor sentimental das palavras.
    FILE *arq_texto; // Ponteiro para o arquivo com o texto de entrada a ser analisado.
    FILE *arq_saida; // Ponteiro para o arquivo de sa�da, que cont�m o valor sentimental das frases analisadas.

    pNodoA* arvore = NULL; // Ponteiro para a raiz da �rvore utilizada.

    char* local_dicionario = argv[1]; // Armazena o nome do arquivo-dicion�rio.
    char* local_texto = argv[2]; // Armazena o nome do arquivo do texto de entrada.
    char* local_saida = argv[3]; // Armazena o nome do arquivo de sa�da.

    char frase[MAX]; // Acumula a parte da frase corrente que ainda resta ser analisada,.
    char backup_frase[MAX]; // Armazena a frase corrente.
    char* palavra; // Aponta para a pr�xima palavra da frase corrente.
    char buffer_palavra[MAX]; // Armazena uma palavra (para a cria��o do dicion�rio).
    int buffer_valor_sentimental; // Armazena um inteiro (para a cria��o do dicion�rio).

    int num_comp_insere; // Conta o n�mero de nodos que foram acessados pela fun��o de inser��o,
    int num_comp_consulta; // Conta o n�mero de nodos que foram acessados pela fun��o de consulta.
    int valor_sentimental_frase; // Conta o valor sentimental de cada frase do texto de entrada.
    int valor_sentimental_texto; // Conta o valor sentimental do texto de entrada.

    int opcao; // Registra a escolha do tipo de �rvore a ser utilizado.
    int indice; // Vari�vel auxiliar, utilizada para o controle de la�os.
    int balanceamento = 1; // Registra se a �rvore AVL est� balanceada.

    deffend(); // Defende o nosso trabalho =D.

    while (desejo_do_usuario)
    {
        num_comp_insere = 0;
        num_comp_consulta = 0;
        valor_sentimental_texto = 0;
        opcao = menu();

        if (opcao == 3)
            return 0;
        else
        {
            arq_dicionario = fopen(local_dicionario, "r");
            if (arq_dicionario == NULL)
            {
                printf("\nFalha ao abrir o dicion�rio.");
                return 1;
            }
            else
            {
                while (!feof(arq_dicionario))
                {
                    fscanf(arq_dicionario,"%s  %d\n", buffer_palavra, &buffer_valor_sentimental);
                    if (opcao == 1)
                        arvore = InsereABP(arvore, buffer_valor_sentimental, buffer_palavra, &num_comp_insere);
                    else
                        arvore = InsereAVL(arvore, buffer_valor_sentimental, buffer_palavra, &balanceamento, &num_comp_insere);
                }
                fclose(arq_dicionario);

                arq_texto = fopen(local_texto, "r");
                if (arq_texto == NULL)
                {
                    printf("\nFalha ao abrir o texto de entrada.");
                    return 1;
                }
                else
                {
                    arq_saida = fopen(local_saida, "w");
                    if (arq_saida == NULL)
                    {
                        printf("\nFalha ao criar o arquivo de sa�da.");
                        return 1;
                    }
                    else
                    {
                        while (!feof(arq_texto))
                        {
                            if (num_comp_consulta > 0)
                            {
                                fprintf(arq_saida, "%d ", valor_sentimental_frase);
                                fputs(backup_frase, arq_saida);
                            }
                            valor_sentimental_frase = 0;
                            fgets(frase, MAX, arq_texto);
                            strcpy(backup_frase, frase);
                            palavra = strtok(frase, " ");
                            while (palavra != NULL)
                            {
                                for (indice = 0; indice < strlen(palavra); indice++)
                                    palavra[indice] = tolower (palavra[indice]);
                                valor_sentimental_frase = valor_sentimental_frase + consultaABP(arvore, palavra, &num_comp_consulta);
                                palavra = strtok( NULL, " ");
                            }
                            valor_sentimental_texto += valor_sentimental_frase;
                        }

                        fclose(arq_texto);
                        fclose(arq_saida);

                        printf("\nValor sentimental do texto: %d.", valor_sentimental_texto);
                        printf("\nN�mero de compara��es realizadas na inser��o: %d.", num_comp_insere);
                        printf("\nN�mero de compara��es realizadas na consulta: %d.", num_comp_consulta);
                        printf("\n\n=================================================\n\n");
                    }
                }
            }
        }
    }
}
