#include <stdio.h>
#include <limits.h>
#include "Heaps.h"
#include <stdlib.h>

void initHeap(heap **pq, int size)
{
    (*pq)->arr = (int **)malloc(sizeof(int *) * 2);
    if (!(*pq)->arr)
    {
        printf("Memory is not allocated in Heap \n");
        return;
    }
    for (int i = 0; i < 2; i++)
    {
        (*pq)->arr[i] = (int *)malloc(sizeof(int) * size);
    }
    (*pq)->rare = -1;
    (*pq)->size = size;
    return;
}

void insertHeap(heap **pq, int id, int val)
{
    heap *head = (*pq);
    if (head->rare >= head->size)
    {
        for (int i = 0; i < 2; i++)
        {
            head->arr[i] = realloc(head->arr[i], 2 * head->size);
        }
        head->size *= 2;
    }
    head->rare++;
    head->arr[0][head->rare] = id;
    head->arr[1][head->rare] = val;

    int curr = head->rare;
    int parent = (curr - 1) / 2;

    while (head->arr[1][curr] > head->arr[1][parent])
    {
        int te = head->arr[1][curr];
        head->arr[1][curr] = head->arr[1][parent];
        head->arr[1][parent] = te;
        curr = parent;
        parent = (curr - 1) / 2;
    }

    return;
}

void heapify(int **arr, int i, int size)
{
    int curr = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < size && arr[1][curr] < arr[1][left])
    {
        curr = left;
    }

    if (right < size && arr[1][curr] < arr[1][right])
    {
        curr = right;
    }

    if (curr != i)
    {
        int temp = arr[1][curr];
        arr[1][curr] = arr[1][i];
        arr[1][i] = temp;
        temp = arr[0][curr];
        arr[0][curr] = arr[0][i];
        arr[0][i] = temp;
        heapify(arr, curr, size);
    }
    return;
}

int removeHeap(heap **pq)
{
    heap *temp = (*pq);
    if (temp->rare == -1)
    {
        return INT_MIN;
    }
    int te = temp->arr[0][0];
    temp->arr[0][0] = temp->arr[0][temp->rare];
    temp->arr[1][0] = temp->arr[1][temp->rare];
    temp->rare--;

    heapify(temp->arr, 0, temp->rare + 1);

    return te;
}

int topHeap(heap *pq)
{

    if (pq->rare == -1)
        return INT_MIN;

    return pq->arr[0][pq->rare];
}