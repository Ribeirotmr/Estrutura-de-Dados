#ifndef matriz_h
#define matriz_h

#include <stdio.h>

//Tipo matriz (tipo opaco)
//Estrutura interna do tipo deve ser definida na implementacao do TAD
typedef struct{
    int numero_linha;
    int numero_coluna;
    int **elementos; 
} Matriz;

Matriz* inicializaMatriz(int nlinhas, int ncolunas);
void modificaElemento(Matriz* mat, int linha, int coluna, int elem);
int recuperaElemento(Matriz* mat, int linha, int coluna);
int recuperaNColunas(Matriz* mat);
int recuperaNLinhas(Matriz* mat);
Matriz* transposta(Matriz* mat);
Matriz* multiplicacao(Matriz* mat1, Matriz* mat2);
void imprimeMatriz(Matriz* mat);
void imprimeLinha(Matriz* mat, int indice);
void destroiMatriz(Matriz* mat);

#endif
