#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struct.h"

Sala_de_aula *cria_matriz(int linha, int coluna)
{

    Sala_de_aula *matriz_sala = (Sala_de_aula *)malloc(sizeof(Sala_de_aula));

    matriz_sala->qtd_linha = linha;
    matriz_sala->qtd_coluna = coluna;

    matriz_sala->nome_alunos = (char ***)malloc(linha * sizeof(char **));

    for (int i = 0; i < linha; i++)
    {
        matriz_sala->nome_alunos[i] = (char **)malloc(coluna * sizeof(char *));
        for (int j = 0; j < coluna; j++)
        {
            matriz_sala->nome_alunos[i][j] = NULL;
        }
    }

    return matriz_sala;
}

void preencher_matriz(Sala_de_aula *matriz_sala, int linha, int coluna, char *nome)
{
    matriz_sala->nome_alunos[linha][coluna] = strdup(nome);
}

Sala_de_aula *matriz_transposta(Sala_de_aula *matriz_sala)
{
    int li = matriz_sala->qtd_linha;
    int co = matriz_sala->qtd_coluna;

    Sala_de_aula *vet_temporario = cria_matriz(co, li);

    for (int i = 0; i < li; i++)
    {
        for (int j = 0; j < co; j++)
        {
            vet_temporario->nome_alunos[j][i] = strdup(matriz_sala->nome_alunos[i][j]);
        }
    }

    return vet_temporario;
}

char **cria_vetor_temporario(Sala_de_aula *matriz_sala)
{
    int li = matriz_sala->qtd_linha;
    int co = matriz_sala->qtd_coluna;
    int tamanho = li * co;

    char **vetor_guarda_nomes = (char **)malloc(tamanho * sizeof(char *));

    int k = 0;
    for (int i = 0; i < li; i++)
    {
        for (int j = 0; j < co; j++)
        {
            vetor_guarda_nomes[k++] = matriz_sala->nome_alunos[i][j];
        }
    }

    return vetor_guarda_nomes;
}

void ordenar_vetor(char **vetor_guarda_nomes, Sala_de_aula *matriz_sala)
{
    int tamanho = matriz_sala->qtd_linha * matriz_sala->qtd_coluna;
    char *aux;

    for (int i = 0; i < tamanho - 1; i++)
    {
        for (int j = 0; j < tamanho - i - 1; j++)
        {
            if (strcmp(vetor_guarda_nomes[j], vetor_guarda_nomes[j + 1]) > 0)
            {
                aux = vetor_guarda_nomes[j];
                vetor_guarda_nomes[j] = vetor_guarda_nomes[j + 1];
                vetor_guarda_nomes[j + 1] = aux;
            }
        }
    }

    int k = 0;

    for (int i = 0; i < matriz_sala->qtd_linha; i++) {
        for (int j = 0; j < matriz_sala->qtd_coluna; j++) {
            //free(matriz_sala->nome_alunos[i][j]);
            matriz_sala->nome_alunos[i][j] = vetor_guarda_nomes[k++]; //acho que aqui pode usar strdup, mas vou testar sem 
        }
    }
}

void limpar(Sala_de_aula *matriz_sala)
{

    for (int i = 0; i < matriz_sala->qtd_linha; i++)
    {
        for (int j = 0; j < matriz_sala->qtd_coluna; j++)
        {
            free(matriz_sala->nome_alunos[i][j]);
        }
        free(matriz_sala->nome_alunos[i]);
    }
    free(matriz_sala->nome_alunos);
    free(matriz_sala);
}

void limpar_vetor(char **vet)
{
    free(vet);
}