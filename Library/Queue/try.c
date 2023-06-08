#include "queue.h"
#include <stdio.h>

int main()
{

    Queue q;
    Queue *qp = &q;
    Qinit(qp);
    enqueue(qp, 10);
    enqueue(qp, 07);
    enqueue(qp, 30);
    enqueue(qp, 40);
    enqueue(qp, 50);
    enqueue(qp, 60);
    enqueue(qp, 10);
    printf("%d\n", dequeue(qp));
    printf("%d\n", dequeue(qp));
    printf("%d\n", dequeue(qp));
    printf("%d\n", dequeue(qp));
    printf("%d\n", dequeue(qp));
    printf("%d\n", dequeue(qp));
    printf("%d\n", dequeue(qp));
    printf("%d\n", dequeue(qp));
    printf("%d\n", dequeue(qp));
    printf("%d\n", dequeue(qp));
    printf("%d\n", dequeue(qp));
    printf("%d\n", dequeue(qp));
    printf("%d\n", dequeue(qp));

    return 0;
}