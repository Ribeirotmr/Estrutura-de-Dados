#ifndef struct_h
#define matriz_h 

#include <stdio.h> 

typedef struct {
    int qtd_linha;
    int qtd_coluna; 
    char ***nome_alunos; 
} Sala_de_aula; 

Sala_de_aula *cria_matriz(int linha, int coluna); 
void preencher_matriz(Sala_de_aula *matriz_sala, int linha, int coluna, char *nome);
Sala_de_aula *matriz_transposta(Sala_de_aula *matriz_sala);  
char **cria_vetor_temporario(Sala_de_aula *matriz_sala);
void ordenar_vetor(char **vetor_guarda_nomes, Sala_de_aula *matriz_sala);
void limpar_vetor(char **vet); 
void limpar(Sala_de_aula* matriz_sala);

#endif 