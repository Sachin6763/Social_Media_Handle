#include <stdio.h>
#include "Library/HashMap/HashMap.h"
#include "Security/encryption.h"

typedef struct head
{
    char *id;
    char *pass;
    int count;
    struct node *next;
} head;

typedef struct node
{
    int data;
    struct node *next;
} node;

typedef struct graph
{
    head **arr;
    int size;
} graph;

void init(char *filename, graph *g);
void init_files(graph *g);
void printGraph(graph *g);
void init_id(graph *g, char *id, char *pass);
void sendConnectionRequest(graph *g, int a, int b);
void makeConnection(graph *g, int a, int b);
// void bfs(graph *g, int t, hashMap *mainMap, hashMap *subMap);
void remainingSuggestions(graph *g, int remaining, hashMap *main, hashMap *subMap);
void removeConnection(graph *g, int a, int b);
void deleteUserAccount(graph **g, int t);
void removeRequest(char *str, int t);
void UpdateGraph(graph **g, int t);
void updateMainFile(graph **g, int t);
//
int find(graph g, char *str);

/* Main task
Make node connection
Update files
1. main file
2. that connections file first 20 Bytes
*/
/* Tasks
do according to main file
create all the file for indivisual user
create graph
*/