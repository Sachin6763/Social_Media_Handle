#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <direct.h>
#include "helping_functions.h"

#define postStart 40
#define broadCastStart 200
#define messageStart 500
#define messageSize 500
#define postSize 160
#define broadCaseSize 300
#define space 500

int checkIdExit(graph *g, char str[])
{
    // printf("%d g->size", g->size);
    for (int i = 0; i < g->size; i++)
    {
        // printf("%d %s here\n", i, g->arr[i]->id);
        if (strcmp(g->arr[i]->id, str) == 0)
            return i;
    }
    return -1;
}

int isValidPassword(char str[])
{
    // test 1 : length of password should be strictly 8
    // test 2 : containg at least one uppercase letter and one non alphabetical and non-numerical letter
    // test 3 : cannot start with number

    if (strlen(str) < 8 || strlen(str) > 8)
    {
        return -1;
    }

    if (str[0] >= '0' && str[0] <= '9')
        return -1;

    int flag = 0;
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
            flag = 1;
    }
    if (flag == 0)
        return -1;

    flag = 0;
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] == '!' || str[i] == '@' || str[i] == '#' || str[i] == '$' || str[i] == '%' || str[i] == '^' || str[i] == '&' || str[i] == '*')
            flag = 1;
    }

    if (flag == 0)
        return -1;

    for (int i = 0; i < strlen(str); i++)
    {
        if (!((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= '0' && str[i] <= '9') || (str[i] == '!' || str[i] == '@' || str[i] == '#' || str[i] == '$' || str[i] == '%' || str[i] == '^' || str[i] == '&' || str[i] == '*')))
            return -1;
    }
    return 1;
}

int isValidId(char str[])
{

    // test 1 : length of password should be strictly greter than 7 and less that 16
    // test 2 : containing characters in the given range
    // test 3 : cannot start with number

    if (strlen(str) < 8 || strlen(str) > 16)
        return -1;

    if (str[0] >= '0' && str[0] <= '9')
        return -1;

    for (int i = 0; i < strlen(str); i++)
    {
        if (!((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= '0' && str[i] <= '9') || (str[i] == '!' || str[i] == '@' || str[i] == '#' || str[i] == '$' || str[i] == '%' || str[i] == '^' || str[i] == '&' || str[i] == '*')))
            return -1;
    }

    return 1;
}

void changePassword(graph *g, int t, char *str)
{
    head *h = g->arr[t];
    strcpy(h->pass, str);

    char file[20] = "folder/";
    strcat(file, h->id);
    FILE *fp = fopen(file, "r+");

    fseek(fp, 0, 0);
    stringEncryption(h->id);
    stringEncryption(h->pass);
    h->count = numberEncryption(h->count);
    fprintf(fp, "%s\n%s\n%d\n", h->id, h->pass, h->count);
    stringDecryption(h->id);
    stringDecryption(h->pass);
    h->count = numberDecryption(h->count);
    fclose(fp);

    strcpy(file, "");
    strcat(file, "main.txt");
    fp = fopen(file, "r+");

    int offset = 20 + 100 * t;
    fseek(fp, offset, 0);
    char id[20];
    char pass[20];
    int count;
    int sr;

    fscanf(fp, "%d %d %s %s ", &sr, &count, id, pass);
    int arr[h->count];

    for (int i = 0; i < h->count; i++)
    {
        fscanf(fp, "%d ", arr + i);
    }

    fseek(fp, offset, 0);
    stringEncryption(h->pass);
    fprintf(fp, "%d %d %s %s ", sr, count, id, h->pass);
    stringDecryption(h->pass);
    for (int i = 0; i < h->count; i++)
    {
        fprintf(fp, "%d ", arr[i]);
    }

    fclose(fp);
    return;
}

void changeId(graph *g, int t, char *str)
{

    head *h = g->arr[t];
    char oldname[30];
    strcpy(oldname, "");
    strcat(oldname, "folder/");
    strcat(oldname, h->id);
    char newname[30];
    strcpy(newname, "");
    strcat(newname, "folder/");
    strcat(newname, str);

    if (rename(oldname, newname) == 0)
    {
        printf("File renamed successfully.\n");
    }
    else
    {
        printf("Error renaming the file.\n");
        return;
    }

    strcpy(h->id, "");
    strcpy(h->id, str);

    char file[20] = "folder/";
    strcat(file, h->id);
    FILE *fp = fopen(file, "r+");
    fseek(fp, 0, 0);
    stringEncryption(h->id);
    stringEncryption(h->pass);
    h->count = numberEncryption(h->count);
    fprintf(fp, "%s\n%s\n%d\n", h->id, h->pass, h->count);
    h->count = numberDecryption(h->count);
    stringDecryption(h->id);
    stringDecryption(h->pass);
    fclose(fp);

    strcpy(file, "");
    strcat(file, "main.txt");
    fp = fopen(file, "r+");
    if (!fp)
    {
        printf("Main file doesn't open !!! \n");
        return;
    }
    int offset = 20 + 100 * t;
    fseek(fp, offset, 0);
    char id[20];
    char pass[20];
    int count;
    int sr;

    fscanf(fp, "%d %d %s %s ", &sr, &count, id, pass);
    int arr[h->count];
    for (int i = 0; i < h->count; i++)
    {
        fscanf(fp, "%d ", arr + i);
    }

    fseek(fp, offset, 0);

    stringEncryption(h->id);
    stringEncryption(h->pass);
    fprintf(fp, "%d %d %s %s ", sr, count, h->id, h->pass);
    stringDecryption(h->id);
    stringDecryption(h->pass);
    for (int i = 0; i < h->count; i++)
    {
        fprintf(fp, "%d ", arr[i]);
    }

    fclose(fp);
}

void deleteChatHistory(graph g, int t, int pos)
{

    head *h = g.arr[t];

    char file[20] = "folder/";
    strcat(file, h->id);
    FILE *fp = fopen(file, "r+");

    int offset = messageStart + pos * messageSize;

    fseek(fp, offset, 0);
    fprintf(fp, "#");
    // stringEncryption(null);
    fputc('\0', fp);

    fclose(fp);
}

int makeGroup(char *userFile, char *groupName, int t, int adminMode)
{

    char file[20] = "folder/";
    strcat(file, userFile);
    FILE *fp = fopen(file, "r+");
    fseek(fp, 400, 0);

    int previousGroupCount = 0;
    fscanf(fp, "%d ", &previousGroupCount);
    previousGroupCount = numberDecryption(previousGroupCount);

    char **groupNameArray = (char **)malloc(sizeof(char *) * (previousGroupCount + 1));
    if (!groupNameArray)
    {
        printf("Memory is not allocated successfully for groupNameArray !!! \n");
        return 0;
    }

    for (int i = 0; i <= previousGroupCount; i++)
    {
        groupNameArray[i] = (char *)malloc(sizeof(char) * 20);
        if (!groupNameArray[i])
        {
            printf("Memory is not allocated successfully for groupNameArray[i] !!! \n");
            return -1;
        }
    }

    for (int i = 0; i < previousGroupCount; i++)
    {
        fscanf(fp, "%s ", groupNameArray[i]);
        stringDecryption(groupNameArray[i]);
        if (strcmp(groupNameArray[i], groupName) == 0)
        {
            printf("Group named %s already exist !!! \n", groupName);
            return -1;
        }
        stringEncryption(groupNameArray[i]);
    }

    char *newGroup = (char *)malloc(sizeof(char) * 20);
    if (!newGroup)
    {
        printf("Memory is not allocated for new Group \n");
        return -1;
    }
    printf("here\n");

    strcpy(newGroup, "");
    strcat(newGroup, groupName);
    groupNameArray[previousGroupCount] = newGroup;
    stringEncryption(groupNameArray[previousGroupCount]);

    fseek(fp, 400, 0);
    int enPreviousCount = numberEncryption(previousGroupCount + 1);
    fprintf(fp, "%d ", enPreviousCount);
    for (int i = 0; i <= previousGroupCount; i++)
    {
        fprintf(fp, "%s ", groupNameArray[i]);
    }

    fclose(fp);

    for (int i = 0; i < previousGroupCount + 1; i++)
    {
        free(groupNameArray[i]);
    }
    free(groupNameArray);

    // printf("here");
    strcpy(file, "");
    strcat(file, "Groups/");
    strcat(file, groupName);

    if (_mkdir("Groups") == 0)
    {
        printf("Folder created successfully.\n");
    }
    else
    {
        printf("Folder creation failed or already exists.\n");
    }
    if (access(file, W_OK) != 0)
    {
        FILE *create = fopen(file, "w");

        fclose(create);
    }

    fp = fopen(file, "r+");
    if (!fp)
    {
        printf("New Group File not opened successfully  !!! \n ");
        return -1;
    }

    fseek(fp, 0, 0);
    int currentUserCount = 1;
    currentUserCount = numberEncryption(currentUserCount);
    adminMode = numberEncryption(adminMode);
    t = numberEncryption(t);
    fprintf(fp, "%d\n", currentUserCount);
    fprintf(fp, "%d\n%d ", adminMode, t);
    t = numberDecryption(t);
    adminMode = numberDecryption(adminMode);

    fclose(fp);

    printf("Total Success \n");

    return 1;
}

int isExistinGroup(char *file, int t) // return's 1 if exist
{
    char filename[20];
    strcpy(filename, "");
    strcat(filename, "Groups/");
    strcat(filename, file);
    // printf("%s \n", filename);
    FILE *fp = fopen(filename, "r+");
    if (!fp)
    {
        printf("Can't open main file in Exist function !!! \n");
        return 0;
    }
    int members, adminMode;
    fscanf(fp, "%d\n%d\n", &members, &adminMode);
    members = numberDecryption(members);
    adminMode = numberDecryption(adminMode);
    int temp;
    for (int i = 0; i < members; i++)
    {
        fscanf(fp, "%d ", &temp);
        temp = numberDecryption(temp);
        if (temp == t)
            return 1;
    }

    return 0;
}