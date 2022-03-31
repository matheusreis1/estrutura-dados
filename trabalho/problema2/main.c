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

void inserir_rota(Rota **rotas, char nomeRota, CidadeHeader *cidades) {
    Rota *rota, *auxiliar;
    rota = criar_rota();
    rota->nome = nomeRota;
    rota->cidades = cidades;
    rota->proximo = NULL;
    if (*rotas == NULL) {
        *rotas = rota;
    } else {
        auxiliar = *rotas;
        while (auxiliar->proximo != NULL) {
            auxiliar = auxiliar->proximo;
        }
        auxiliar->proximo = rota;
    }
}

void excluir_rota(Rota **rotas, char nomeRota) {
    if (*rotas == NULL) return 0;
    Rota *atual, *anterior;
    atual = *rotas;
    while (atual != NULL && atual->nome != nomeRota) {
        anterior = atual;
        atual = atual->proximo;
    }
    if (atual == NULL) {
        printf("Rota não encontrada!\n");
        return 0;
    }
    if (atual == *rotas)
        *rotas = atual->proximo;
    else
        anterior->proximo = atual->proximo;
    free(atual);
}

void acessar_rota(Rota **rotas, char nomeRota, Rota **busca) {
    if (*rotas == NULL) return 0;
    Rota *atual;
    atual = *rotas;
    while (atual != NULL && atual->nome != nomeRota) {
        atual = atual->proximo;
    }
    if (atual == NULL) {
        printf("Rota não encontrada!\n");
        return 0;
    }
    *busca = atual;
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

int main() {
    Rota * rotas;
    inicia_lista_rotas(&rotas);

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
            CidadeHeader cidades;
            inicializa_lista_cidades(&cidades);

            int escolhaCidades;
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
            acessar_rota(&rotas, nomeRotaVisita, &rotaVisita);
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

/*
*/
