// #include "graphs.h"
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <direct.h>
#include "functionalities.h"
#include "Library/PriorityQueue/Heaps.h"
#include "Library/Queue/queue.h"

#define postStart 40
#define broadCastStart 200
#define messageStart 500
#define messageSize 500
#define postSize 160
#define broadCaseSize 300
#define space 500

void init(char *filename, graph *g)
{
    FILE *fp = fopen(filename, "r");
    if (!fp)
    {
        printf("main file not opened in init \n");
        return;
    }
    int decSize;
    fscanf(fp, "%d\n", &decSize);
    g->size = numberDecryption(decSize);
    // printf("%d", g->size);

    g->arr = (head **)malloc(sizeof(head *) * (g->size));

    for (int i = 0; i < g->size; i++)
        g->arr[i] = NULL;

    for (int i = 0; i < g->size; i++)
    {
        int curr, size = 0;
        int off = 20 + 100 * i;
        fseek(fp, off, 0);
        int decCurr, decSize;
        fscanf(fp, "%d %d ", &decCurr, &decSize);
        // printf("%d %d tt \n", decCurr, decSize);
        curr = numberDecryption(decCurr);
        size = numberDecryption(decSize);
        head *h = (head *)malloc(sizeof(head));
        g->arr[i] = h;
        h->id = (char *)malloc(sizeof(char) * 20);
        h->pass = (char *)malloc(sizeof(char) * 20);
        h->count = size;

        fscanf(fp, "%s %s ", h->id, h->pass);
        stringDecryption(h->id);
        stringDecryption(h->pass);
        // printf("%s %s %d ", h->id, h->pass, size);

        // making id and password file
        char new_file[20] = "folder/";
        strcat(new_file, h->id);

        if (access(new_file, W_OK) != 0)
        {
            FILE *create = fopen(new_file, "w");
            // spaces(create, 0, 10000);
            fclose(create);
        }

        h->next = NULL;
        // printf("%d\n", size);
        for (int j = 0; j < size; j++)
        {
            node *temp;
            temp = (node *)malloc(sizeof(node));
            if (!temp)
            {
                printf("Error in allocating \n");
                return;
            }
            int decTemp;
            fscanf(fp, "%d ", &decTemp);
            temp->data = numberDecryption(decTemp);
            // printf("%d\n", temp->data);
            temp->next = h->next;
            h->next = temp;
        }
    }

    // for (int i = 0; i < g->size; i++)
    // {
    //     node *temp = g->arr[i]->next;
    //     head *h = g->arr[i];
    //     if (strcmp(h->id, "null") == 0)
    //         continue;
    //     printf("%s %s", h->id, h->pass);
    //     while (temp)
    //     {
    //         printf("%d ", temp->data);
    //         temp = temp->next;
    //     }
    //     printf("\n");
    // }

    // printf("success\n");
}

int find(graph g, char *str)
{

    for (int i = 0; i < g.size; i++)
    {
        if (strcmp(g.arr[i]->id, str) == 0)
        {
            return i;
        }
    }

    return -1;
}

void printGraph(graph *g)
{
    for (int i = 0; i < g->size; i++)
    {
        node *temp = g->arr[i]->next;
        head *h = g->arr[i];
        if (h == NULL)
            continue;
        printf("%d %s %s ", i, h->id, h->pass);
        while (temp)
        {
            printf("%d ", temp->data);
            temp = temp->next;
        }
        printf("\n");
    }

    // printf("success\n");
}

void init_files(graph *g)
{
    head **temp = g->arr;

    if (_mkdir("folder") == 0)
    {
        printf("Folder created successfully.\n");
    }
    else
    {
        printf("Folder creation failed or already exists.\n");
    }

    for (int i = 0; i < g->size; i++)
    {

        head *curr = temp[i];

        char file[20] = "folder/";
        strcat(file, curr->id);
        FILE *fp = fopen(file, "r+");

        stringEncryption(curr->id);
        stringEncryption(curr->pass);
        int enCount = numberEncryption(curr->count);
        fprintf(fp, "%s\n", curr->id);
        fprintf(fp, "%s\n", curr->pass);
        fprintf(fp, "%d\n", enCount);
        stringDecryption(curr->id);
        stringDecryption(curr->pass);

        int sendRequestCount = 0, getRequestsCount = 0;

        // again is of no use so direclty encrypt into single integer

        sendRequestCount = numberEncryption(sendRequestCount);
        getRequestsCount = numberEncryption(getRequestsCount);
        fseek(fp, 200, 0);
        fprintf(fp, "%d ", sendRequestCount);
        fseek(fp, 300, 0);
        fprintf(fp, "%d ", getRequestsCount);

        int groupCreated = 0, groupHasPart = 0;
        groupCreated = numberEncryption(groupCreated);
        groupHasPart = numberEncryption(groupHasPart);
        fseek(fp, 400, 0);
        fprintf(fp, "%d ", groupCreated);
        fseek(fp, 450, 0);
        fprintf(fp, "%d ", groupHasPart);

        // initialize all reserve chat with #

        // int off = 200, t = 0;
        // node *trav = curr->next;
        // while (trav)
        // {
        //     storeHash(fp, off + t);
        //     t += 500;
        //     trav = trav->next;
        // }
        // printf("%d\n", i);

        fclose(fp);
    }
}

void init_id(graph *g, char *id, char *pass)
{
    // build connection in graph i.e. update graph

    g->arr = realloc(g->arr, sizeof(head *) * (g->size + 1));
    head *h = (head *)malloc(sizeof(head));
    g->arr[g->size] = h;
    h->id = (char *)malloc(sizeof(char) * 20);
    h->pass = (char *)malloc(sizeof(char) * 20);
    h->next = NULL;
    if (!h->id || !h->pass)
    {
        printf("Error !!! in init_id \n");
    }
    // printf("here");
    // printf("%s %s \n", id, pass);
    strcpy(h->id, "");
    strcpy(h->pass, "");
    strcat(h->id, id);
    strcat(h->pass, pass);
    h->count = 0;
    g->size++;
    // printGraph(g);

    // build connection in files for long and parman. storage

    // In main file
    int offset = 20 + (g->size - 1) * 100;
    FILE *fp = fopen("main.txt", "r+");
    fseek(fp, 0, 0);
    g->size = numberEncryption(g->size);
    fprintf(fp, "%d\n", g->size);
    g->size = numberDecryption(g->size);
    fseek(fp, offset, 0);
    int sr = g->size - 1;
    sr = numberEncryption(sr);
    h->count = numberEncryption(h->count);
    stringEncryption(h->id);
    stringEncryption(h->pass);
    fprintf(fp, "%d %d %s %s ", sr, h->count, h->id, h->pass);
    h->count = numberDecryption(h->count);
    stringDecryption(h->id);
    stringDecryption(h->pass);
    fclose(fp);

    // printf("here");

    if (_mkdir("folder") == 0)
    {
        printf("Folder created successfully.\n");
    }
    else
    {
        printf("Folder creation failed or already exists.\n");
    }

    char file[20] = "folder/";
    strcat(file, h->id);
    if (access(file, W_OK) != 0)
    {
        FILE *create = fopen(file, "w");
        // spaces(create, 0, 10000);
        fclose(create);
    }

    fp = fopen(file, "r+");

    fseek(fp, 0, 0);
    stringEncryption(h->id);
    stringEncryption(h->pass);
    h->count = numberEncryption(h->count);
    fprintf(fp, "%s\n%s\n%d\n", h->id, h->pass, h->count);
    stringDecryption(h->id);
    stringDecryption(h->pass);
    h->count = numberDecryption(h->count);
    fseek(fp, 200, 0);
    int sendRequestCount = 0, getRequestsCount = 0;
    // no use of this variable again so no need to decrypt
    sendRequestCount = numberEncryption(sendRequestCount);
    getRequestsCount = numberEncryption(getRequestsCount);
    fprintf(fp, "%d ", sendRequestCount);
    fseek(fp, 300, 0);
    fprintf(fp, "%d ", getRequestsCount);

    int groupCreated = 0, groupHasPart = 0;
    groupCreated = numberEncryption(groupCreated);
    groupHasPart = numberEncryption(groupHasPart);
    fseek(fp, 400, 0);
    fprintf(fp, "%d ", groupCreated);
    fseek(fp, 450, 0);
    fprintf(fp, "%d ", groupHasPart);

    fclose(fp);

    return;
}

void sendConnectionRequest(graph *g, int a, int b)
{
    // from a to b
    // broadcast field : 200-300 sent requests and 300-400 get requests
    /* Two phases
    1. Send request  -- > write and wait for accept
    2. Accept request   -- > accept and rub
    */

    // writing in a's file from 200 -to-300

    // printf("Connection Request : %s %s \n", g->arr[a]->id, g->arr[a]->pass);
    // printf("Connection Request : %s %s \n", g->arr[b]->id, g->arr[b]->pass);

    char file[20] = "folder/";
    strcat(file, g->arr[a]->id);
    FILE *fp = fopen(file, "r+");
    if (!fp)
    {
        printf("Error in opening file !!  \n ");
        return;
    }
    fseek(fp, 200, 0);
    int sendRequestCount = 0;
    fscanf(fp, "%d ", &sendRequestCount);
    sendRequestCount = numberDecryption(sendRequestCount);
    int req[sendRequestCount + 1];
    for (int i = 0; i < sendRequestCount; i++)
    {
        fscanf(fp, "%d ", &req[i]);
        int tmp = numberDecryption(req[i]);
        // printf("%d %dHera\n", tmp, b);
        if (b == tmp)
        {
            printf("Request has already sent !!! Please wait for action ... \n");
            return;
        }
    }

    req[sendRequestCount] = numberEncryption(b);
    fseek(fp, 200, 0);
    int enSendRequestCount = numberEncryption(sendRequestCount + 1);
    fprintf(fp, "%d ", enSendRequestCount);
    for (int i = 0; i < sendRequestCount + 1; i++)
    {
        fprintf(fp, "%d ", req[i]);
    }
    fclose(fp);

    // writing in the file of b's

    strcpy(file, "");
    strcat(file, "folder/");
    strcat(file, g->arr[b]->id);
    fp = fopen(file, "r+");
    fseek(fp, 300, 0);
    int getRequestCount = 0;
    fscanf(fp, "%d ", &getRequestCount);
    getRequestCount = numberDecryption(getRequestCount);
    int get[getRequestCount + 1];
    for (int i = 0; i < getRequestCount; i++)
    {
        fscanf(fp, "%d ", &get[i]);
    }
    get[getRequestCount] = numberEncryption(a);
    fseek(fp, 300, 0);
    int enGetRequestCount = numberEncryption(getRequestCount + 1);
    fprintf(fp, "%d ", enGetRequestCount);
    for (int i = 0; i < getRequestCount + 1; i++)
    {
        fprintf(fp, "%d ", get[i]);
    }
    fclose(fp);

    printf("Request have been sent !!! \n");
}

void makeConnection(graph *g, int a, int b) // Accept connection request
{

    node *t1, *t2;
    t1 = (node *)malloc(sizeof(node));
    t2 = (node *)malloc(sizeof(node));
    t1->data = a;
    t1->next = NULL;
    t2->data = b;
    t2->next = NULL;

    head *h1 = g->arr[a];
    head *h2 = g->arr[b];

    h1->count++;
    h2->count++;

    if (h1->next)
    {
        node *temp1 = h1->next;
        while (temp1->next)
        {
            temp1 = temp1->next;
        }
        temp1->next = t2;
    }
    else
    {
        h1->next = t2;
    }

    if (h2->next)
    {
        node *temp2 = h2->next;
        while (temp2->next)
        {
            temp2 = temp2->next;
        }
        temp2->next = t1;
    }
    else
    {
        h2->next = t1;
    }

    // updating file

    // changing in a's file
    char file[20] = "folder/";
    strcat(file, h1->id);
    FILE *fp = fopen(file, "r+");

    char id[20];
    char pass[20];
    int count;

    fseek(fp, 0, 0);
    fscanf(fp, "%s\n%s\n%d\n", id, pass, &count);
    count = numberDecryption(count);
    count++;
    // printf("%d %s \n ", count, id);
    fseek(fp, 0, 0);
    count = numberEncryption(count);
    fprintf(fp, "%s\n%s\n%d\n", id, pass, count);
    fclose(fp);

    // changing in b's file
    strcpy(file, "");
    strcat(file, "folder/");
    strcat(file, h2->id);
    fp = fopen(file, "r+");

    strcpy(id, "");
    strcpy(pass, "");
    count = 0;

    fseek(fp, 0, 0);
    fscanf(fp, "%s\n%s\n%d\n", id, pass, &count);
    count = numberDecryption(count);
    count++;
    count = numberEncryption(count);
    // printf("%d %s \n ", count, id);
    fseek(fp, 0, 0);
    fprintf(fp, "%s\n%s\n%d\n", id, pass, count);
    fclose(fp);

    // printf("success\n");

    // changing main file
    strcpy(file, "");
    strcat(file, "main.txt");
    fp = fopen(file, "r+");
    if (!fp)
    {
        printf("main file not opened !!! ");
        return;
    }
    int offset1 = 20 + 100 * a;
    int offset2 = 20 + 100 * b;

    fseek(fp, offset1, 0);
    stringEncryption(h1->id);
    stringEncryption(h1->pass);
    a = numberEncryption(a);
    h1->count = numberDecryption(h1->count);
    fprintf(fp, "%d %d %s %s ", a, h1->count, h1->id, h1->pass);
    stringDecryption(h1->id);
    stringDecryption(h1->pass);
    h1->count = numberDecryption(h1->count);
    a = numberDecryption(a);
    int loop1 = h1->count;
    node *trav1 = h1->next;
    while (loop1 > 0 && trav1)
    {
        trav1->data = numberEncryption(trav1->data);
        fprintf(fp, "%d ", trav1->data);
        trav1->data = numberDecryption(trav1->data);
        trav1 = trav1->next;
        loop1--;
    }

    // second change for second user

    fseek(fp, offset2, 0);
    // printf("b %d count %d \n", b, h2->count);
    stringEncryption(h2->id);
    stringEncryption(h2->pass);
    b = numberEncryption(b);
    h2->count = numberEncryption(h2->count);
    fprintf(fp, "%d %d %s %s ", b, h2->count, h2->id, h2->pass);
    stringDecryption(h2->id);
    stringDecryption(h2->pass);
    b = numberDecryption(b);
    h2->count = numberDecryption(h2->count);
    int loop2 = h2->count;
    node *trav2 = h2->next;
    while (loop2 > 0 && trav2)
    {
        trav2->data = numberEncryption(trav2->data);
        fprintf(fp, "%d ", trav2->data);
        trav2->data = numberDecryption(trav2->data);
        trav2 = trav2->next;
        loop2--;
    }

    fclose(fp);

    // printf("success\n");
}

#define suggestions 10 /*                                                                       \
 void bfs(graph *g, int t, hashMap *mainMap, hashMap *subMap)                                   \
 {                                                                                              \
     // traverse bfs and check if int hash connection is present or not                         \
     // case 1 : if connection present -- > dont print because already has connection           \
     // case 2 : if connection is not present -- > print with suffix and id                     \
     int n = suggestions;                                                                       \
     Queue q;                                                                                   \
     Queue *pq = &q;                                                                            \
     Qinit(&pq);                                                                                \
                                                                                              \ \
     enqueue(&pq, t);                                                                           \
     int visited[g->size];                                                                      \
     for (int i = 0; i < g->size; i++)                                                          \
     {                                                                                          \
         visited[i] = 0;                                                                        \
     }                                                                                          \
                                                                                              \ \
     visited[t] = 1;                                                                            \
     int sr = 0;                                                                                \
                                                                                              \ \
     // printf("here");                                                                         \
     while (!QisEmpty(*pq) && n > 0)                                                            \
     {                                                                                          \
         int a = dequeue(&pq);                                                                  \
         if (a == INT_MIN)                                                                      \
         {                                                                                      \
             return;                                                                            \
         }                                                                                      \
         // printf("here was fault ");                                                          \
         head *h = g->arr[a];                                                                   \
         node *temp = h->next;                                                                  \
         while (temp)                                                                           \
         {                                                                                      \
             // printf("%d temp\n", temp->data);                                                \
             if (visited[temp->data] == 0)                                                      \
             {                                                                                  \
                 enqueue(&pq, temp->data);                                                      \
                 visited[temp->data] = 1;                                                       \
             }                                                                                  \
             // printf("%s %d %d \n", getHashVal(mainMap, temp->data), temp->data, h->count);   \
             if (getHashVal(mainMap, temp->data) == NULL)                                       \
             {                                                                                  \
                 add(&subMap, sr, g->arr[temp->data]->id);                                      \
                 sr++;                                                                          \
                 add(&mainMap, temp->data, g->arr[temp->data]->id);                             \
                 n--;                                                                           \
             }                                                                                  \
             temp = temp->next;                                                                 \
         }                                                                                      \
     }                                                                                          \
     // printf("true");                                                                         \
                                                                                              \ \
     while (!QisEmpty(q))                                                                       \
     {                                                                                          \
         dequeue(&pq);                                                                          \
     }                                                                                          \
     // printf("here");                                                                         \
                                                                                              \ \
     return;                                                                                    \
 }                                                                                              \
 */

void remainingSuggestions(graph *g, int remaining, hashMap *main, hashMap *subMap)
{
    // make priority queue
    heap h;
    heap *pq = &h;
    initHeap(&pq, g->size);
    // printf("i am in graphc");
    for (int i = 0; i < g->size; i++)
    {
        if (getHashVal(main, i) == NULL)
        {
            insertHeap(&pq, i, g->arr[i]->count);
        }
    }
    for (int i = 0; i < remaining; i++)
    {
        int t = removeHeap(&pq);
        if (t == INT_MIN)
        {
            // printf("heap is empty !!!");
            return;
        }
        add(&subMap, 10 - remaining + i, g->arr[t]->id);
    }
}

void removeConnection(graph *g, int a, int b)
{

    // Prereqisite a should be connection of b
    // remove from both a and b

    // Here a is real t but b is relative to a
    // finding real b

    // printf("a= %d b = %d", a, b);

    head *h1 = g->arr[a];
    head *h2 = g->arr[b];
    node *temp1 = h1->next, *temp2 = h2->next;
    int count1 = 0, count2 = 0;
    node *prev1 = NULL;
    node *prev2 = NULL;
    // printf("here");
    // 1. removing form graph

    // from a
    while (temp1)
    {
        if (temp1->data == b)
        {
            break;
        }
        prev1 = temp1;
        count1++;
        temp1 = temp1->next;
    }

    if (prev1 == NULL)
    {
        h1->next = temp1->next;
        free(temp1);
    }
    else
    {
        prev1->next = temp1->next;
        free(temp1);
    }

    // from b
    while (temp2)
    {
        if (temp2->data == a)
        {
            break;
        }
        prev2 = temp2;
        count2++;
        temp2 = temp2->next;
    }

    if (prev2 == NULL)
    {
        h2->next = temp2->next;
        free(temp2);
    }
    else
    {
        prev2->next = temp2->next;
        free(temp2);
    }

    h1->count--;
    h2->count--;

    // change in files of a and b

    // a's file

    char file[20] = "folder/";
    strcat(file, h1->id);
    FILE *fp = fopen(file, "r+");

    if (!fp)
    {
        printf("not opening file \n");
        return;
    }

    fseek(fp, 0, 0);
    stringEncryption(h1->id);
    // printf("%s\n", h1->pass);
    stringEncryption(h1->pass);
    h1->count = numberEncryption(h1->count);
    // printf("%s\n", h1->pass);
    fprintf(fp, "%s\n%s\n%d\n", h1->id, h1->pass, h1->count);
    stringDecryption(h1->id);
    stringDecryption(h1->pass);
    h1->count = numberDecryption(h1->count);
    int offset = messageStart + messageSize * count1;
    int iterate = h1->count + 2 - count1;
    int i = 1;

    char buffer[500];
    strcpy(buffer, "");
    // printf("%d iterate1 \n", iterate);
    while (iterate > 0)
    {
        fseek(fp, offset + i * messageSize, 0);
        fgets(buffer, 500, fp);
        if (strlen(buffer) == 0)
        {
            strcpy(buffer, "#");
        }
        fseek(fp, offset + (i - 1) * messageSize, 0);
        fprintf(fp, "%s", buffer);
        fputc('\0', fp);
        i++;
        strcpy(buffer, "");
        iterate--;
    }
    fseek(fp, offset + (i - 1) * messageSize, 0);
    fputc('\0', fp);
    fclose(fp);

    // b's file
    strcpy(file, "");
    strcat(file, "folder/");
    strcat(file, h2->id);

    if (!fp)
    {
        printf("not opening file \n");
        return;
    }

    fp = fopen(file, "r+");

    fseek(fp, 0, 0);
    stringEncryption(h2->id);
    stringEncryption(h2->pass);
    h2->count = numberEncryption(h2->count);
    // printf("%s\n", h2->pass);
    fprintf(fp, "%s\n%s\n%d\n", h2->id, h2->pass, h2->count);
    stringDecryption(h2->id);
    stringDecryption(h2->pass);
    h2->count = numberDecryption(h2->count);
    offset = messageStart + messageSize * count2;
    iterate = h2->count + 2 - count2;
    i = 1;

    strcpy(buffer, "");
    // printf("%d iterate2 \n", iterate);
    while (iterate > 0)
    {
        fseek(fp, offset + i * messageSize, 0);
        fgets(buffer, 500, fp);
        if (strlen(buffer) == 0)
        {
            strcpy(buffer, "#");
        }
        fseek(fp, offset + (i - 1) * messageSize, 0);
        fprintf(fp, "%s", buffer);
        fputc('\0', fp);
        i++;
        strcpy(buffer, "");
        iterate--;
    }
    fclose(fp);

    // main file

    strcpy(file, "");
    strcat(file, "main.txt");
    fp = fopen(file, "r+");

    // for a to remove
    offset = 20 + 100 * a;
    fseek(fp, offset, 0);
    char id[20];
    char pass[20];
    int count;
    int sr;
    fscanf(fp, "%d %d %s %s ", &sr, &count, id, pass);
    count = numberDecryption(count);
    count--;
    int arr[count];
    int temp;
    i = 0;
    for (int j = 0; j < count + 1; j++)
    {
        fscanf(fp, "%d ", &temp);
        temp = numberDecryption(temp);
        if (temp != b)
        {
            arr[i] = numberEncryption(temp);
            i++;
        }
    }
    fseek(fp, offset, 0);
    count = numberEncryption(count);
    fprintf(fp, "%d %d %s %s ", sr, count, id, pass);
    count = numberDecryption(count);
    for (int j = 0; j < count; j++)
    {
        fprintf(fp, "%d ", arr[j]);
    }

    // for b to remove

    offset = 20 + 100 * b;
    fseek(fp, offset, 0);
    char id1[20];
    char pass1[20];
    count = 0;
    sr = 0;
    fscanf(fp, "%d %d %s %s ", &sr, &count, id1, pass1);
    count = numberDecryption(count);
    count--;
    int new_arr[count];
    temp = 0;
    i = 0;
    // printf("%s %s\n", id1, pass1);
    for (int j = 0; j < count + 1; j++)
    {
        fscanf(fp, "%d ", &temp);
        temp = numberDecryption(temp);
        if (temp != a)
        {
            arr[i] = numberEncryption(temp);
            i++;
        }
    }
    fseek(fp, offset, 0);
    count = numberEncryption(count);
    fprintf(fp, "%d %d %s %s ", sr, count, id1, pass1);
    count = numberDecryption(count);
    for (int j = 0; j < count; j++)
    {
        fprintf(fp, "%d ", arr[j]);
    }

    fclose(fp);
}

void deleteUserAccount(graph **gh, int t)
{
    graph *g = (*gh);

    head *h = g->arr[t];
    node *temp = h->next;
    char idToDel[20] = "";
    strcat(idToDel, g->arr[t]->id);

    // printf("just before adjust\n");
    // printGraph(g);
    // printf("\n");

    while (temp)
    {
        removeConnection(g, t, temp->data);
        temp = h->next;
    }

    // printf("before adjust\n");
    // printGraph(g);
    // printf("\n");

    // delete sub-file and
    // readjustment of main file

    FILE *fp = fopen("main.txt", "r+");
    fseek(fp, 0, 0);
    int enSize = g->size - 1;
    enSize = numberEncryption(enSize);
    fprintf(fp, "%d\n", enSize);
    int offset = 20 + 100 * t;
    int times = g->size - t - 1;

    // data  variables
    char id[20];
    char pass[20];
    int count;
    int sr;

    for (int i = 0; i < times; i++)
    {
        // printf("here3");
        fseek(fp, offset + 100 * (i + 1), 0);
        // clearing all
        strcpy(id, "");
        strcpy(pass, "");
        fscanf(fp, "%d %d %s %s ", &sr, &count, id, pass);
        int total = numberDecryption(count);
        int arr[total + 1];

        for (int j = 0; j < total; j++)
        {
            fscanf(fp, "%d ", arr + j);
        }
        fseek(fp, offset + 100 * i, 0);

        fprintf(fp, "%d %d %s %s ", sr, count, id, pass);

        for (int j = 0; j < total; j++)
        {
            fprintf(fp, "%d ", arr[j]);
        }
    }
    fclose(fp);

    // fseek(fp, offset + 100 * (g->size - 1), 0);
    // fputc('\0', fp);
    // fclose(fp);

    // updateConnectionsRequest which is send by t

    char fileName[20];
    strcpy(fileName, "");
    strcat(fileName, "folder/");
    strcat(fileName, g->arr[t]->id);

    FILE *rt = fopen(fileName, "r+");

    if (!rt)
    {
        printf("File doesn't open !!! \n");
        return;
    }
    fseek(rt, 200, 0);
    int totalSentRequests = 0;
    fscanf(rt, "%d ", &totalSentRequests);
    totalSentRequests = numberDecryption(totalSentRequests);
    int req[totalSentRequests + 1];

    for (int i = 0; i < totalSentRequests; i++)
    {
        fscanf(rt, "%d ", req + i);
        req[i] = numberDecryption(req[i]);
    }

    for (int i = 0; i < totalSentRequests; i++)
    {
        // printf("hrer %d %s\n ", req[i]);
        if (req[i] < g->size)
            removeRequest(g->arr[req[i]]->id, t);
    }

    fclose(rt);

    // printf("Grand Success !!  \n ");

    // Finally adjustment in graph

    head *copy = g->arr[t];

    for (int i = t; i < g->size - 1; i++)
    {
        g->arr[i] = g->arr[i + 1];
    }
    // printf("here500\n");
    // printGraph(g);

    g->arr[g->size - 1] = NULL;
    free(copy);
    g->size--;
    // printf("g -> size -- %d\n", g->size);

    // g->arr = realloc(g->arr, g->size);
    // printf("%d final", g->size);

    // printf("Success");

    // removeConnection(g, t, tr->data);
    //
    // Update main file
    updateMainFile(&g, t);

    // Update graph
    UpdateGraph(&g, t);

    char FILENAME[20] = "folder/";
    strcat(FILENAME, idToDel);

    printf("To be removed : %s\n", FILENAME);
    if (remove(FILENAME) == 0)
    {
        printf("File deleted successfully.\n");
    }
    else
    {
        printf("Unable to delete the file.\n");
    }

    // if (g->size == 0)
    // {
    //     if (remove("main.txt") == 0)
    //     {
    //         printf("Main file deleted successfully \n");
    //     }
    //     else
    //     {
    //         printf("Unable to delete the file \n");
    //     }
    // }
}

void removeRequest(char *str, int t)
{

    printf("Removed request form the file having name : %s \n", str);

    char file[20];
    strcpy(file, "");
    strcat(file, "folder/");
    strcat(file, str);

    FILE *fp = fopen(file, "r+");

    if (!fp)
    {
        printf("File doesn't opened successfully !! \n");
        return;
    }

    fseek(fp, 300, 0);
    int totalRequests = 0;
    fscanf(fp, "%d ", &totalRequests);
    totalRequests = numberDecryption(totalRequests);
    int req[totalRequests + 1];
    int total = 0;
    for (int i = 0; i < totalRequests; i++)
    {
        int temp;
        fscanf(fp, "%d ", &temp);
        temp = numberDecryption(temp);
        if (temp == t)
        {
            continue;
        }
        if (temp > t)
        {
            temp--;
        }
        temp = numberEncryption(temp);
        req[total] = temp; //    encrypted array from start
        total++;
    }

    fseek(fp, 300, 0);
    int enTotal = numberEncryption(total);
    fprintf(fp, "%d ", enTotal);
    for (int i = 0; i < total; i++)
    {
        fprintf(fp, "%d ", req[i]);
    }

    fclose(fp);
}

void updateMainFile(graph **gh, int t)
{

    graph *g = (*gh);

    // printf("t = %d ", t);
    FILE *fp = fopen("main.txt", "r+");
    int offset = 20;

    char id[20], pass[20];
    int sr, count;
    // printf("%d", g->size);
    // return;
    for (int i = 0; i < g->size; i++)
    {
        fseek(fp, offset + 100 * i, 0);
        strcpy(id, "");
        strcpy(pass, "");
        fscanf(fp, "%d %d %s %s ", &sr, &count, id, pass);
        sr = numberDecryption(sr);
        // printf("%s %d \n", id, sr);
        if (sr > t)
        {
            sr--;
        }
        int deCount = numberDecryption(count);
        int arr[deCount + 1];
        for (int j = 0; j < deCount; j++)
        {
            int temp;
            fscanf(fp, "%d ", &temp);
            temp = numberDecryption(temp);
            if (temp > t)
            {
                temp--;
            }
            temp = numberEncryption(temp);
            arr[j] = temp; // encrypt array
        }
        fseek(fp, offset + 100 * i, 0);
        sr = numberEncryption(sr);
        fprintf(fp, "%d %d %s %s ", sr, count, id, pass);
        for (int j = 0; j < deCount; j++)
        {
            fprintf(fp, "%d ", arr[j]);
        }
    }

    fclose(fp);
}

void UpdateGraph(graph **gh, int t)
{

    graph *g = (*gh);

    for (int i = 0; i < g->size; i++)
    {
        head *h = g->arr[i];
        node *temp = h->next;
        while (temp)
        {
            if (temp->data > t)
            {
                temp->data--;
            }
            temp = temp->next;
        }
    }

    // printf("printing gprah \n");
    // printGraph(g);
    // printf("printing gprah \n");

    return;
}