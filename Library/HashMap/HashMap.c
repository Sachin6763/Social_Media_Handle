#include <stdio.h>
#include <string.h>
#include "HashMap.h"
#include <stdlib.h>

void initHash(hashMap **h, int n)
{
    hashMap *temp = (*h);
    (*h)->arr = (linknode **)malloc(sizeof(linknode *) * n);
    if (!temp->arr)
        printf("No allocation donev !!! \n");
    temp->size = n;

    for (int i = 0; i < n; i++)
    {
        temp->arr[i] = NULL;
    }

    return;
}

void add(hashMap **h, int i, char *str)
{
    hashMap *temp = (*h);
    if (i >= temp->size)
    {
        printf("No such hashValue found !!! \n");
        return;
    }

    linknode *n = (linknode *)malloc(sizeof(linknode));
    char *name = (char *)malloc(sizeof(str));
    if (!name || !n)
        printf("Not allocated \n");
    strcpy(name, str);
    n->str = name;
    n->next = NULL;

    temp->arr[i] = n;

    return;
}

void rem(hashMap **h, int i)
{

    hashMap *temp = (*h);
    if (i >= temp->size)
    {
        printf("No such hashValue found !!! \n");
        return;
    }
    linknode *remo = temp->arr[i];
    temp->arr[i] = NULL;
    free(remo);

    return;
}

char *getHashVal(hashMap *h, int i)
{
    if (i < 0 || h->size <= i)
        return NULL;
    if (h->arr[i] == NULL)
        return NULL;
    return h->arr[i]->str;
}

void traverse(hashMap *h)
{
    int n = h->size;
    for (int i = 0; i < n; i++)
    {
        if (h->arr[i] != NULL)
            printf("%d. %s\n", i, h->arr[i]->str);
    }
    return;
}

int hashCount(hashMap *h)
{
    int count = 0;
    for (int i = 0; i < h->size; i++)
    {
        if (h->arr[i] != NULL)
            count++;
    }
    return count;
}