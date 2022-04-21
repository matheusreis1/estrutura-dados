#include <stdio.h>
#include <stdlib.h>

typedef struct queue_node {
    int data;
    struct queue_node *next;
} QueueNode;

typedef struct queue_header {
    QueueNode *start;
    QueueNode *finish;
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

int insert_node(Queue *queue, int data) {
    if(queue == NULL) return 0;
    QueueNode *node = initialize_node();
    node->data = data;
    node->next = NULL;
    if (queue->finish == NULL) // empty queue
        queue->start = node;
    else
        queue->finish->next = node;
    queue->finish = node;
    return 1;
}

int remove_node(Queue *queue) {
    if (queue == NULL || queue->start == NULL) return 0;
    QueueNode *previous_start = queue->start;
    queue->start = queue->start->next;
    if (queue->start == NULL) // queue got empty
        queue->finish = NULL;
    free(previous_start);
    return 1;
}

int get_node(Queue *queue, QueueNode **search) {
    if (queue == NULL || queue->start == NULL) return 0;
    *search = queue->start;
    printf("Node: %i\n", (*search)->data);
    return 1;
}

int main() {
    Queue *queue = initialize_queue();

    insert_node(queue, 1);
    insert_node(queue, 2);
    insert_node(queue, 3);
    remove_node(queue);

    QueueNode *search;
    get_node(queue, &search);

    return 0;
}
