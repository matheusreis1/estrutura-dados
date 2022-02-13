#include <stdio.h>
#include "ListaSequencial.h"

struct lista {
    int quantidade;
    Aluno dados[MAX];
};

Lista* cria_lista() {
    Lista *li;
    li = (Lista*) malloc(sizeof(struct lista));
    if (li != NULL)
        li->quantidade = 0;
    return li;
}

void libera_lista(Lista* li) {
    free(li);
}

int tamanho_lista(Lista* li) {
    if (li == NULL)
        return -1;
    return li->quantidade;
}

int lista_cheia(Lista* li) {
    if (li == NULL) 
        return -1;
    return (li->quantidade == MAX);
}

int lista_vazia(Lista* li) {
    if (li == NULL) 
        return -1;
    return (li->quantidade == 0);
}

int insere_lista_final(Lista* li, Aluno al) {
    if (li == NULL || lista_cheia(li))
        return 0;

    li->dados[li->quantidade] = al;
    li->quantidade++;

    return 1;
}

int insere_lista_inicio(Lista* li, Aluno al) {
    if (li == NULL || lista_cheia(li))
        return 0;

    int i;

    for (i=li->quantidade - 1; i >= 0; i--)
        li->dados[i+1] = li->dados[i];

    li->dados[0] = al;
    li->quantidade++;

    return 1;
}

int insere_lista_ordenada(Lista* li, Aluno al) {
    if (li == NULL || lista_cheia(li))
        return 0;

    int k, i = 0;

    while (i < li->quantidade && li->dados[i].matricula < al.matricula)
        i++;

    for (k = li->quantidade-1; k >= i; k--)
        li->dados[k+1] = li->dados[k];

    li->dados[i] = al;
    li->quantidade++;

    return 1;
}

int remove_lista_final(Lista* li) {
    if (li == NULL || lista_vazia(li))
        return 0;

    li->quantidade--;
    return 1;
}

int remove_lista_inicio(Lista* li) {
    if (li == NULL || lista_vazia(li))
        return 0;

    int k = 0;

    for (k = 0; k >= li->quantidade-1; k++)
        li->dados[k] = li->dados[k+1];

    li->quantidade--;

    return 1;
}

int remove_lista(Lista* li, int matricula) {
    if (li == NULL || lista_vazia(li))
        return 0;

    int k, i = 0;

    while (i < li->quantidade && li->dados[i].matricula != matricula)
        i++;

    if (i == li->quantidade) // elemento nao encontrado
        return 0;

    for (k = i; k < li->quantidade - 1; k++)
        li->dados[k] = li->dados[k+1];

    li->quantidade--;
    return 1;
}

int consulta_lista_posicao(Lista* li, int posicao, Aluno *al) {
    if (li == NULL || posicao <= 0 || posicao > li->quantidade)
        return 0;

    *al = li->dados[posicao-1];
    return 1;
}

int consulta_lista_matricula(Lista* li, int matricula, Aluno *al) {
    if (li == NULL)
        return 0;
    
    int k, i = 0;
    while (i < li->quantidade && li->dados[i].matricula != matricula)
        i++;
    
    if (li == li->quantidade)
        return 0;
    
    *al = li->dados[i];
    return 1;    
}

void imprimir_lista(Lista* li) {
    if (li == NULL || lista_vazia(li))
        return 0;

    int i;
    
    for (i = 0; i <= li->quantidade - 1; i++) {
        printf("Matricula: %d\n", li->dados[i].matricula);
        printf("Nome: %s\n", li->dados[i].nome);
        printf("Nota 1: %.2f\n", li->dados[i].n1);
        printf("Nota 2: %.2f\n", li->dados[i].n2);
        printf("Nota 3: %.2f\n", li->dados[i].n3);
    }
}

int main() {
    Lista *li;

    li = cria_lista();

    // int size = tamanho_lista(li);
    // int is_full_filled = lista_cheia(li);
    // int is_empty = lista_vazia(li);

    Aluno aluno;
    strcpy(aluno.nome, "Matheus");
    aluno.matricula = 1;
    aluno.n1 = 10.0;
    aluno.n2 = 9.0;
    aluno.n3 = 8.5;

    insere_lista_final(li, aluno);

    imprimir_lista(li);

    libera_lista(li);
}

/*
*/
