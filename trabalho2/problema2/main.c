#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STRING_LIMIT 64

typedef struct queue_node {
    char name[MAX_STRING_LIMIT];
    char phone[MAX_STRING_LIMIT];
    int urgency;
    struct queue_node *next;
} QueueNode;

typedef struct queue_header {
    QueueNode *start;
    QueueNode *finish;
    int size;
} Queue;

QueueNode * initialize_node() {
    QueueNode *node = (QueueNode*) malloc(sizeof(QueueNode));
    if(!node) exit(0);
    return node;
}

Queue* initialize_queue() {
    Queue *queue = (Queue*) malloc(sizeof(Queue));
    if(!queue) exit(0);
    queue->start = NULL;
    queue->finish = NULL;
    queue->size = 0;
    return queue;
}

void destroy_queue(Queue * queue) {
    if (queue != NULL) {
        QueueNode *node;
        while (queue->start != NULL) {
            node = queue->start;
            queue->start = queue->start->next;
            free(node);
        }
        free(queue);
    }
}

int insert_node(Queue *queue, char name[], char phone[], int urgency) {
    if(queue == NULL) return 0;
    QueueNode *node = initialize_node();
    strcpy(node->name, name);
    strcpy(node->phone, phone);
    node->urgency = urgency;
    node->next = NULL;

    if (queue->finish == NULL) {  // empty queue
        queue->start = node;
        queue->finish = node;
    } else { // insert in order
        QueueNode *previous, *current = queue->start;
        while (current != NULL && current->urgency >= node->urgency) {
            previous = current;
            current = current->next;
        }
        if (current == queue->start) {
            node->next = queue->start;
            queue->start = node;
        } else {
            node->next = previous->next;
            previous->next = node;
            queue->finish = node;
        }
    }

    queue->size++;
    return 1;
}

int remove_node(Queue *queue) {
    if (queue == NULL || queue->start == NULL) return 0;
    QueueNode *actual = queue->start;
    queue->start = queue->start->next;
    if (queue->start == NULL) // queue got empty
        queue->finish = NULL;
    free(actual);
    queue->size--;
    return 1;
}

int get_node(Queue *queue, QueueNode **search) {
    if (queue == NULL || queue->start == NULL) return 0;
    *search = queue->start;
    return 1;
}

int search_node_by_name(Queue *queue, char name[]) {
    if (queue == NULL || queue->start == NULL) return 0;
    QueueNode *current = queue->start;
    int count;
    for (count = 1; current != NULL && strcmp(current->name, name) != 0; count++) {
        current = current->next;
    }
    if (!current) return 0;

    printf("Paciente: %s\n", current->name);
    printf("Posicao na fila: %i\n", count);
    printf("Grau de urgencia: %i\n", current->urgency);

    return 1;
}

int save_text(QueueNode *node) {
    printf("Salvando paciente %s no relatorio...\n", node->name);
}

int main() {
    Queue *queue = initialize_queue();

    int menu_choice = 0;
    while (menu_choice != 5) {
        printf("--- Menu ---\n");
        printf(" 1. Cadastrar paciente\n");
        printf(" 2. Buscar paciente\n");
        printf(" 3. Proximo paciente a ser operado\n");
        printf(" 4. Verificar tamanho da fila\n");
        printf(" 5. Sair\n");

        scanf("%i", &menu_choice);
        switch (menu_choice) {
            case 1:
                printf("Digite o nome do paciente:\n");
                char name[MAX_STRING_LIMIT];
                scanf(" %[^\n]%*c", name);
                printf("Digite o telefone do paciente:\n");
                char phone[MAX_STRING_LIMIT];
                scanf(" %[^\n]%*c", phone);
                printf("Digite o grau de urgencia (1 a 5):\n");
                int urgency;
                scanf("%i", &urgency);
                insert_node(queue, name, phone, urgency);
                break;
            case 2:
                printf("busca de paciente\n");
                printf("Digite o nome do paciente a ser procurado:\n");
                char name_search[MAX_STRING_LIMIT];
                scanf(" %[^\n]%*c", name_search);

                search_node_by_name(queue, name_search);
                break;
            case 3:
                printf("");
                QueueNode *search = NULL;
                get_node(queue, &search);
                if (!search) {
                    printf("A lista de pacientes está vazia!\n");
                } else {
                    printf("O proximo paciente a ser operado é: %s\n", search->name);
                    // send search struct to txt file
                    save_text(search);
                    // call delete node
                    remove_node(queue);
                }
                break;
            case 4:
                printf("O tamanho atual da fila é de: %i\n", queue->size);
                break;
            case 5:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida, digite novamente\n");
                break;
        }
    }
    return 0;
}
