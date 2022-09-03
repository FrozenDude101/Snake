#include <stdlib.h>


typedef struct Queue Queue;
typedef struct Node Node;


struct Queue {

    Node* head;
    Node* tail;

};

struct Node {

    int x;
    int y;
    Node* next;

};


Queue* newQueue();
void freeQueue(Queue* queue);
void printQueue(Queue* queue);

Node* newNode(int x, int y);
void freeNode(Node* node);
void printNode(Node* node);

void enqueue(Queue* queue, int x, int y);
void dequeue(Queue* queue);

int queueLength(Queue* queue);

int* getQueueData(Queue* queue);
void freeQueueData(int* data);

Queue* newQueue() {

    Queue * queue = (Queue*) malloc(sizeof(Queue));

    queue -> head = NULL;
    queue -> tail = NULL;

    return queue;

}
void freeQueue(Queue* queue) {

    if (queue -> head) {

        Node* node = queue -> head;
        Node* nextNode;
        do {
            nextNode = node -> next;
            freeNode(node);
            node = nextNode;
        } while (node != NULL);
        
    }

    free(queue);

}
void printQueue(Queue* queue) {

    if (queue -> head == NULL) {

        printf("<Empty>\n");

    } else {

        Node* node = queue -> head;
        do {
            printf("(%d, %d) -> ", node -> x, node -> y);
            node = node -> next;
        } while (node != NULL);

        printf("NULL\n");

    }

}

Node* newNode(int x, int y) {

    Node* node = malloc(sizeof(Node));

    node -> x = x;
    node -> y = y;
    node -> next = NULL;

    return node;

}
void freeNode(Node* node) {

    free(node);
    
}
void printNode(Node* node) {

    printf("(%d, %d)", node -> x, node -> y);

}

void enqueue(Queue* queue, int x, int y) {

    if (queue -> head == NULL) {

        queue -> head = newNode(x, y);
        queue -> tail = queue -> head;

    } else {

        queue -> tail -> next = newNode(x, y);
        queue -> tail = queue -> tail -> next;

    }

}
void dequeue(Queue* queue) {

    if (queue -> head == NULL) return;

    Node* head = queue -> head;
    queue -> head = queue -> head -> next;
    freeNode(head);

}
void enqueueToEnd(Queue* queue, int x, int y) {

    Node* node = newNode(x, y);
    node -> next = queue -> head;
    queue -> head = node;

}

int queueLength(Queue* queue) {

    if (queue -> head == NULL) return 0;
    
    Node* node = queue -> head;
    int length = 0;

    do {
        length++;
        node = node -> next;
    } while (node != NULL);

    return length;

}

int* getQueueData(Queue* queue) {

    int* data = malloc(sizeof(int) * queueLength(queue) * 2);

    if (queue -> head == NULL) return data;

    Node* node = queue -> head;
    int i = 0;

    do {
        data[i * 2] = node -> x;
        data[i * 2 + 1] = node -> y;
        i ++;
        node = node -> next;
    } while (node != NULL);

    return data;

}
void freeQueueData(int* data) {

    free(data);

}