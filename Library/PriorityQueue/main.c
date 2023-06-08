#include <stdio.h>
#include "Heaps.h"

int main()
{

    heap pq;
    heap *h = &pq;
    initHeap(&h, 10);
    // printf("Errpr");
    insertHeap(&h, 0, 10);
    insertHeap(&h, 1, 20);
    insertHeap(&h, 2, 0);
    insertHeap(&h, 3, 30);
    insertHeap(&h, 5, 1000);
    insertHeap(&h, 7, 300);
    insertHeap(&h, 10, 01245);
    insertHeap(&h, 44, 70);
    insertHeap(&h, 30, 300);

    for (int i = 0; i < h->rare + 1; i++)
    {
        printf("%d %d\n", h->arr[0][i], h->arr[1][i]);
    }

    printf("\n");
    int j = h->rare;

    for (int i = 0; i < j + 5; i++)
    {
        printf("%d ", removeHeap(&h));
    }
    return 0;
}