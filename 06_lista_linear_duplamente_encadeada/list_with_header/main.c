#include <stdio.h>

typedef struct node {
    int data;
    struct node *previous, *next;
} Node;

typedef struct header {
    int total_elements;
    Node *begin, *end;
} Header;

void initialize_list(Header * list) {
    list->total_elements = 0;
    list->begin = NULL;
    list->end = NULL;
}

Node * create_node() {
    Node *node;
    node = (Node*) malloc(sizeof(Node));
    if (!node) {
        printf("Error on create node");
        exit(0);
    }
    return node;
}

void insert_begin(Header * list, int data) {
    Node * node;
    node = create_node();
    node->data = data;
    node->previous = NULL;
    node->next = list->begin;
    if (list->begin != NULL) 
        list->begin->previous = node;
    list->begin = node;
    list->total_elements += 1;
    if (list->end == NULL)
        list->end = node; 
}

void insert_end(Header * list, int data) {
    Node * node;
    node = create_node();
    node->data = data;
    node->next = NULL;
    node->previous = list->end;
    if (list->end != NULL)
        list->end->next = node;
    list->end = node;
    list->total_elements += 1;
    if (list->begin == NULL)
        list->begin = node;
}

void remove_begin(Header * list) {
    if (list == NULL) {
        printf("Lista vazia");
        exit(0);
    }
    Node * aux = list->begin;
    list->begin = list->begin->next;
    list->begin->previous = NULL;
    list->total_elements -= 1;
    free(aux);
}

void remove_end(Header * list) {
    if (list == NULL) {
        printf("Lista vazia");
        exit(0);
    }
    Node * aux = list->end;
    list->end = list->end->previous;
    list->end->next = NULL;
    list->total_elements -= 1;
    free(aux);
}

void print_list(Header * list) {
    if (!list || list == NULL || list->total_elements == 0) {
        printf("lista vazia");
        exit(0);
    }

    Node * current;
    current = list->begin;

    while (current != NULL) {
        printf("Data: %i\n", current->data);
        current = current->next;
    }
}

void apaga_lista(Header * list) {
    Node * current;
    current = list->begin;
    int count = 0;
    while (count < list->total_elements) {
        Node *aux = current;
        printf("liberando item %i\n", current->data);
        free(current->data);
        current = aux;
        free(aux);
        count--;
    }
    free(current);
    free(list);
}

int main() {
    Header list;
    initialize_list(&list);


    // insert_begin(&list, 10);
    // insert_begin(&list, 20);
    // insert_begin(&list, 3);

    insert_end(&list, 10);
    insert_end(&list, 20);
    insert_end(&list, 30);

    print_list(&list);

    // remove_begin(&list);
    // remove_begin(&list);
    // remove_begin(&list);
    // remove_begin(&list);
    // remove_end(&list);
    printf("---------------\n");

    print_list(&list);

    apaga_lista(&list);

    return 1;
}

/*
*/
