#include <stdio.h>

typedef struct nodo {
    float dado;
    int lin, col;
    struct nodo * proximo;
} Matriz_Esparsa;

void inicia_lista(Matriz_Esparsa ** lista) {
    *lista = NULL;
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

void insere_final_lista(Matriz_Esparsa ** lista, float dado, int lin, int col) {
    Matriz_Esparsa * nodo = cria_nodo();
    nodo->dado = dado;
    nodo->lin = lin;
    nodo->col = col;
    nodo->proximo = NULL;
    if (*lista == NULL) {
        *lista = nodo;
    } else {
        Matriz_Esparsa * aux = *lista;
        while (aux->proximo != NULL) {
            aux = aux->proximo;
        }
        aux->proximo = nodo;
    }
}

void imprime_lista(Matriz_Esparsa ** lista) {
    if (*lista == NULL) return 0;
    Matriz_Esparsa * aux = *lista;
    while (aux != NULL) {
        printf("Dado: %f\n", aux->dado);
        aux = aux->proximo;
    }
}

void libera_lista(Matriz_Esparsa ** lista) {
    if (*lista == NULL) return 0;
    Matriz_Esparsa * aux;
    while (*lista != NULL) {
        aux = *lista;
        *lista = (*lista)->proximo;
        free(aux);
    }
    free(*lista);
}

int main() {
    Matriz_Esparsa * matriz;

    inicia_lista(&matriz);

    insere_final_lista(&matriz, 10.0, 0, 0);
    insere_final_lista(&matriz, 20.0, 0, 1);
    insere_final_lista(&matriz, 0.0, 1, 0);
    insere_final_lista(&matriz, 40.0, 1, 1);

    imprime_lista(&matriz);

    libera_lista(&matriz);

    imprime_lista(&matriz);

    return 1;
}

/*
*/
