#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 100

typedef struct {
    char *nome;
    double valor;
} TipoProduto;

typedef struct {
    TipoProduto **produto;
    int quantidade;
} ItemEstoque;

typedef struct {
    ItemEstoque **itens;
    int num_itens;
    double valor_total;
} Estoque;

typedef struct {
    char *nome;
    Estoque **estoque;
} Filial;

typedef struct {
    char *nome;
    Filial **filiais;
    int num_filiais;
    double valor_total_estoque;
} Supermercado;

// TipoProduto **catalogo_produtos = NULL;
// int num_produtos_cadastrados = 0;


TipoProduto **cadastrar_produtos(int *num_produtos) {
    printf("Quantos produtos deseja cadastrar? ");
    scanf("%d", num_produtos);
    while(getchar() != '\n');

    //printf("VASCO DA GAMA %d\n", *num_produtos); 

    TipoProduto **produtos = (TipoProduto**)malloc(*num_produtos * sizeof(TipoProduto*));
    for(int i = 0; i < *num_produtos; i++) {
        char buffer[TAM];
        printf("Nome do produto %d: ", i+1);
        fgets(buffer, TAM, stdin);
        buffer[strcspn(buffer, "\n")] = 0;

        produtos[i] = (TipoProduto*)malloc(sizeof(TipoProduto));
        produtos[i]->nome = (char*)malloc(strlen(buffer)+1);
        strcpy(produtos[i]->nome, buffer);

        printf("Valor do produto: ");
        scanf("%lf", &produtos[i]->valor);
        while(getchar() != '\n');

        //printf("VASCO DA GAMA %s %.2lf\n", produtos[i]->nome, produtos[i]->valor);
    }
    return produtos;
}


Supermercado *criar_supermercado() {
    Supermercado *super = (Supermercado*)malloc(sizeof(Supermercado));
    char buffer[TAM];
    printf("Nome do supermercado: ");
    fgets(buffer, TAM, stdin);
    buffer[strcspn(buffer, "\n")] = 0;

    super->nome = (char*)malloc(strlen(buffer)+1);
    strcpy(super->nome, buffer);
    super->filiais = NULL;
    super->num_filiais = 0;
    super->valor_total_estoque = 0;

    printf("VASCO DA GAMA %s\n", super->nome);
    return super;
}


void criar_filiais(Supermercado *super) {
    printf("Quantas filiais? ");
    scanf("%d", &super->num_filiais);
    while(getchar() != '\n');

    //printf("VASCO DA GAMA %d\n", super->num_filiais);

    super->filiais = (Filial**)malloc(super->num_filiais * sizeof(Filial*));

    for(int i = 0; i < super->num_filiais; i++) {
        char buffer[TAM];
        printf("Nome da filial %d: ", i+1);
        fgets(buffer, TAM, stdin);
        buffer[strcspn(buffer, "\n")] = 0;

        super->filiais[i] = (Filial*)malloc(sizeof(Filial));
        super->filiais[i]->nome = (char*)malloc(strlen(buffer)+1);
        strcpy(super->filiais[i]->nome, buffer);

        
        super->filiais[i]->estoque = (Estoque**)malloc(sizeof(Estoque*));
        super->filiais[i]->estoque[0] = (Estoque*)malloc(sizeof(Estoque));
        super->filiais[i]->estoque[0]->itens = NULL;
        super->filiais[i]->estoque[0]->num_itens = 0;
        super->filiais[i]->estoque[0]->valor_total = 0;

        //printf("ACERTEI %s\n", super->filiais[i]->nome);
    }
}


void preencher_estoque(Supermercado *super, TipoProduto **produtos, int num_produtos) {
    for(int i = 0; i < super->num_filiais; i++) {
        Filial *filial = super->filiais[i];
        int n_itens;
        printf("Quantos produtos na filial %s? ", filial->nome);
        scanf("%d", &n_itens);
        while(getchar() != '\n');

        filial->estoque[0]->num_itens = n_itens;
        filial->estoque[0]->itens = (ItemEstoque**)malloc(n_itens * sizeof(ItemEstoque*));

        for(int j = 0; j < n_itens; j++) {
            int escolha, qtd;
            printf("Escolha produto %d (1-%d): ", j+1, num_produtos);
            scanf("%d", &escolha);
            while(getchar() != '\n');
            if(escolha < 1 || escolha > num_produtos) escolha = 1; // correção básica

            printf("Quantidade: ");
            scanf("%d", &qtd);
            while(getchar() != '\n');

            filial->estoque[0]->itens[j] = (ItemEstoque*)malloc(sizeof(ItemEstoque));
            filial->estoque[0]->itens[j]->produto = &produtos[escolha-1];
            filial->estoque[0]->itens[j]->quantidade = qtd;
        }
    }
}


void calcular_valores_filial(Filial *filial) {
    double total = 0;
    for(int i = 0; i < filial->estoque[0]->num_itens; i++) {
        ItemEstoque *item = filial->estoque[0]->itens[i];
        total += (*(item->produto))->valor * item->quantidade;
    }
    filial->estoque[0]->valor_total = total;
}

// Calcular valores do supermercado
void calcular_valores_super(Supermercado *super) {
    double total = 0;
    for(int i = 0; i < super->num_filiais; i++) {
        calcular_valores_filial(super->filiais[i]);
        total += super->filiais[i]->estoque[0]->valor_total;
    }
    super->valor_total_estoque = total;
}


void imprimir(Supermercado *super) {
    printf("Supermercado: %s\n", super->nome);
    printf("Total estoque: %.2lf\n", super->valor_total_estoque);

    for(int i = 0; i < super->num_filiais; i++) {
        Filial *f = super->filiais[i];
        printf("Filial: %s - Estoque: %.2lf\n", f->nome, f->estoque[0]->valor_total);
        for(int j = 0; j < f->estoque[0]->num_itens; j++) {
            ItemEstoque *item = f->estoque[0]->itens[j];
            printf("  Produto: %s, Preco: %.2lf, Qtd: %d\n",
                   (*(item->produto))->nome,
                   (*(item->produto))->valor,
                   item->quantidade);
        }
    }
}


void liberar(Supermercado *super, TipoProduto **produtos, int num_produtos) {
    for(int i = 0; i < num_produtos; i++) {
        free(produtos[i]->nome);
        free(produtos[i]);
    }
    free(produtos);

    for(int i = 0; i < super->num_filiais; i++) {
        for(int j = 0; j < super->filiais[i]->estoque[0]->num_itens; j++) {
            free(super->filiais[i]->estoque[0]->itens[j]);
        }
        free(super->filiais[i]->estoque[0]->itens);
        free(super->filiais[i]->estoque[0]);
        free(super->filiais[i]->estoque);
        free(super->filiais[i]->nome);
        free(super->filiais[i]);
    }
    free(super->filiais);
    free(super->nome);
    free(super);
}

int main() {
    TipoProduto **produtos;
    int num_produtos;
    Supermercado *super;

    produtos = cadastrar_produtos(&num_produtos);
    super = criar_supermercado();
    criar_filiais(super);
    preencher_estoque(super, produtos, num_produtos);
    calcular_valores_super(super);
    imprimir(super);
    liberar(super, produtos, num_produtos);

    return 0;
}


//VER PONTEIRO DE PONTEIRO NOVEMENTE, MINHA PASTA NO GITHUB... 
//DIFICULDADE EM UM POUCO A ORGANIZAÇÃO DA MEMORIA...
//PERCORRENDO E QUEBRANDO.....