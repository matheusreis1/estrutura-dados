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

// criar lista de matrizes
void iniciar_lista_matrizes(Matriz ** matrizes) {
    *matrizes = NULL;
}
void iniciar_matriz_esparsa(Matriz_Esparsa ** matriz) {
    *matriz = NULL;
}
// adicionar matriz nova no final
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
    if ((*matrizes) != NULL)
        indice = (*matrizes)->matriz->indice + 1;
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
        auxiliar->proximo = matriz;
    }
}

// procurar matriz
void imprimir_matriz(Matriz * matriz) {
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
            imprimir_matriz(atual);
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
Matriz_Esparsa * busca_por_posicao_matriz_esparsa(Matriz_Esparsa ** matriz, int lin, int col) {
    Matriz_Esparsa *nodo = *matriz;
    while (nodo != NULL) {
        if (nodo->lin == lin && nodo->col == col) return nodo;
        nodo = nodo->proximo;
    }
    return NULL;
}
void imprime_matriz(Matriz_Esparsa ** matrizEsparsa, int tamanho_linhas, int tamanho_colunas) {
    if (*matrizEsparsa == NULL) return;
    Matriz_Esparsa *nodo;
    int linha;
    for (linha = 0; linha < tamanho_linhas; linha++) {
        int coluna;
        for (coluna = 0; coluna < tamanho_colunas; coluna++) {
            nodo = busca_por_posicao_matriz_esparsa(&(*matrizEsparsa), linha, coluna);
            float dado = 0;
            if (nodo) dado = nodo->dado;
            printf("%.2f  ", dado);
        }
        printf("\n");
    }
}
void imprime_diagonal_principal(Matriz_Esparsa ** matriz, int tamanho_linhas, int tamanho_colunas) {
    if (*matriz == NULL) return;
    Matriz_Esparsa *nodo;
    printf("Diagonal principal: \n");
    int linha;
    for (linha = 0; linha < tamanho_linhas; linha++) {
        int coluna;
        for (coluna = 0; coluna < tamanho_colunas; coluna++) {
            if (linha != coluna) continue;
            nodo = busca_por_posicao_matriz_esparsa(&(*matriz), linha, coluna);
            float dado = 0;
            if (nodo) dado = nodo->dado;
            printf("%.2f ", dado);
        }
    }
}
void imprime_matriz_transposta(Matriz_Esparsa ** matriz, int tamanho_linhas, int tamanho_colunas) {
    if (*matriz == NULL) return;
    Matriz_Esparsa *nodo, *transposta;
    iniciar_matriz_esparsa(&transposta);
    printf("Matriz transposta: \n");
    int linha;
    for (linha = 0; linha < tamanho_linhas; linha++) {
        int coluna;
        for (coluna = 0; coluna < tamanho_colunas; coluna++) {
            nodo = busca_por_posicao_matriz_esparsa(&(*matriz), linha, coluna);
            float dado = 0;
            if (nodo) dado = nodo->dado;
            // o numero de colunas é o contrario ao de linhas
            insere_final_matriz(&transposta, dado, coluna, linha);
        }
    }
    // o numero de colunas é o contrario ao de linhas
    imprime_matriz(&transposta, tamanho_colunas, tamanho_linhas);
}

// operacoes
void soma_matrizes(Matriz_Esparsa ** matrizA, Matriz_Esparsa ** matrizB, int tamanho_linhas, int tamanho_colunas) {
    if (*matrizA == NULL || *matrizB == NULL) return;
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
    imprime_matriz(&resultado, tamanho_linhas, tamanho_colunas);
}
void subtrair_matrizes(Matriz_Esparsa ** matrizA, Matriz_Esparsa ** matrizB, int tamanho_linhas, int tamanho_colunas) {
    if (*matrizA == NULL || *matrizB == NULL) return;
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
    imprime_matriz(&resultado, tamanho_linhas, tamanho_colunas);
}
void multiplicar_matrizes(Matriz_Esparsa ** matrizA, Matriz_Esparsa ** matrizB, int tamanho_linhasA, int tamanho_colunasB) {
    if (*matrizA == NULL || *matrizB == NULL) return;
    Matriz_Esparsa *nodoA, *nodoB, *resultado;
    iniciar_matriz_esparsa(&resultado);
    int linha;
    for (linha = 0; linha < tamanho_linhasA; linha++) {
        int coluna;
        for (coluna = 0; coluna < tamanho_colunasB; coluna++) {
            float soma = 0;
            int indice;
            for (indice = 0; indice < tamanho_linhasA; indice++) {
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
    imprime_matriz(&resultado, tamanho_linhasA, tamanho_colunasB);
}

int main() {
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

                if ((buscaSomaA->matriz->quantidade_linhas == buscaSomaB->matriz->quantidade_linhas) && (buscaSomaA->matriz->quantidade_colunas == buscaSomaB->matriz->quantidade_colunas)) {
                    soma_matrizes(&buscaSomaA->matriz->matriz, &buscaSomaB->matriz->matriz, buscaSomaA->matriz->quantidade_linhas, buscaSomaA->matriz->quantidade_colunas);
                } else {
                    printf("So pode somar matrizes com numeros de linha e colunas iguais\n");
                }
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

                if ((buscaSubtracaoA->matriz->quantidade_linhas == buscaSubtracaoB->matriz->quantidade_linhas) && (buscaSubtracaoA->matriz->quantidade_colunas == buscaSubtracaoB->matriz->quantidade_colunas)) {
                    soma_matrizes(&buscaSubtracaoA->matriz->matriz, &buscaSubtracaoB->matriz->matriz, buscaSubtracaoA->matriz->quantidade_linhas, buscaSubtracaoA->matriz->quantidade_colunas);
                } else {
                    printf("So pode subtrair matrizes com numeros de linha e colunas iguais\n");
                }
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

                if (buscaMultiplicacaoA->matriz->quantidade_colunas == buscaMultiplicacaoB->matriz->quantidade_linhas) {
                    multiplicar_matrizes(&buscaMultiplicacaoA->matriz->matriz, &buscaMultiplicacaoB->matriz->matriz, buscaMultiplicacaoA->matriz->quantidade_linhas, buscaMultiplicacaoB->matriz->quantidade_colunas);
                } else {
                    printf("So se pode multiplicar matrizes quando o numero de colunas da primeira for igual ao numero de linhas da segunda\n");
                }
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

                imprime_matriz_transposta(&buscaTransposta->matriz->matriz, buscaTransposta->matriz->quantidade_linhas, buscaTransposta->matriz->quantidade_colunas);
                break;
            case 6:
                printf(" -- Diagonal principal da matriz --\n");
                imprimir_matrizes(&matrizes);
                int indiceA;

                printf("Digite o indice da matriz:\n");
                scanf("%i", &indiceTranspostaA);

                Matriz * buscaDiagonalPrincipal;
                iniciar_lista_matrizes(&buscaDiagonalPrincipal);
                acessar_matriz(&matrizes, indiceTranspostaA, &buscaDiagonalPrincipal);

                imprime_diagonal_principal(&buscaDiagonalPrincipal->matriz->matriz, buscaDiagonalPrincipal->matriz->quantidade_linhas, buscaDiagonalPrincipal->matriz->quantidade_colunas);
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

                imprime_matriz(&buscaImprimir->matriz->matriz, buscaImprimir->matriz->quantidade_linhas, buscaImprimir->matriz->quantidade_colunas);
                break;
            default:
                printf("Opção inválida!\n");
                break;

        }
    }
}
