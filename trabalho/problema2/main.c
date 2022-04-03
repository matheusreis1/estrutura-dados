#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LIMIT 64

typedef struct cidade {
    char descricao[MAX_LIMIT];
    char nome[MAX_LIMIT];
    struct cidade *proximo;
    struct cidade *anterior;
} Cidade;

typedef struct cidadeHeader {
    int quantidade;
    Cidade *primeiro, *ultimo;
} CidadeHeader;

typedef struct rota {
    CidadeHeader *cidades;
    char nome[MAX_LIMIT];
    struct rota *proximo;
} Rota;

void iniciar_lista_cidades(CidadeHeader **cidades) {
    *cidades = (CidadeHeader*) malloc(sizeof(CidadeHeader));
    (*cidades)->quantidade = 0;
    (*cidades)->primeiro = NULL;
    (*cidades)->ultimo = NULL;
}

Cidade * criar_cidade() {
    Cidade * cidade = (Cidade *) malloc(sizeof(Cidade));
    if (!cidade) {
        printf("Problema na alocação!\n");
        exit(0);
    }
    return cidade;
}

void inserir_cidade(CidadeHeader **cidades, char nomeCidade[], char descricaoCidade[]) {
    Cidade *cidade = criar_cidade();
    strcpy((*cidade).nome, nomeCidade);
    strcpy((*cidade).descricao, descricaoCidade);
    cidade->proximo = NULL;
    cidade->anterior = (*cidades)->ultimo;
    if ((*cidades)->ultimo != NULL)
        (*cidades)->ultimo->proximo = cidade;
    (*cidades)->ultimo = cidade;
    (*cidades)->quantidade += 1;
    if ((*cidades)->primeiro == NULL)
        (*cidades)->primeiro = cidade;
}

void apresentar_cidades(CidadeHeader *cidades) {
    if (!cidades || (cidades)->quantidade == 0) {
        printf("lista vazia");
        exit(0);
    }
    Cidade * atual;
    atual = (cidades)->primeiro;

    while (atual != NULL) {
        printf("Cidade: %s\nDescrição: %s\n", atual->nome, atual->descricao);
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

void iniciar_lista_rotas(Rota **rotas) {
    *rotas = NULL;
}

Rota * criar_rota() {
    Rota *rota = (Rota*) malloc(sizeof(Rota));
    if (!rota) {
        printf("Problema na alocação!\n");
        exit(0);
    }
    return rota;
}

void inserir_rota(Rota ** rotas, char nome[], CidadeHeader **cidades) {
    Rota *rota = criar_rota();
    strcpy(rota->nome, nome);
    rota->cidades = *cidades;
    rota->proximo = NULL;
    if ((*rotas) == NULL) {
        *rotas = rota;
    } else {
        Rota *auxiliar = *rotas;
        while (auxiliar->proximo != NULL) {
            auxiliar = auxiliar->proximo;
        }
        auxiliar->proximo = rota;
    }
}

void excluir_cidades(CidadeHeader **cidades) {
    Cidade * atual = (*cidades)->primeiro;
    for (int count = 0; count < (*cidades)->quantidade; count++) {
        Cidade *auxiliar = atual->proximo;
        free(atual);
        atual = auxiliar;
    }
    free(atual);
    free(*cidades);
}

void excluir_rota(Rota **rotas, char nomeRota[]) {
    if (*rotas == NULL) return;
    Rota *atual = *rotas;
    Rota *anterior = (Rota*) malloc(sizeof(Rota));
    while (atual != NULL && atual->nome != nomeRota) {
        anterior = atual;
        atual = atual->proximo;
    }
    if (atual == NULL) {
        printf("Rota não encontrada!\n");
        return;
    }
    if (atual == *rotas)
        *rotas = atual->proximo;
    else
        anterior->proximo = atual->proximo;
    excluir_cidades(&(atual)->cidades);
    free(atual);
}

void apresentar_rota(Rota *rota) {
    if (rota != NULL)
        printf("Nome: %s\n", rota->nome);
}

void apresentar_rotas(Rota ** rotas) {
    if (*rotas == NULL) return;
    printf("Rotas disponiveis:\n");
    Rota *atual = *rotas;
    int numero = 1;
    do {
        printf("Rota #%i:\n", numero);
        apresentar_rota(atual);
        atual = atual->proximo;
        numero++;
    } while (atual != NULL);
}

void acessar_rota(Rota *rotas, char nomeRota[], Rota **busca) {
    Rota *auxiliar;
    if (rotas == NULL) {
        printf("Lista esta vazia\n");
        *busca = NULL;
    } else {
        for (auxiliar = rotas; auxiliar != NULL; auxiliar = auxiliar->proximo) {
            if (strcmp(auxiliar->nome, nomeRota) == 0) {
                *busca = auxiliar;
                break;
            }
        }
    }
}

int main() {
    Rota * rotas;
    iniciar_lista_rotas(&rotas);

    int escolha = 0;
    while (escolha != 4) {
        printf("---- Menu ----\n");
        printf(" 1. Cadastrar rota\n");
        printf(" 2. Excluir rota\n");
        printf(" 3. Visitar rota\n");
        printf(" 4. Sair\n");
        scanf("%i", &escolha);
        switch (escolha) {
            case 1:
                printf("Digite o nome da rota:\n");
                char nomeRota[MAX_LIMIT];
                scanf(" %[^\n]%*c", nomeRota);
                CidadeHeader * cidades;
                iniciar_lista_cidades(&cidades);

                int escolhaCidades = 0;
                while (escolhaCidades != 2) {
                    printf("---- Menu ----\n");
                    printf(" 1. Cadastrar nova cidade\n");
                    printf(" 2. Sair\n");
                    scanf("%i", &escolhaCidades);
                    if (escolhaCidades == 1) {
                        printf("Digite o nome da cidade:\n");
                        char nomeCidade[MAX_LIMIT];
                        scanf(" %[^\n]%*c", nomeCidade);
                        printf("Digite a descrição da cidade:\n");
                        char descricaoCidade[MAX_LIMIT];
                        scanf(" %[^\n]%*c", descricaoCidade);
                        inserir_cidade(&cidades, nomeCidade, descricaoCidade);
                    } else break;
                }
                inserir_rota(&rotas, nomeRota, &cidades);
                break;
            case 2:
                printf("Digite o nome da rota que deseja excluir:\n");
                char nome[MAX_LIMIT];
                scanf (" %[^\n]%*c", nome);
                excluir_rota(&rotas, nome);
                break;
            case 3:
                apresentar_rotas(&rotas);
                printf("Digite o nome da rota que deseja visitar:\n");
                Rota * rotaVisita;
                char nomeRotaVisita[MAX_LIMIT];
                scanf (" %[^\n]%*c", nomeRotaVisita);
                acessar_rota(rotas, nomeRotaVisita, &rotaVisita);
                if (rotaVisita)
                    apresentar_cidades(rotaVisita->cidades);
                break;
            case 4:
                break;
            default:
                printf("Opção inválida!\n");
                break;
        }
    }
}
