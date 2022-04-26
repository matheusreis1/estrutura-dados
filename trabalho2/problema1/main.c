#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define RATO_CHAR 1
#define LIVRE_CHAR 32
#define PAREDE_CHAR 219
#define BECO_CHAR 176
#define VISITADA_CHAR 46
#define RATO -1
#define LIVRE 0
#define PAREDE 1
#define BECO 3
#define VISITADA 4
#define MATRIX_SIZE 5 // number of rows and columns

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

int insert_stack(Solution *stack, int row, int column) {
    SolutionNode *node = initialize_node();
    int data = row * 100 + column;
    node->position = data;
    node->next = *stack;
    *stack = node;
    return 1;
}

int search_stack(Solution *stack, int *row, int *column) {
    if(stack == NULL || (*stack) == NULL) return 0;
    *row = (*stack)->position / 100;
    *column = (*stack)->position % 100;
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

void print_maze(int (*maze)[MATRIX_SIZE][MATRIX_SIZE]) {
    int row, column;
    for (row = 0; row < MATRIX_SIZE; row++) {
        for (column = 0; column < MATRIX_SIZE; column++) {
            int current_position_value = (*maze)[row][column];
            char current_position_char = LIVRE_CHAR;
            switch (current_position_value) {
                case LIVRE:
                    current_position_char = LIVRE_CHAR;
                    break;
                case PAREDE:
                    current_position_char = PAREDE_CHAR;
                    break;
                case BECO:
                    current_position_char = BECO_CHAR;
                    break;
                case VISITADA:
                    current_position_char = VISITADA_CHAR;
                    break;
                case RATO:
                    current_position_char = RATO_CHAR;
                    break;
            }
            printf(" %c ", current_position_char);
        }
        printf("\n");
    }
}

void init_maze(int (*maze)[MATRIX_SIZE][MATRIX_SIZE], int initial_mouse_row, int initial_mouse_column, int final_position_row, int final_position_column) {
    int i, j;
    for (i = 0; i < MATRIX_SIZE; i++)
        for (j = 0; j < MATRIX_SIZE; j++) {
            int number = random_in_range(LIVRE, PAREDE);
            if (i == 0 || j == 0 || i == MATRIX_SIZE - 1 || j == MATRIX_SIZE - 1) number = PAREDE; // fill matrix boundary
            if (i == initial_mouse_row && j == initial_mouse_column) number = RATO;
            if (i == final_position_row && j == final_position_column) number = LIVRE;
            (*maze)[i][j] = number;
        }
}

int main() {
    setbuf(stdout, 0);
    srand(time(0));

    int (*maze)[MATRIX_SIZE][MATRIX_SIZE] = malloc(sizeof *maze);
    int initial_mouse_x = random_in_range(0, MATRIX_SIZE - 1);
    int initial_mouse_y = random_in_range(0, MATRIX_SIZE - 1);
    int final_x = random_in_range(0, MATRIX_SIZE - 1);
    int final_y = random_in_range(0, MATRIX_SIZE - 1);

    init_maze(&(*maze), initial_mouse_x, initial_mouse_y, final_x, final_y);

    int row = initial_mouse_x;
    int column = initial_mouse_y;
    Solution *solution = initialize_stack();
    int found_exit = 0;

    do {
        (*maze)[row][column] = VISITADA;
        if (row == final_x && column == final_y) {
            found_exit = 1;
            break;
        }

        int right = (*maze)[row][column + 1];
        int left = (*maze)[row][column - 1];
        int up = (*maze)[row - 1][column];
        int down = (*maze)[row + 1][column];

        if (right == LIVRE) {
            insert_stack(solution, row, column);
            column++;
            continue;
        } else if (left == LIVRE) {
            insert_stack(solution, row, column);
            column--;
            continue;
        } else if (up == LIVRE) {
            insert_stack(solution, row, column);
            row--;
            continue;
        } else if (down == LIVRE) {
            insert_stack(solution, row, column);
            row++;
            continue;
        } else {
            if (row == initial_mouse_x && column == initial_mouse_y) {
                // cant move, finish program
                *solution = NULL;
                break;
            } else {
                // cant move, remove from stack
                (*maze)[row][column] = BECO;
                search_stack(solution, &row, &column);
                remove_stack(solution);
                continue;
            }
        }
    } while (row < MATRIX_SIZE && column < MATRIX_SIZE);

    printf("-- Comeco: (%d,%d) --\n", initial_mouse_x, initial_mouse_y);
    printf("-- Saida: (%d,%d) --\n", final_x, final_y);
    if (!found_exit) {
        printf("Nao foi possivel achar uma saida!\n");
    }
    print_maze(&(*maze));

    destroy_stack(solution);

    return 0;
}
