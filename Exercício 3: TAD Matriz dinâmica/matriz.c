//
#include <stdio.h>
#include <stdlib.h>
#include "struct_matriz.h"
//  TADMatriz
//
//  Created by Patricia Dockhorn Costa on 19/09/20.
//  Copyright © 2020 Patricia Dockhorn Costa. All rights reserved.
//

/*Inicializa uma matriz de nlinhas e ncolunas
 * inputs: nlinhas (no de linhas) e ncolunas (no de colunas)
 * output: ponteiro para a matriz inicializada
 * pre-condicao: nlinhas e ncolunas diferentes de 0
 * pos-condicao: matriz de retorno existe e contem nlinhas e ncolunas
 */
Matriz *inicializaMatriz(int nlinhas, int ncolunas)
{

    if(nlinhas <= 0 || ncolunas <= 0){
        return NULL; 
    }

    Matriz *mat = (Matriz *)malloc(sizeof(Matriz));
    // printf("o que ta vazando aqui-> %p\n", mat);
    if (mat == NULL)
    {
        return NULL;
    }

    mat->numero_linha = nlinhas;
    mat->numero_coluna = ncolunas;
    mat->elementos = (int **)malloc(nlinhas * sizeof(int *));
    // printf("o que ta vazando aqui-> %p\n", mat->elementos);
    if (mat->elementos == NULL)
    {
        free(mat);
        return NULL;
    }

    for (int i = 0; i < nlinhas; i++)
    {
        mat->elementos[i] = (int *)malloc(ncolunas * sizeof(int));
        if (mat->elementos[i] == NULL)
        {
            for (int j = 0; j < i; j++)
            {
                free(mat->elementos[j]);
            }

            free(mat->elementos);
            free(mat);
            return NULL;
        }

        for(int j = 0; j < ncolunas; j++){
            mat->elementos[i][j] = 0;
        }
    }
    return mat;
}

/*Modifica o elemento [linha][coluna] da matriz mat
 * inputs: a matriz, a linha, a coluna, e o novo elemento
 * output: nenhum
 * pre-condicao: matriz mat existe, linha e coluna sao validos na matriz
 * pos-condicao: elemento [linha][coluna] da matriz modificado
 */
void modificaElemento(Matriz *mat, int linha, int coluna, int elem)
{
    if (mat == NULL || mat->elementos == NULL)
    {
        return;
    }
    if (linha < 0 || linha >= mat->numero_linha || coluna < 0 || coluna >= mat->numero_coluna)
    {
        return;
    }
    mat->elementos[linha][coluna] = elem;
}

/*Retorna o elemento mat[linha][coluna]
 * inputs: a matriz, a linha e a coluna
 * output: elemento mat[linha][coluna]
 * pre-condicao: matriz mat existe, linha e coluna sao validos na matriz
 * pos-condicao: mat nao eh modificada
 */
int recuperaElemento(Matriz *mat, int linha, int coluna)
{
    if (mat == NULL)
    {
        return 0;
    }
    if (linha < 0 || linha >= mat->numero_linha || coluna < 0 || coluna >= mat->numero_coluna)
    {
        return 0;
    }
    return mat->elementos[linha][coluna];
}

/*Retorna o numero de colunas da matriz mat
 * inputs: a matriz
 * output: o numero de colunas da matriz
 * pre-condicao: matriz mat existe
 * pos-condicao: mat nao eh modificada
 */
int recuperaNColunas(Matriz *mat)
{
    if (mat == NULL)
    {
        return 0;
    }
    return mat->numero_coluna;
}

/*Retorna o numero de linhas da matriz mat
 * inputs: a matriz
 * output: o numero de linhas da matriz
 * pre-condicao: matriz mat existe
 * pos-condicao: mat nao eh modificada
 */
int recuperaNLinhas(Matriz *mat)
{
    if (mat == NULL)
    {
        return 0;
    }
    return mat->numero_linha;
}

/*Retorna a matriz transposta de mat
 * inputs: a matriz
 * output: a matriz transposta
 * pre-condicao: matriz mat existe
 * pos-condicao: mat nao eh modificada e matriz transposta existe
 */
Matriz *transposta(Matriz *mat)
{
    if (mat == NULL)
    {
        return NULL;
    }
    int linha_mat = mat->numero_linha;
    int coluna_mat = mat->numero_coluna;

    Matriz *mat_trp = inicializaMatriz(coluna_mat, linha_mat);
    if (mat_trp == NULL)
    {
        return NULL;
    }

    for (int i = 0; i < linha_mat; i++)
    {
        for (int j = 0; j < coluna_mat; j++)
        {
            mat_trp->elementos[j][i] = mat->elementos[i][j];
        }
    }
    return mat_trp;
}

/*Retorna a matriz multiplicacao entre mat1 e mat2
 * inputs: as matrizes mat1 e mat2
 * output: a matriz multiplicacao
 * pre-condicao: matrizes mat1 e mat2 existem, e o numero de colunas de mat1 correponde ao numero de linhas de mat2
 * pos-condicao: mat1 e mat2 nao sao modificadas e a matriz multiplicacao existe
 */
Matriz *multiplicacao(Matriz *mat1, Matriz *mat2)
{
    if (mat1 == NULL || mat2 == NULL)
    {
        return NULL;
    }

    int linha_mat1 = mat1->numero_linha;
    int coluna_mat1 = mat1->numero_coluna;
    int coluna_mat2 = mat2->numero_coluna;

    if (coluna_mat1 != mat2->numero_linha)
    {
        return NULL;
    }

    Matriz *multiplica_mat1_mat2 = inicializaMatriz(linha_mat1, coluna_mat2);
    if (multiplica_mat1_mat2 == NULL)
    {
        return NULL;
    }
    // Matriz* multiplica_mat1_mat2_2 = inicializaMatriz(linha_mat1, coluna_mat1);

    for (int i = 0; i < linha_mat1; i++)
    {
        for (int j = 0; j < coluna_mat2; j++)
        {
            int soma = 0;
            // multiplica_mat1_mat2_2->elementos[i][j] = 0;
            for (int k = 0; k < coluna_mat1; k++)
            {
                soma += mat1->elementos[i][k] * mat2->elementos[k][j];
                // multiplica_mat1_mat2_2->elementos[i][j] += mat1->elementos[i][k] * mat2->elementos[k][j];
            }
            multiplica_mat1_mat2->elementos[i][j] = soma;
        }
    }
    return multiplica_mat1_mat2;
}

/*Imprime a matriz completa
 * inputs: matriz mat
 * output: nenhum
 * pre-condicao: matriz mat existe
 * pos-condicao: nenhuma
 */
void imprimeMatriz(Matriz *mat)
{
    if (mat == NULL)
    {
        return;
    }
    int linha_mat = mat->numero_linha;
    int coluna_mat = mat->numero_coluna;

    for (int i = 0; i < linha_mat; i++)
    {
        for (int j = 0; j < coluna_mat; j++)
        {
            printf("%d ", mat->elementos[i][j]);
        }
        printf("\n");
    }
}

/*Imprime apenas uma linha da matriz
 * inputs: matriz mat e o indice da linha
 * output: nenhum
 * pre-condicao: matriz mat existe e indice eh valido na matriz
 * pos-condicao: nenhuma
 */
void imprimeLinha(Matriz *mat, int indice)
{
    if (mat == NULL)
    {
        return;
    }
    int coluna_mat = mat->numero_coluna;

    if (indice >= mat->numero_linha || indice < 0)
    {
        return;
    }

    for (int i = 0; i < coluna_mat; i++)
    {
        printf("%d ", mat->elementos[indice][i]);
    }
    printf("\n");
}

/*Libera toda a memoria alocada para a matriz
 * inputs: matriz mat
 * output: nenhum
 * pre-condicao: matriz mat existe
 * pos-condicao: memoria ocupada por linhas e colunas liberada!
 */
void destroiMatriz(Matriz *mat)
{
    if (mat == NULL)
    {
        return;
    }

    int linha_mat = mat->numero_linha;

    if(mat->elementos){
        for (int i = 0; i < linha_mat; i++)
        {
            free(mat->elementos[i]);
        }
        free(mat->elementos);
    }
    free(mat);
}
