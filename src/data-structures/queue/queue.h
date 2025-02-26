#ifndef QUEUE_H
typedef struct QNode
{
    void *element;
    struct QNode *next;
    struct QNode *prev;

} QNODE;

typedef struct Queue
{
    QNODE *front;
    QNODE *rear;
} QUEUE;

QUEUE *createQueue();

void enqueue(QUEUE *queue, void *ele);

void *dequeue(QUEUE *queue);

char isEmptyQueue(QUEUE *queue);

void *peekQueue(QUEUE *queue);

void freeQueue(QUEUE *queue);

#endif