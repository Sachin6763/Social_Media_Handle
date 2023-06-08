typedef struct heap
{
    int **arr;
    int size;
    int rare;
} heap;

void initHeap(heap **pq, int size);
void insertHeap(heap **pq, int id, int data);
int removeHeap(heap **pq);
int topHeap(heap *pq);