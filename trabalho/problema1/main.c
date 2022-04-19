#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
    float dado;
    int lin, col;
    struct nodo * proximo;
} Matriz_Esparsa;

typedef struct matriz_esparsa_header {
    int indice;
    int quantidade_linhas, quantidade_colunas;
    Matriz_Esparsa * matriz;
} MatrizEsparsaHeader;

typedef struct lista_matriz {
    MatrizEsparsaHeader * matriz;
    struct lista_matriz *proximo;
} Matriz;

void iniciar_lista_matrizes(Matriz ** matrizes) {
    *matrizes = NULL;
}
void iniciar_matriz_esparsa(Matriz_Esparsa ** matriz) {
    *matriz = NULL;
}
Matriz * criar_matriz() {
    Matriz * matriz = (Matriz *) malloc(sizeof(Matriz));
    if (!matriz) {
        printf("Problema na alocação");
        exit(0);
    }
    return matriz;
}
Matriz_Esparsa * criar_matriz_esparsa() {
    Matriz_Esparsa * nodo = (Matriz_Esparsa *) malloc(sizeof(Matriz_Esparsa));
    if (!nodo) {
        printf("Problema na alocação");
        exit(0);
    }
    return nodo;
}
MatrizEsparsaHeader * criar_header(Matriz_Esparsa *matrizEsparsa, int linhas, int colunas, int indice) {
    MatrizEsparsaHeader * header = (MatrizEsparsaHeader *) malloc(sizeof(MatrizEsparsaHeader));
    if (!header) {
        printf("Problema na alocação");
        exit(0);
    }
    header->indice = indice;
    header->quantidade_linhas = linhas;
    header->quantidade_colunas = colunas;
    header->matriz = matrizEsparsa;
    return header;
}
void insere_final_matriz(Matriz_Esparsa ** matriz, float dado, int lin, int col) {
    Matriz_Esparsa * matrizEsparsa = criar_matriz_esparsa();
    matrizEsparsa->dado = dado;
    matrizEsparsa->lin = lin;
    matrizEsparsa->col = col;
    matrizEsparsa->proximo = NULL;
    if (*matriz == NULL) {
        *matriz = matrizEsparsa;
    } else {
        Matriz_Esparsa *atual = *matriz;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = matrizEsparsa;
    }
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
void adicionar_matriz(Matriz ** matrizes, Matriz_Esparsa **matrizEsparsa, int quantidade_linhas, int quantidade_colunas) {
    int indice = 1;
    MatrizEsparsaHeader * header = criar_header(*matrizEsparsa, quantidade_linhas, quantidade_colunas, indice);
    Matriz * matriz = criar_matriz();
    matriz->matriz = header;
    matriz->proximo = NULL;
    if ((*matrizes) == NULL) {
        *matrizes = matriz;
    } else {
        Matriz *auxiliar = *matrizes;
        while (auxiliar->proximo != NULL) {
            auxiliar = auxiliar->proximo;
        }
        matriz->matriz->indice = auxiliar->matriz->indice + 1;
        auxiliar->proximo = matriz;
    }
}
void libera_matriz_espersa(Matriz_Esparsa ** matriz) {
    if (*matriz == NULL) return;
    Matriz_Esparsa * aux;
    while (*matriz != NULL) {
        aux = *matriz;
        *matriz = (*matriz)->proximo;
        free(aux);
    }
    free(*matriz);
}
void libera_matriz_header(MatrizEsparsaHeader * header) {
    free(header);
}
void libera_lista_matrizes(Matriz ** lista) {
    if (*lista == NULL) return;
    Matriz * atual;
    while (*lista != NULL) {
        atual = *lista;
        libera_matriz_espersa(&atual->matriz->matriz);
        libera_matriz_header(atual->matriz);
        *lista = (*lista)->proximo;
        free(atual);
    }
    free(*lista);
}

Matriz_Esparsa * busca_por_posicao_matriz_esparsa(Matriz_Esparsa ** matriz, int lin, int col) {
    Matriz_Esparsa *nodo = *matriz;
    while (nodo != NULL) {
        if (nodo->lin == lin && nodo->col == col) return nodo;
        nodo = nodo->proximo;
    }
    return NULL;
}
void imprimir_matriz_formatada(Matriz_Esparsa ** matriz, int tamanho_linhas, int tamanho_colunas) {
    Matriz_Esparsa *matrizEsparsa;
    int linha;
    for (linha = 0; linha < tamanho_linhas; linha++) {
        int coluna;
        for (coluna = 0; coluna < tamanho_colunas; coluna++) {
            matrizEsparsa = busca_por_posicao_matriz_esparsa(&(*matriz), linha, coluna);
            float dado = 0;
            if (matrizEsparsa) dado = matrizEsparsa->dado;
            printf("%.2f  ", dado);
        }
        printf("\n");
    }
}
void imprimir_matriz_header(Matriz * matriz) {
    printf("Matriz #%i\n", matriz->matriz->indice);
    printf("Numero de linhas: %i\n", matriz->matriz->quantidade_linhas);
    printf("Numero de colunas %i\n", matriz->matriz->quantidade_colunas);
}
void imprimir_matrizes(Matriz ** matrizes) {
    printf("Matrizes disponiveis:\n");
    Matriz * atual;
    if ((*matrizes) == NULL) {
        printf("Lista esta vazia\n");
    } else {
        for (atual = *matrizes; atual != NULL; atual = atual->proximo) {
            imprimir_matriz_header(atual);
            imprimir_matriz_formatada(&atual->matriz->matriz, atual->matriz->quantidade_linhas, atual->matriz->quantidade_colunas);
        }
    }
}
void acessar_matriz(Matriz ** matrizes, int indice, Matriz **busca) {
    Matriz * atual;
    if ((*matrizes) == NULL) {
        printf("Lista esta vazia\n");
    } else {
        for (atual = *matrizes; atual != NULL; atual = atual->proximo) {
            if (atual->matriz->indice == indice) *busca = atual;
        }
    }
}
void imprimir_diagonal_principal(Matriz_Esparsa ** matriz, int tamanho_linhas, int tamanho_colunas) {
    if (*matriz == NULL) return;
    Matriz_Esparsa *matrizEsparsa;
    int linha;
    for (linha = 0; linha < tamanho_linhas; linha++) {
        int coluna;
        for (coluna = 0; coluna < tamanho_colunas; coluna++) {
            if (linha != coluna) {
                printf("  ");
                continue;
            }
            matrizEsparsa = busca_por_posicao_matriz_esparsa(&(*matriz), linha, coluna);
            float dado = 0;
            if (matrizEsparsa) dado = matrizEsparsa->dado;
            printf("%.2f  ", dado);
        }
        printf("\n");
    }
}
void imprimir_matriz_transposta(Matriz_Esparsa ** matriz, int tamanho_linhas, int tamanho_colunas) {
    if (*matriz == NULL) return;
    Matriz_Esparsa *matrizEsparsa, *transposta;
    iniciar_matriz_esparsa(&transposta);
    int linha;
    for (linha = 0; linha < tamanho_linhas; linha++) {
        int coluna;
        for (coluna = 0; coluna < tamanho_colunas; coluna++) {
            matrizEsparsa = busca_por_posicao_matriz_esparsa(&(*matriz), linha, coluna);
            float dado = 0;
            if (matrizEsparsa) dado = matrizEsparsa->dado;
            // o numero de colunas é o contrario ao de linhas
            insere_final_matriz(&transposta, dado, coluna, linha);
        }
    }
    // o numero de colunas é o contrario ao de linhas
    imprimir_matriz_formatada(&transposta, tamanho_colunas, tamanho_linhas);
}

void soma_matrizes(Matriz ** matrizes, MatrizEsparsaHeader * matrizAHeader, MatrizEsparsaHeader * matrizBHeader) {
    Matriz_Esparsa **matrizA = &matrizAHeader->matriz;
    Matriz_Esparsa **matrizB = &matrizBHeader->matriz;
    if (*matrizA == NULL || *matrizB == NULL) return;
    if (matrizAHeader->quantidade_linhas != matrizBHeader->quantidade_linhas ||
        matrizAHeader->quantidade_colunas != matrizBHeader->quantidade_colunas) {
        printf("A operação de soma só é possível quando o numero de linhas e colunas das matrizes são iguais!\n");
        return;
    }
    int tamanho_linhas = matrizAHeader->quantidade_linhas;
    int tamanho_colunas = matrizAHeader->quantidade_colunas;

    Matriz_Esparsa *nodoA, *nodoB, *resultado;
    iniciar_matriz_esparsa(&resultado);
    int linha;
    for (linha = 0; linha < tamanho_linhas; linha++) {
        int coluna;
        for (coluna = 0; coluna < tamanho_colunas; coluna++) {
            nodoA = busca_por_posicao_matriz_esparsa(&(*matrizA), linha, coluna);
            float dadoA = 0;
            if (nodoA) dadoA = nodoA->dado;
            nodoB = busca_por_posicao_matriz_esparsa(&(*matrizB), linha, coluna);
            float dadoB = 0;
            if (nodoB) dadoB = nodoB->dado;
            float soma = dadoA + dadoB;
            insere_final_matriz(&resultado, soma, linha, coluna);
        }
    }
    imprimir_matriz_formatada(&resultado, tamanho_linhas, tamanho_colunas);
    adicionar_matriz(matrizes, &resultado, tamanho_linhas, tamanho_colunas);
}
void subtrair_matrizes(MatrizEsparsaHeader * matrizAHeader, MatrizEsparsaHeader * matrizBHeader) {
    Matriz_Esparsa **matrizA = &matrizAHeader->matriz;
    Matriz_Esparsa **matrizB = &matrizBHeader->matriz;
    if (*matrizA == NULL || *matrizB == NULL) return;
    if (matrizAHeader->quantidade_linhas != matrizBHeader->quantidade_linhas ||
        matrizAHeader->quantidade_colunas != matrizBHeader->quantidade_colunas) {
        printf("A operação de subtração só é possível quando o numero de linhas e colunas das matrizes são iguais!\n");
        return;
    }
    int tamanho_linhas = matrizAHeader->quantidade_linhas;
    int tamanho_colunas = matrizAHeader->quantidade_colunas;
    Matriz_Esparsa *nodoA, *nodoB, *resultado;
    iniciar_matriz_esparsa(&resultado);
    int linha;
    for (linha = 0; linha < tamanho_linhas; linha++) {
        int coluna;
        for (coluna = 0; coluna < tamanho_colunas; coluna++) {
            nodoA = busca_por_posicao_matriz_esparsa(&(*matrizA), linha, coluna);
            float dadoA = 0;
            if (nodoA) dadoA = nodoA->dado;
            nodoB = busca_por_posicao_matriz_esparsa(&(*matrizB), linha, coluna);
            float dadoB = 0;
            if (nodoB) dadoB = nodoB->dado;
            float subtracao = dadoA - dadoB;
            insere_final_matriz(&resultado, subtracao, linha, coluna);
        }
    }
    imprimir_matriz_formatada(&resultado, tamanho_linhas, tamanho_colunas);
}
void multiplicar_matrizes(MatrizEsparsaHeader * matrizAHeader, MatrizEsparsaHeader * matrizBHeader) {
    Matriz_Esparsa **matrizA = &matrizAHeader->matriz;
    Matriz_Esparsa **matrizB = &matrizBHeader->matriz;
    if (*matrizA == NULL || *matrizB == NULL) return;
    if (matrizAHeader->quantidade_colunas != matrizBHeader->quantidade_linhas) {
        printf("A operação de multiplicação só é possível quando o numero de colunas da matriz A e o numero de linhas da matriz B são iguais!\n");
        return;
    }
    int tamanho_linhas = matrizAHeader->quantidade_linhas;
    int tamanho_colunas = matrizBHeader->quantidade_colunas;
    Matriz_Esparsa *nodoA, *nodoB, *resultado;
    iniciar_matriz_esparsa(&resultado);
    int linha;
    for (linha = 0; linha < tamanho_linhas; linha++) {
        int coluna;
        for (coluna = 0; coluna < tamanho_colunas; coluna++) {
            float soma = 0;
            int indice;
            for (indice = 0; indice < tamanho_linhas; indice++) {
                nodoA = busca_por_posicao_matriz_esparsa(&(*matrizA), linha, indice);
                float dadoA = 0;
                if (nodoA) dadoA = nodoA->dado;
                nodoB = busca_por_posicao_matriz_esparsa(&(*matrizB), indice, coluna);
                float dadoB = 0;
                if (nodoB) dadoB = nodoB->dado;
                soma += dadoA * dadoB;
            }
            insere_final_matriz(&resultado, soma, linha, coluna);
        }
    }
    imprimir_matriz_formatada(&resultado, tamanho_linhas, tamanho_colunas);
}

int main() {
    setbuf(stdout, 0);
    Matriz * matrizes;
    iniciar_lista_matrizes(&matrizes);

    int escolha = 1;
    while (escolha != 0) {
        printf("---- Menu ----\n");
        printf(" 0. Sair\n");
        printf(" 1. Adicionar matriz\n");
        printf(" 2. Somar matrizes\n");
        printf(" 3. Subtrair matrizes\n");
        printf(" 4. Multiplicar matrizes\n");
        printf(" 5. Imprimir matriz transposta\n");
        printf(" 6. Imprimir diagonal principal de matriz\n");
        printf(" 7. Imprimir matriz\n");
        scanf("%i", &escolha);
        switch (escolha) {
            case 0:
                libera_lista_matrizes(&matrizes);
                break;
            case 1:
                printf("-- Adicionar matriz --\n");
                Matriz_Esparsa * matrizEsparsa;
                iniciar_matriz_esparsa(&matrizEsparsa);
                int quantidadeLinhas, quantidadeColunas;
                printf("Digite o numero de linhas da matriz:\n");
                scanf("%i", &quantidadeLinhas);
                printf("Digite o numero de colunas da matriz:\n");
                scanf("%i", &quantidadeColunas);
                receber_matriz(&matrizEsparsa, quantidadeLinhas, quantidadeColunas);

                adicionar_matriz(&matrizes, &matrizEsparsa, quantidadeLinhas, quantidadeColunas);
                break;
            case 2:
                printf(" -- Soma de matrizes --\n");
                imprimir_matrizes(&matrizes);
                int indiceSomaA, indiceSomaB;

                printf("Digite o indice da primeira matriz:\n");
                scanf("%i", &indiceSomaA);
                printf("Digite o indice da segunda matriz:\n");
                scanf("%i", &indiceSomaB);
                Matriz * buscaSomaA;
                iniciar_lista_matrizes(&buscaSomaA);
                acessar_matriz(&matrizes, indiceSomaA, &buscaSomaA);
                Matriz * buscaSomaB;
                iniciar_lista_matrizes(&buscaSomaB);
                acessar_matriz(&matrizes, indiceSomaB, &buscaSomaB);

                soma_matrizes(&matrizes, buscaSomaA->matriz, buscaSomaB->matriz);
                break;
            case 3:
                printf(" -- Subtracao de matrizes --\n");
                imprimir_matrizes(&matrizes);
                int indiceSubtracaoA, indiceSubtracaoB;

                printf("Digite o indice da primeira matriz:\n");
                scanf("%i", &indiceSubtracaoA);

                printf("Digite o indice da segunda matriz:\n");
                scanf("%i", &indiceSubtracaoB);
                Matriz * buscaSubtracaoA;
                iniciar_lista_matrizes(&buscaSubtracaoA);
                acessar_matriz(&matrizes, indiceSubtracaoA, &buscaSubtracaoA);
                Matriz * buscaSubtracaoB;
                iniciar_lista_matrizes(&buscaSubtracaoB);
                acessar_matriz(&matrizes, indiceSubtracaoB, &buscaSubtracaoB);

                subtrair_matrizes(buscaSubtracaoA->matriz, buscaSubtracaoB->matriz);
                break;
            case 4:
                printf(" -- Multiplicacao de matrizes --\n");
                imprimir_matrizes(&matrizes);
                int indiceMultiplicacaoA, indiceMultiplicacaoB;

                printf("Digite o indice da primeira matriz:\n");
                scanf("%i", &indiceMultiplicacaoA);
                printf("Digite o indice da segunda matriz:\n");
                scanf("%i", &indiceMultiplicacaoB);
                Matriz * buscaMultiplicacaoA;
                iniciar_lista_matrizes(&buscaMultiplicacaoA);
                acessar_matriz(&matrizes, indiceMultiplicacaoA, &buscaMultiplicacaoA);
                Matriz * buscaMultiplicacaoB;
                iniciar_lista_matrizes(&buscaMultiplicacaoB);
                acessar_matriz(&matrizes, indiceMultiplicacaoB, &buscaMultiplicacaoB);

                multiplicar_matrizes(buscaMultiplicacaoA->matriz, buscaMultiplicacaoB->matriz);
                break;
            case 5:
                printf(" -- Matriz transposta --\n");
                imprimir_matrizes(&matrizes);
                int indiceTranspostaA;

                printf("Digite o indice da matriz:\n");
                scanf("%i", &indiceTranspostaA);

                Matriz * buscaTransposta;
                iniciar_lista_matrizes(&buscaTransposta);
                acessar_matriz(&matrizes, indiceTranspostaA, &buscaTransposta);

                imprimir_matriz_transposta(&buscaTransposta->matriz->matriz, buscaTransposta->matriz->quantidade_linhas, buscaTransposta->matriz->quantidade_colunas);
                break;
            case 6:
                printf(" -- Diagonal principal da matriz --\n");
                imprimir_matrizes(&matrizes);
                int indiceDiagonalPrincipal;

                printf("Digite o indice da matriz:\n");
                scanf("%i", &indiceDiagonalPrincipal);

                Matriz * buscaDiagonalPrincipal;
                iniciar_lista_matrizes(&buscaDiagonalPrincipal);
                acessar_matriz(&matrizes, indiceDiagonalPrincipal, &buscaDiagonalPrincipal);

                imprimir_diagonal_principal(&buscaDiagonalPrincipal->matriz->matriz, buscaDiagonalPrincipal->matriz->quantidade_linhas, buscaDiagonalPrincipal->matriz->quantidade_colunas);
                break;
            case 7:
                printf(" -- Imprimir matriz --\n");
                imprimir_matrizes(&matrizes);
                int indiceImprimir;

                printf("Digite o indice da matriz:\n");
                scanf("%i", &indiceImprimir);

                Matriz * buscaImprimir;
                iniciar_lista_matrizes(&buscaImprimir);
                acessar_matriz(&matrizes, indiceImprimir, &buscaImprimir);

                imprimir_matriz_formatada(&buscaImprimir->matriz->matriz, buscaImprimir->matriz->quantidade_linhas, buscaImprimir->matriz->quantidade_colunas);
                break;
            default:
                printf("Opção inválida!\n");
                break;
        }
    }
}
