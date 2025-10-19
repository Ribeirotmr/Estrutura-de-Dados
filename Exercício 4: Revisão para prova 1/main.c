#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struct.h"

#define TAM 101

int main()
{

    FILE *entrada = fopen("entrada.txt", "r");
    int linha, coluna;
    fscanf(entrada, "%d %d", &linha, &coluna);

    Sala_de_aula *matriz_sala = cria_matriz(linha, coluna);

    char nome[TAM];
    for (int i = 0; i < linha; i++)
    {
        for (int j = 0; j < coluna; j++)
        {
            fscanf(entrada, "%s", nome);
            preencher_matriz(matriz_sala, i, j, nome);
        }
    }

    fclose(entrada);

    FILE *saida = fopen("saida.txt", "w");
    fprintf(saida, "%d %d\n", matriz_sala->qtd_linha, matriz_sala->qtd_coluna);

    for (int i = 0; i < linha; i++)
    {
        for (int j = 0; j < coluna; j++)
        {
            fprintf(saida, "%s", matriz_sala->nome_alunos[i][j]);
            if (j < coluna - 1)
            {
                fprintf(saida, " ");
            }
        }
        fprintf(saida, "\n");
    }
    fprintf(saida, "\n");

    Sala_de_aula *transposta = matriz_transposta(matriz_sala);
    fprintf(saida, "MATRIZ TRNAPOSTA\n");
    fprintf(saida, "\n");

    for (int i = 0; i < coluna; i++)
    {
        for (int j = 0; j < linha; j++)
        {
            fprintf(saida, "%s", transposta->nome_alunos[i][j]);
            if (j < linha - 1)
            {
                fprintf(saida, " ");
            }
        }
        fprintf(saida, "\n");
    }
    fprintf(saida, "\n");

    char **vetor_nomes = cria_vetor_temporario(matriz_sala);
    fprintf(saida, "SERA QUE PASSOU PARA O VETOR\n");
    fprintf(saida, "\n");
    for (int i = 0; i < linha * coluna; i++)
    {
        fprintf(saida, "%s", vetor_nomes[i]);
        if (i < linha * coluna - 1)
        {
            fprintf(saida, " ");
        }
    }
    fprintf(saida, "\n");

    ordenar_vetor(vetor_nomes, matriz_sala);
    fprintf(saida, "SERA QUE DEU CERTO\n");
    fprintf(saida, "\n");
    for (int i = 0; i < linha; i++)
    {
        for (int j = 0; j < coluna; j++)
        {
            fprintf(saida, "%s", matriz_sala->nome_alunos[i][j]);

            if (j < coluna - 1)
            {
                fprintf(saida, " ");
            }
        }
        fprintf(saida, "\n");
    }

        fclose(saida);
        limpar(matriz_sala);
        limpar(transposta); 
        limpar_vetor(vetor_nomes);
        return 0;
}