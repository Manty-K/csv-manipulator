#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

QUEUE *createQueue()
{
    QUEUE *queue = malloc(sizeof(QUEUE));
    if (queue == NULL)
    {
        fprintf(stderr, "Queue allocation failed\n");
        return NULL;
    }
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

void enqueue(QUEUE *q, void *ele)
{
    QNODE *node = malloc(sizeof(QNODE));

    if (node == NULL)
    {
        fprintf(stderr, "QNODE allocation failed\n");
        return;
    }

    node->element = ele;
    node->next = NULL;
    node->prev = NULL;

    if (isEmptyQueue(q))
    {
        q->front = node;
        q->rear = node;
    }
    else
    {
        q->rear->next = node;
        node->prev = q->rear;
        q->rear = node;
    }
}

void *dequeue(QUEUE *q)
{
    if (isEmptyQueue(q))
    {
        fprintf(stderr, "Cannot deque : Queue Empty\n");
        return NULL;
    }

    void *val = peekQueue(q);

    QNODE *temp = q->front;
    q->front = q->front->next;

    if (q->front == NULL)
    {
        q->rear = NULL;
    }
    else
    {
        q->front->prev = NULL;
    }

    free(temp);

    return val;
}

char isEmptyQueue(QUEUE *q)
{
    return q->front == NULL;
}

void *peekQueue(QUEUE *q)
{
    if (isEmptyQueue(q))
    {
        fprintf(stderr, "Cannot peekQueue : Queue Empty\n");
        return NULL;
    }

    return q->front->element;
}

void freeQueue(QUEUE *q)
{
    if (q == NULL)
        return;

    while (!isEmptyQueue(q))
    {
        dequeue(q);
    }

    free(q);
}
