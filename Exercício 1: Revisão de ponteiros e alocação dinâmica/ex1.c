#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void calc_esfera(float r, float *area, float *volume){
    *area = 4.0 * 3.1415 * r * r;
    *volume = (4.0 / 3.0) * 3.1415 * r * r * r;
}

int raizes(float a, float b, float c, float *x1, float *x2){
    float delta = b * b - 4 * a * c;

    if (delta < 0)
        return 0;
    else if (delta == 0) {
        *x1 = -b / (2 * a);
        *x2 = *x1;
        return 1;
    } else {
        *x1 = (-b + sqrt(delta)) / (2 * a);
        *x2 = (-b - sqrt(delta)) / (2 * a);
        return 2;
    }
}

int pares(int n, int *vet){
    int count = 0;
    for (int i = 0; i < n; i++)
        if (vet[i] % 2 == 0)
            count++;
    return count;
}

void inverte(int n, int *vet){
    int *inicio = vet;
    int *fim = vet + n - 1;

    while (inicio < fim)
    {
        int aux = *inicio;
        *inicio = *fim;
        *fim = aux;
        inicio++;
        fim--;
    }
}

double avalia(double* poli, int grau, double x) {
    double res = 0.0;
    for (int i = 0; i <= grau; i++)
        res += poli[i] * pow(x, i);
    return res;
}

int compare_ponteiro(const void* a, const void* b) {
    int* pa = *(int**)a;
    int* pb = *(int**)b;
    return (*pa - *pb);
}

int** inverte2(int n, int* vet) {
    int** ponteiro = (int**) malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++)
        ponteiro[i] = &vet[i];

    qsort(ponteiro, n, sizeof(int*), compare_ponteiro);
    return ponteiro;
}

int main()
{
    
    float area, volume;
    calc_esfera(3.0, &area, &volume);
    printf("area = %f e volume = %f\n", area, volume);

    
    float x1, x2;
    int qtd_raizes = raizes(1.0, -3.0, -10.0, &x1, &x2);
    printf("x1 = %f x2 = %f qtd_raizes = %d\n", x1, x2, qtd_raizes);

    
    int vet1[] = {1, 2, 4, 5, 6};
    int count = pares(5, vet1);
    printf("Quantidade de pares = %d\n", count);

    
    int vet2[] = {1, 2, 3, 4, 5};
    inverte(5, vet2);
    printf("Vetor invertido = ");
    for (int i = 0; i < 5; i++)
        printf("%d", vet2[i]);
    printf("\n");
    

    
    int vet3[] = {50, 20, 40, 10, 30};
    int** ponteiro_novo = inverte2(5, vet3);
    printf("Vetor novo = ");
    for (int i = 0; i < 5; i++)
        printf("%d ", *ponteiro_novo[i]);
    printf("\n");
    free(ponteiro_novo);

    return 0;
}
