#include "graphs.h"

int checkIdExit(graph *g, char *id1);
int isValidId(char id[]);
int isValidPassword(char str[]);
void changePassword(graph *g, int t, char *str);
void changeId(graph *g, int t, char *id);
void changeUsername(graph *g, int t, char *str);
void deleteChatHistory(graph g, int t, int pos);
int isExistinGroup(char *file, int t);
int makeGroup(char *userFile, char *groupName, int t, int adminMode);