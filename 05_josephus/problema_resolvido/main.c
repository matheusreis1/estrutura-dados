#include <stdio.h>
#include <stdlib.h>

typedef struct Bloco {
    char nome;
    struct Bloco * prox;
} Nodo;

void inicializa_lista(Nodo ** lista) {
    *lista = NULL;
}

Nodo * cria_nodo() {
    Nodo * ponteiro;
    ponteiro = (Nodo *) malloc(sizeof(Nodo));
    if (!ponteiro) {
        printf("Problema de alocação");
        exit(0);
    }
    return ponteiro;
}

void insere_esquerda(Nodo ** lista, char nome) {
    Nodo *ponteiro;
    ponteiro = cria_nodo();
    ponteiro->nome = nome;
    if (*lista == NULL) {
        ponteiro->prox = ponteiro;
        *lista = ponteiro;
    } else {
        ponteiro->prox = (*lista)->prox;
        (*lista)->prox = ponteiro;
    }
}

void ordena_lista(Nodo ** lista, char nome) {
    if (lista == NULL) {
        printf("Lista vazia!");
        exit(0);
    }
    Nodo * aux = * lista;
    while (aux->nome != nome) {
        aux = aux->prox;
    }
    * lista = aux;
}

void procura(Nodo ** lista) {
    if (lista == NULL) {
        printf("Lista vazia!");
        exit(0);
    }
    Nodo * aux;
    aux = * lista;
    while (aux->prox != *lista) {
        printf("nome da vez: %c\n", aux->nome);
        aux = aux->prox;
    }
    // printf("nome da vez: %c\n", aux->nome);
}

void insere_direita(Nodo ** lista, char nome) {
    Nodo *ponteiro, *aux;
    ponteiro = cria_nodo();
    ponteiro->nome = nome;
    if (*lista == NULL) {
        ponteiro->prox = ponteiro;
        *lista = ponteiro;
    } else {
        aux = *lista;
        while (aux->prox != *lista)
            aux = aux->prox;
        aux->prox = ponteiro;
        ponteiro->prox = *lista;
    }
}

void remove_nodo_esquerda(Nodo ** lista, char * nome) {
    Nodo * ponteiro;
    if (*lista == NULL) {
        printf("Lista circular vazia");
    } else {
        ponteiro = (*lista)->prox;
        *nome = ponteiro->nome;
        if (*lista == ponteiro)
            *lista = NULL;
        else 
            (*lista)->prox = ponteiro->prox;
        free(ponteiro);
    }
}

int main() {
    int numero_sorteado;
    printf("Digite o numero sorteado: \n");
    scanf("%i", &numero_sorteado);

    Nodo * lista;
    inicializa_lista(&lista);

    char nome;
    while (nome != ':') {
        printf("Digite o nome do soldado: \n");
        scanf(" %c", &nome);
        if (nome != ':')
            insere_direita(&lista, nome);
    }

    // char nome_inicio_contagem;
    // printf("Digite o nome de onde a contagem deve começar: \n");
    // scanf(" %c", &nome_inicio_contagem);

    // ordena_lista(&lista, nome_inicio_contagem);
    
    
    

    // char nome_removido;
    // remove_nodo_esquerda(&lista, &nome_removido);
    // printf("Soldado %s removido \n", nome_removido);
    
    
    // enquanto a lista tiver mais que 1 item
    // while (lista->prox != *lista)

    // ordena lista
    
    // faz a contagem enquanto o count for menor ou igual a numero_sorteado

    
    // mostra a ordem de como ficou a lista
    procura(&lista);
}

/*
O Problema Josephus é um problema clássico de lista linear circular.

Este problema postula um grupo de soldados circundados por uma força inimiga esmagadora. 
Não há esperanças na vitória sem a chegada de reforços, mas existe somente um cavalo disponível para escapar. 
Os soldados entram em um acordo para determinar qual deles deverá escapar e trazer ajuda. 
Eles formam um círculo e um número N é sorteado num chapéu. 
Um de seus nomes é sorteado também. 
Começando pelo soldado cujo nome foi sorteado, eles começam a contar ao longo do círculo em sentido horário. 
Quando a contagem alcança N, esse soldado é retirado do círculo, e a contagem reinicia com o soldado seguinte. 
O processo continua de maneira que, toda vez que N é alcançado, outro soldado sai do círculo. 
Todo soldado retirado do círculo não entra mais na contagem. 
O último soldado que restar deverá montar no cavalo e escapar. 
Considerando um número N, a ordenação dos soldados no círculo e o soldado a partir da qual começa a contagem, o problema é determinar a sequência na qual os soldados são eliminados do círculo e o soldado que escapará. 
A entrada para o programa é: 
- o número N; 
- lista de nomes (devem ser armazenados em uma lista circular encadeada) que será o sequenciamento do círculo no sentido horário; 
- nome do soldado onde deve iniciar a contagem. 
Para indicar o final da entrada de nomes o usuário deve digitar dois pontos (:). 
O programa deve imprimir os nomes na sequência em que são eliminados e o nome do soldado que escapará. 
OBS: Você pode utilizar como nomes para os soldados as letras do alfabeto: soldado A, B, C, D, etc.

Teste o programa com as seguintes entradas:
 N = 4

Nomes dos soldados = A, B, C, D, E, F, G, H, I, J

A contagem inicia no soldado: E
*/
