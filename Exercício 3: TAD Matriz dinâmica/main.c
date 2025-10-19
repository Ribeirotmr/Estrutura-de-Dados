#include <stdio.h>
#include <stdlib.h> 

#include "struct_matriz.h"


int main() {
    FILE* entrada = fopen("entrada.txt", "r");
    if(entrada == NULL){
        return 1;
    }
    int linhas, colunas;
    fscanf(entrada, "%d %d", &linhas, &colunas);
    
    Matriz* mat = inicializaMatriz(linhas, colunas);
    if(mat == NULL){
        fclose(entrada);
        return 1;
    }
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            int elem;
            fscanf(entrada, "%d", &elem);
            modificaElemento(mat, i, j, elem);
        }
    }
    fclose(entrada);

    FILE* saida = fopen("saida.txt", "w");
    if(saida == NULL){
        return 1;
    }
    fprintf(saida, "Matriz original:\n");
    for (int i = 0; i < recuperaNLinhas(mat); i++) {
        for (int j = 0; j < recuperaNColunas(mat); j++) {
            fprintf(saida, "%d ", recuperaElemento(mat, i, j));
        }
        fprintf(saida, "\n");
    }

    Matriz* trans = transposta(mat);
    if(trans){
        fprintf(saida, "\nMatriz transposta:\n");
        for (int i = 0; i < recuperaNLinhas(trans); i++) {
            for (int j = 0; j < recuperaNColunas(trans); j++) {
                fprintf(saida, "%d ", recuperaElemento(trans, i, j));
            }
            fprintf(saida, "\n");
        }
    }

    Matriz* mult = multiplicacao(mat, trans);
    if(mult){
        fprintf(saida, "\nMatriz multiplicada (original x transposta):\n");
        for (int i = 0; i < recuperaNLinhas(mult); i++) {
            for (int j = 0; j < recuperaNColunas(mult); j++) {
                fprintf(saida, "%d ", recuperaElemento(mult, i, j));
            }
            fprintf(saida, "\n");
        }
    }

    fclose(saida);
    destroiMatriz(mat);
    destroiMatriz(trans);
    destroiMatriz(mult);

    return 0;
}

