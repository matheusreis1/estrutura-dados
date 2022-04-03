#include <stdio.h>
#include <stdlib.h>

typedef struct cidade {
    char descricao;
    char nome;
    struct cidade *proximo;
    struct cidade *anterior;
} Cidade;

typedef struct cidadeHeader {
    int quantidade;
    Cidade *primeiro, *ultimo;
} CidadeHeader;

typedef struct rota {
    CidadeHeader *cidades;
    char nome;
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

void inserir_cidade(CidadeHeader **cidades, char nomeCidade, char descricaoCidade) {
    Cidade *cidade = criar_cidade();
    cidade->nome = nomeCidade;
    cidade->descricao = descricaoCidade;
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
    if (!cidades || (cidades) == NULL || (cidades)->quantidade == 0) {
        printf("lista vazia");
        exit(0);
    }
    Cidade * atual;
    atual = (cidades)->primeiro;

    while (atual != NULL) {
        printf("Cidade: %c\nDescrição: %c\n", atual->nome, atual->descricao);
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

void inserir_rota(Rota ** rotas, char nome, CidadeHeader **cidades) {
    Rota *rota = criar_rota();
    rota->nome = nome;
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

void excluir_rota(Rota **rotas, char nomeRota) {
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
        printf("Nome: %c\n", rota->nome);
}

void acessar_rota(Rota *rotas, char nomeRota, Rota **busca) {
    Rota *auxiliar;
    if (rotas == NULL) {
        printf("Lista esta vazia\n");
        *busca = NULL;
    } else {
        for (auxiliar = rotas; auxiliar != NULL; auxiliar = auxiliar->proximo) {
            apresentar_rota(auxiliar);
            if (auxiliar->nome == nomeRota) {
                *busca = auxiliar;
                break;
            }
        }
    }
}

int main() {
    Rota * rotas;
    iniciar_lista_rotas(&rotas);

    int escolha;
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
                char nomeRota;
                scanf(" %c", &nomeRota);
                CidadeHeader * cidades;
                iniciar_lista_cidades(&cidades);

                int escolhaCidades = 0;
                while (escolhaCidades != 2) {
                    printf("---- Menu ----\n");
                    printf(" 1. Cadastrar nova cidade\n");
                    printf(" 2. Sair\n");
                    scanf("%i", &escolhaCidades);
                    switch (escolhaCidades) {
                        case 1:
                            printf("Digite o nome da cidade:\n");
                            char nomeCidade;
                            scanf(" %c", &nomeCidade);
                            printf("Digite a descrição da cidade:\n");
                            char descricaoCidade;
                            scanf(" %c", &descricaoCidade);
                            inserir_cidade(&cidades, nomeCidade, descricaoCidade);
                            break;
                        default:
                            escolhaCidades = 2;
                            break;
                    }
                }
                inserir_rota(&rotas, nomeRota, &cidades);
                break;
            case 2:
                printf("Digite o nome da rota que deseja excluir:\n");
                char nome;
                scanf(" %c", &nome);
                excluir_rota(&rotas, nome);
                break;
            case 3:
                printf("Digite o nome da rota que deseja visitar:\n");
                Rota * rotaVisita;
                char nomeRotaVisita;
                scanf(" %c", &nomeRotaVisita);
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
