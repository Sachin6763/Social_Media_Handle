typedef struct Qnode
{
    int data;
    struct Qnode *next;
} Qnode;

typedef struct Queue
{
    Qnode *rare;
    Qnode *front;
    int size;
} Queue;

void Qinit(Queue **q);
void enqueue(Queue **q, int data);
int dequeue(Queue **q);
int QisEmpty(Queue q);