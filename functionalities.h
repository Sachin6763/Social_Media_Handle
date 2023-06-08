#include "helping_functions.h"
#include "Security/encryption.h"
// #include "Library/HashMap/HashMap.h"

int seeProfile(graph **g, int t);
void seeConnections(graph g, int t);
void uploadPost(graph *g, int t);
int countTillNULL(FILE *fp);
void privateMessage(graph *g, int t);
void checkMessages(graph *g, int t);
void checkPost(graph *g, int t);
void seeRequests(graph *g, int t);
void makeNewConnections(graph *g, int t); // send request
void broadCast(graph *g, int t);
void removeChoice(graph *g, int t);

void viewGroup(graph *g, int t);
void adminView(graph *g, int t, char *filename);
void userView(graph *g, int t, char *filename);

void random(graph *g, int t);
void spaces(FILE *fp, int start, int end);
void storeHash(FILE *fp, int position);