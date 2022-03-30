#include <stdio.h>
#include "operacoes.h"

void inicia_lista_rotas(Rota **rotas) {
    *rotas = NULL;
}

Rota * criar_rota() {
    Rota * rota;
    rota = (Rota *) malloc(sizeof(Rota));
    if (!rota) {
        printf("Problema na alocação!\n");
        exit(0);
    }
    return rota;
}

void inicializa_lista_cidades(CidadeHeader *cidades) {
    cidades->quantidade = 0;
    cidades->primeiro = NULL;
    cidades->ultimo = NULL;
}

Cidade * criar_cidade() {
    Cidade * cidade;
    cidade = (Cidade *) malloc(sizeof(Cidade));
    if (!cidade) {
        printf("Problema na alocação!\n");
        exit(0);
    }
    return cidade;
}

void inserir_cidade(CidadeHeader *cidades, char nomeCidade, char descricaoCidade) {
    Cidade * cidade;
    cidade = criar_cidade();
    cidade->nome = nomeCidade;
    cidade->descricao = descricaoCidade;
    cidade->proximo = NULL;
    cidade->anterior = cidades->ultimo;
    if (cidades->ultimo != NULL)
        cidades->ultimo->proximo = cidade;
    cidades->ultimo = cidade;
    cidades->quantidade += 1;
    if (cidades->primeiro == NULL)
        cidades->primeiro = cidade;
}

void apresentar_cidades(CidadeHeader *cidades) {
    if (!cidades || cidades == NULL || cidades->quantidade == 0) {
        printf("lista vazia");
        exit(0);
    }
    Cidade * atual;
    atual = cidades->primeiro;

    while (atual != NULL) {
        printf("Cidade: %c\nDescriçãoÇ %c", atual->nome, atual->descricao);
        printf("1 - Ir para próxima cidade\n2 - Voltar para cidade anterior\n");
        int escolha;
        scanf("%i", &escolha);

        if (escolha == 1) {
            atual = atual->proximo;
        }
        if (escolha == 2) {
            atual = atual->anterior;
        }
    }
}

int main() {
    CidadeHeader cidades;
    inicializa_lista_cidades(&cidades);

    inserir_cidade(&cidades, 'A', 'A');
    inserir_cidade(&cidades, 'B', 'B');
    inserir_cidade(&cidades, 'C', 'C');

    apresentar_cidades(&cidades);
}

/*
*/
