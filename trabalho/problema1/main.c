#include <stdio.h>

typedef struct nodo {
    float dado;
    int lin, col;
    struct nodo * proximo;
} Matriz_Esparsa;

void inicia_matriz(Matriz_Esparsa ** matriz) {
    *matriz = NULL;
}

Matriz_Esparsa * cria_nodo() {
    Matriz_Esparsa * nodo;
    nodo = (Matriz_Esparsa *) malloc(sizeof(Matriz_Esparsa));
    if (!nodo) {
        printf("Problema na alocação");
        exit(0);
    }
    return nodo;
}

void insere_final_matriz(Matriz_Esparsa ** matriz, float dado, int lin, int col) {
    Matriz_Esparsa * nodo = cria_nodo();
    nodo->dado = dado;
    nodo->lin = lin;
    nodo->col = col;
    nodo->proximo = NULL;
    if (*matriz == NULL) {
        *matriz = nodo;
    } else {
        Matriz_Esparsa * aux = *matriz;
        while (aux->proximo != NULL) {
            aux = aux->proximo;
        }
        aux->proximo = nodo;
    }
}

Matriz_Esparsa * busca_por_posicao(Matriz_Esparsa ** matriz, int lin, int col) {
    Matriz_Esparsa *aux = *matriz;
    while (aux != NULL) {
        if (aux->lin == lin && aux->col == col) return aux;
        aux = aux->proximo; 
    }
    return NULL;
}

void imprime_matriz(Matriz_Esparsa ** matriz, int tamanho_linhas, int tamanho_colunas) {
    if (*matriz == NULL) return 0;
    Matriz_Esparsa * aux;
    int linha;
    for (linha = 0; linha < tamanho_linhas; linha++) {
        int coluna;
        for (coluna = 0; coluna < tamanho_colunas; coluna++) {
            aux = busca_por_posicao(&(*matriz), linha, coluna);
            float dado = 0;
            if (aux) dado = aux->dado;
            printf("%.2f  ", dado);
        }
        printf("\n");
    }
}

void imprime_diagonal_principal(Matriz_Esparsa ** matriz, int tamanho_linhas, int tamanho_colunas) {
    if (*matriz == NULL) return 0;
    Matriz_Esparsa * aux;
    printf("Diagonal principal: \n");
    int linha;
    for (linha = 0; linha < tamanho_linhas; linha++) {
        int coluna;
        for (coluna = 0; coluna < tamanho_colunas; coluna++) {
            if (linha != coluna) continue;
            aux = busca_por_posicao(&(*matriz), linha, coluna);
            float dado = 0;
            if (aux) dado = aux->dado;
            printf("%.2f ", dado);
        }
    }
}

void libera_matriz(Matriz_Esparsa ** matriz) {
    if (*matriz == NULL) return 0;
    Matriz_Esparsa * aux;
    while (*matriz != NULL) {
        aux = *matriz;
        *matriz = (*matriz)->proximo;
        free(aux);
    }
    free(*matriz);
}

void receber_matriz(Matriz_Esparsa ** matriz, int tamanho_linhas, int tamanho_colunas) {
    int linha;
    for (linha = 0; linha < tamanho_linhas; linha++) {
        int coluna;
        for (coluna = 0; coluna < tamanho_colunas; coluna++) {
            float dado;
            printf("Insira o dado da posição [%i][%i]\n", linha, coluna);
            scanf("%f",&dado);
            if (dado != 0) insere_final_matriz(&(*matriz), dado, linha, coluna);
        }
    }
}

int main() {
    Matriz_Esparsa * matriz;
    inicia_matriz(&matriz);

    int tamanho_linhas;
    printf("Digite o tamanho das linhas\n");
    scanf("%d", &tamanho_linhas);
    int tamanho_colunas;
    printf("Digite o tamanho das colunas\n");
    scanf("%d", &tamanho_colunas);

    receber_matriz(&matriz, tamanho_linhas, tamanho_colunas);

    // imprime_matriz(&matriz, tamanho_linhas, tamanho_colunas);

    imprime_diagonal_principal(&matriz, tamanho_linhas, tamanho_colunas);

    libera_matriz(&matriz);

    return 1;
}

/*
*/