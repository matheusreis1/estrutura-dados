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

int insere_lista_inicio(Lista * li, Aluno aluno) {
    if (li == NULL) return 0;
    Elemento * node = (Elemento *) malloc(sizeof(Elemento));
    if (node == NULL) return 0;
    node->dados = aluno;
    node->prox = (* li);
    * li = node;
    return 1;
}

int insere_lista_final(Lista * li, Aluno aluno) {
    if (li == NULL) return 0;
    Elemento * node = (Elemento *) malloc(sizeof(Elemento));
    if (node == NULL) return 0;
    node->dados = aluno;
    node->prox = NULL;
    if ((* li) == NULL) { // lista vazia, insere no inicio
        * li = node;
    } else {
        Elemento * aux = * li;
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = node;
    }
    return 1;
}

int insere_lista_ordenada(Lista * li, Aluno aluno) {
    if (li == NULL) return 0;
    Elemento * node = (Elemento *) malloc(sizeof(Elemento));
    if (node == NULL) return 0;
    node->dados = aluno;
    if (lista_vazia(li)) {
        node->prox = (*li);
        * li = node;
        return 1;
    } else {
        Elemento * anterior, * atual = * li;
        while (atual != NULL && atual->dados.matricula < aluno.matricula) {
            anterior = atual;
            atual = atual->prox;
        }
        if (atual == * li) {
            node->prox = (*li);
            *li = node;
        } else {
            node->prox = anterior->prox;
            anterior->prox = node;
        }
        return 1;
    }
}

int remove_lista_inicio(Lista * li) {
    if (li == NULL) return 0;
    if((*li) == NULL) return 0;
    Elemento * node = *li;
    *li = node->prox;
    free(node);
    return 1;
}

int remove_lista_final(Lista * li) {
    if (li == NULL) return 0;
    if ((*li) == NULL) return 0;
    Elemento * previousNode, * node = *li;
    while (node->prox != NULL) {
        previousNode = node;
        node = node->prox;
    }
    if (node == (*li))
        *li = node->prox;
    else
        previousNode->prox = node->prox;
    free(node);
    return 1;
}

int remove_lista(Lista * li, int matricula) {
    if (li == NULL) return 0;
    Elemento * previousNode, * node = *li;
    while (node != NULL && node->dados.matricula != matricula) {
        previousNode = node;
        node = node->prox;
    }
    if (node == NULL) return 0;
    if (node == *li)
        *li = node->prox;
    else
        previousNode->prox = node->prox;
    free(node);
    return 1;
}

int consulta_lista_posicao(Lista * li, int posicao, Aluno * aluno) {
    if (li == NULL || posicao <= 0) return 0;
    Elemento * node = *li;
    int i = 1;
    while (node != NULL && i < posicao) {
        node = node->prox;
        i++;
    }
    if (node == NULL) return 0;
    else {
        *aluno = node->dados;
        return 1;
    }
}

int consulta_lista_matricula(Lista * li, int matricula, Aluno * aluno) {
    if (li == NULL) return 0;
    Elemento * node = *li;
    while (node->prox != NULL && node->dados.matricula != matricula) {
        node = node->prox;
    }
    if (node == NULL) return 0;
    else {
        *aluno = node->dados;
        return 1;
    }
}

int main() {
    Lista * li;

    li = cria_lista();

    printf("Hello World!");
}

/*
*/
