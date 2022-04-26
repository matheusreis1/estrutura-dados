#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define RATO_CHAR 1
#define LIVRE_CHAR 32
#define PAREDE_CHAR 219
#define BECO_CHAR 176
#define VISITADA_CHAR 56
#define RATO -1
#define LIVRE 0
#define PAREDE 1
#define BECO 3
#define VISITADA 4
#define LINHAS 5
#define COLUNAS 5

typedef struct solution_node {
    int position;
    struct solution_node *next;
} SolutionNode;
typedef SolutionNode *Solution;

SolutionNode * initialize_node() {
    SolutionNode *node = (SolutionNode*) malloc(sizeof(SolutionNode));
    if (!node) exit(0);
    return node;
}

Solution * initialize_stack() {
    Solution *stack = (Solution*) malloc(sizeof(Solution));
    if (stack != NULL)
        *stack = NULL;
    return stack;
}

int destroy_stack(Solution *stack) {
    if (stack == NULL) return 0;
    SolutionNode *current;
    while ((*stack) != NULL) {
        current = *stack;
        *stack = (*stack)->next;
        free(current);
    }
    free(stack);
    return 1;
}

int insert_stack(Solution *stack, int x, int y) {
    // always on begin
    SolutionNode *node = initialize_node();

    // calculate
    int data = x * 100 + y;

    node->position = data;
    node->next = *stack;
    *stack = node;

    return 1;
}

int search_stack(Solution *stack, int *x, int *y) {
    if(stack == NULL || (*stack) == NULL) return 0;
    *x = (*stack)->position / 100;
    *y = (*stack)->position % 100;
    return 1;
}

int remove_stack(Solution *stack) {
    if (stack == NULL || (*stack) == NULL) return 0;
    SolutionNode *node = *stack;
    *stack = node->next;
    free(node);
    return 1;
}

int random_in_range(int min, int max) {
    return min + (int) (rand() / (double) (RAND_MAX + 1) * (max - min + 1));
}

void print_maze(int (*maze)[LINHAS][COLUNAS]) {
    int i, j;
    for (i = 0; i < LINHAS; i++) {
        for (j = 0; j < COLUNAS; j++) {
            int posicao = (*maze)[i][j];
            char print = LIVRE_CHAR;
            switch (posicao) {
                case LIVRE:
                    print = LIVRE_CHAR;
                    break;
                case PAREDE:
                    print = PAREDE_CHAR;
                    break;
                case BECO:
                    print = BECO_CHAR;
                    break;
                case VISITADA:
                    print = VISITADA_CHAR;
                    break;
                case RATO:
                    print = RATO_CHAR;
                    break;
            }
            printf(" %c ", print);
        }
        printf("\n");
    }
}

void init_maze(int (*maze)[LINHAS][COLUNAS], int initial_mouse_x, int initial_mouse_y, int final_x, int final_y) {
    int i, j;
    for (i = 0; i < LINHAS; i++)
        for (j = 0; j < COLUNAS; j++) {
            int number = random_in_range(LIVRE, PAREDE);
            if (i == 0 || j == 0 || i == COLUNAS - 1 || j == COLUNAS - 1) number = PAREDE; // fill matrix boundary
            if (i == initial_mouse_x && j == initial_mouse_y) number = RATO;
            if (i == final_x && j == final_y) number = LIVRE;
            (*maze)[i][j] = number;
        }
}

int main() {
    setbuf(stdout, 0);
    srand(time(0));

    int (*maze)[LINHAS][COLUNAS] = malloc(sizeof *maze);
    int initial_mouse_x = 1;
    int initial_mouse_y = 1;
    int final_x = random_in_range(0, LINHAS - 1);
    int final_y = random_in_range(0, LINHAS - 1);

    init_maze(&(*maze), initial_mouse_x, initial_mouse_y, final_x, final_y);

    int linha = initial_mouse_x;
    int coluna = initial_mouse_y;
    Solution *solution = initialize_stack();

    do {
        (*maze)[linha][coluna] = VISITADA;
        if (linha == final_x && coluna == final_y) {
            // reached the final
            break;
        }

        int right = (*maze)[linha][coluna + 1];
        int left = (*maze)[linha][coluna - 1];
        int up = (*maze)[linha - 1][coluna];
        int down = (*maze)[linha + 1][coluna];

        if (linha == initial_mouse_x && coluna == initial_mouse_y) {
            // is in mouse initial position
            if (right == LIVRE) {
                insert_stack(solution, linha, coluna);
                coluna++;
                continue;
            } else if (left == LIVRE) {
                insert_stack(solution, linha, coluna);
                coluna--;

                continue;
            } else if (up == LIVRE) {
                insert_stack(solution, linha, coluna);
                linha--;

                continue;
            } else if (down == LIVRE) {
                insert_stack(solution, linha, coluna);
                linha++;

                continue;
            } else {
                // cant move, finish program
                *solution = NULL;
                break;
            }
        } else {
            if (right == LIVRE) {
                insert_stack(solution, linha, coluna);
                coluna++;

                continue;
            } else if (left == LIVRE) {
                insert_stack(solution, linha, coluna);
                coluna--;

                continue;
            } else if (up == LIVRE) {
                insert_stack(solution, linha, coluna);
                linha--;

                continue;
            } else if (down == LIVRE) {
                insert_stack(solution, linha, coluna);
                linha++;

                continue;
            } else {
                // cant move, remove from stack
                (*maze)[linha][coluna] = BECO;
                search_stack(solution, &linha, &coluna);
                remove_stack(solution);

                continue;
            }
        }
    } while (linha < LINHAS && coluna < COLUNAS);

    printf("-- Comeco: (%d,%d) --\n", initial_mouse_x, initial_mouse_y);
    printf("-- Saida: (%d,%d) --\n", final_x, final_y);
    if (*solution == NULL) {
        printf("Nao foi possivel achar uma saida!\n");
    }
    print_maze(&(*maze));

    destroy_stack(solution);

    return 0;
}
