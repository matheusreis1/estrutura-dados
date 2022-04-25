#include <stdio.h>
#include <stdlib.h>

typedef struct stack_node {
    int data;
    struct stack_node *next;
} StackNode;

typedef StackNode * Stack;

StackNode * initialize_node() {
    StackNode *node = (StackNode*) malloc(sizeof(StackNode));
    if (!node) exit(0);
    return node;
}

Stack * initialize_stack() {
    Stack *stack = (Stack*) malloc(sizeof(Stack));
    if (!stack) exit(0);
    return stack;
}

int destroy_stack(Stack *stack) {
    if (stack == NULL) return 0;
    StackNode *current;
    while ((*stack) != NULL) {
        current = *stack;
        *stack = (*stack)->next;
        free(current);
    }
    free(stack);
    return 1;
}

int insert_stack(Stack *stack, int data) {
    // always on begin
    StackNode *node = initialize_node();
    node->data = data;
    node->next = (*stack);
    *stack = node;
    return 1;
}

int remove_stack(Stack *stack) {
    // always on begin
    if (stack == NULL || (*stack) == NULL) return 0;
    StackNode *node = *stack;
    *stack = node->next;
    free(node);
    return 1;
}

int main() {
    Stack *stack = initialize_stack();

    insert_stack(stack, 1);
    insert_stack(stack, 2);
    insert_stack(stack, 3);
    insert_stack(stack, 4);

    remove_stack(stack);

    printf("Hello World!");
}

/*
*/
