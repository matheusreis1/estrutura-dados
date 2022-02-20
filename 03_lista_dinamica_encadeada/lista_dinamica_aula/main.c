#include <stdio.h>
#include "ListaDinEncadeada.h"

typedef struct elemento {
    Aluno dados;
    struct elemento * prox;
} Elemento;

Lista * cria_lista() {
    Lista * li = (Lista *) malloc(sizeof(Lista));
    if (li != NULL) {
        * li = NULL;
    }
    return li;
}

void libera_lista(Lista * li) {
    if (li != NULL) {
        Elemento * no;
        while ((* li) != NULL) {
            no = * li;
            * li = (* li)->prox;
            free(no);
        }
        free(li);
    }
}

int tamanho_lista(Lista * li) {
    if (li == NULL) return 0;
    int count = 0;
    Elemento * no = * li;
    while (no != NULL) {
        count++;
        no = no->prox;
    }
    return count;
}

int lista_cheia(Lista * li) {
    return 0;
}

int lista_vazia(Lista * li) {
    if (li == NULL) return 1;
    if (*li == NULL) return 1;
    return 0;
}

int main() {
    Lista * li;

    li = cria_lista();

    printf("Hello World!");
}

/*
*/
