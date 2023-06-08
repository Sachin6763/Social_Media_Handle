#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void Qinit(Queue **q)
{
    (*q)->front = NULL;
    (*q)->rare = NULL;
    return;
}

void enqueue(Queue **pq, int val)
{
    Queue *q = (*pq);
    Qnode *temp = (Qnode *)malloc(sizeof(Qnode));
    temp->data = val;
    temp->next = NULL;

    if (q->rare == NULL)
    {
        q->rare = temp;
        q->front = temp;
        return;
    }

    q->rare->next = temp;
    q->rare = temp;

    return;
}

int dequeue(Queue **pq)
{
    Queue *q = (*pq);
    if (q->front == NULL)
        return INT_MIN;
    int temp = q->front->data;
    Qnode *deleted = q->front;
    q->front = q->front->next;
    if (q->front == NULL)
    {
        q->rare = NULL;
    }
    free(deleted);
    return temp;
}

int QisEmpty(Queue q)
{
    return q.front == NULL || q.rare == NULL;
}