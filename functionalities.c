#include "functionalities.h"
#include <stdlib.h>
#include <string.h>

#define postStart 40
#define broadCastStart 200
#define messageStart 500
#define messageSize 500
#define postSize 160
#define broadCaseSize 300
#define GroupMessagesSize 2000
#define GroupMessagesStart 200
#define space 500

int seeProfile(graph **gh, int t) // 1 for sign out
{
    graph *g = (*gh);
    head *h = g->arr[t];

    int choice;

    while (1)
    {
        printf("Enter \n1. To see username and no. of connections \n2. To change Username(Id) \n3. To change password \n4. To clear chat history \n5. Sign out \n6. To delete Account  \n7. Make New Group \n8. Move back\n");

        scanf("%d", &choice);

        if (choice == 1)
        {
            printf("----- Details ----- \n");
            printf("Username : %s \nNo. of Connections : %d \n", h->id, h->count);
        }
        else if (choice == 2)
        {
            printf("Enter your Password \n");
            char id[20];
            scanf("%s", id);
            if (strcmp(h->pass, id) == 0)
            {
                printf("Enter new Id \n");
                strcpy(id, "");
                scanf("%s", id);
                if (isValidId(id) != -1)
                {
                    changeId(g, t, id); // change Id
                    printf("    ---  Username changed successfully  ----    \n");
                }
                else
                {
                    printf("Enter strong Id having following protocols \n1. Cannot start with no. \n2. Having symbols in given range i.e. alphanumericals and special character including ('!', '@', '#', '$', '%', '^', '&','*') . \n3. Length should be at least 8 and cannot grater than 16. \n");
                }
            }
            else
            {
                printf("Password doesn't match !!! \n");
            }
        }
        else if (choice == 3)
        {
            printf("Enter your password \n");
            char pass[20];
            scanf("%s", pass);
            if (strcmp(h->pass, pass) == 0)
            {
                printf("Enter new password \n");
                strcpy(pass, "");
                scanf("%s", pass);
                if (isValidPassword(pass) != -1)
                {
                    changePassword(g, t, pass); // change password
                    printf("    ---  Password changed successfully  ----    \n");
                }
                else
                {
                    printf("Enter strong password having following protocols \n1. Cannot start with no. \n2. Having at least one uppercase symbol. \n3. Having one non-alphanumberical symbol.\n4. Remaing all should be alphabets only. \n5. Contain exactly 8 letters\n");
                }
            }
            else
            {
                printf("Password doesn't match !!! \n");
            }
        }
        else if (choice == 4)
        {
            seeConnections(*g, t);
            if (g->arr[t]->count == 0)
            {
                continue;
            }
            printf("Enter how many connections history do you want to clear \n");
            int count = 0;
            scanf("%d", &count);
            if (count <= 0 || count > h->count)
            {
                printf("Enter valid count \n");
                continue;
            }
            int arr[count];
            printf("Enter the suffix no. of connections one-by-one \n");

            for (int i = 0; i < count; i++)
            {
                scanf("%d", arr + i);
            }

            for (int i = 0; i < count; i++)
            {
                if (arr[i] < h->count && arr[i] >= 0)
                {
                    deleteChatHistory(*g, t, arr[i]);
                }
            }
            printf("    ----   History Cleared Successfully !!!  ----    \n");
        }
        else if (choice == 5)
        {
            // 1 for sign out
            return 1;
        }
        else if (choice == 6)
        {
            printf("Enter the password \n");
            char pas[20];
            scanf("%s", pas);
            if (strcmp(pas, h->pass) == 0)
            {
                printf("Are you sure with deletion of your account !!! Please confirm by pressing 1 otherwise press any number for unsure\n");
                int sure = 0;
                scanf("%d", &sure);
                if (sure == 1)
                {
                    deleteUserAccount(gh, t);
                    printf("    ---   Account Deleted Successfully   ----    \n");
                    return 1;
                }
            }
            else
            {
                printf("Password is Incorrect !!! \n");
            }
        }
        else if (choice == 7)
        {
            printf("Enter Group Name : ");
            char name[20];
            scanf("%s", name);
            printf("Choose 1 for Admin can message only otherwise any number for all can message permission \n");
            int adminMode = 0;
            scanf("%d", &adminMode);
            if (adminMode != 1)
            {
                adminMode = 0;
            }
            int group = makeGroup(h->id, name, t, adminMode);
            if (group == 1)
            {
                printf("Group Created Successfully !!! \n");
            }
            else
            {
                printf("Some Error in creating a Group !!!  \n");
            }
        }
        else if (choice == 8)
        {
            return 0;
        }
        else
        {
            printf("Enter valid choice \n");
        }
    }

    return 0;
}

void seeConnections(graph g, int t)
{
    node *temp = g.arr[t]->next;

    if (!temp)
    {
        printf("Not any connections yet \n");
        return;
    }

    int i = 0;

    while (temp)
    {
        printf("%d. %s \n", i++, g.arr[temp->data]->id);
        temp = temp->next;
    }

    printf("\n");

    return;
}

int findConnectionNumber(graph *g, int t, char *id)
{
    node *temp = g->arr[t]->next;
    int count = 0;
    while (temp)
    {
        if (strcmp(g->arr[temp->data]->id, id) == 0)
            return count;
        temp = temp->next;

        count++;
    }
    return -1;
}

int findUserNumber(graph *g, char *id)
{
    head **h = g->arr;
    for (int i = 0; i < g->size; i++)
    {
        if (strcmp(h[i]->id, id) == 0)
            return i;
    }
    return -1;
}

void uploadPost(graph *g, int t)
{

    head *h = g->arr[t];

    char file[20] = "folder/";
    strcat(file, h->id);
    FILE *fp = fopen(file, "r+");

    char *buffer = (char *)malloc(sizeof(char) * postSize);
    char *str = (char *)malloc(sizeof(char) * postSize);
    printf("Enter your post in text format \n");
    strcpy(str, "");
    scanf(" %[^\n]", str);
    strcpy(buffer, "");
    strcat(buffer, str);
    fseek(fp, postStart, 0);
    stringEncryption(buffer);
    fputs(buffer, fp);
    fputs('\0', fp);

    free(buffer);
    free(str);
    fclose(fp);
}

void privateMessage(graph *g, int t)
{
    if (g->arr[t]->count == 0)
    {
        printf("No connections yet !!! \n");
        return;
    }
    head *h = g->arr[t];

    printf("Enter the no. suffix of connections do you want to message \n");
    seeConnections(*g, t);

    int connectionNumber;
    scanf("%d", &connectionNumber);

    if (connectionNumber >= h->count || connectionNumber < 0)
    {
        printf("Enter valid connectionNumber \n");
        return;
    }

    char file[20] = "folder/";
    strcat(file, h->id);
    FILE *fp = fopen(file, "r+");

    char str[messageSize];
    printf("Enter your text message\n");
    scanf(" %[^\n]", str);

    int position = messageStart + connectionNumber * messageSize; // 10 for storage of count

    char *buffer = (char *)malloc(sizeof(char) * messageSize);

    fseek(fp, position, 0);
    strcpy(buffer, "");
    fgets(buffer, messageSize, fp);
    if (strlen(buffer) == 0 || buffer[0] == '\0')
    {
        // printf("this is success \n");
        strcat(buffer, "#");
    }
    stringDecryption(buffer);
    // adjustment
    strcat(str, "$");
    char *simu = (char *)malloc(sizeof(char) * 500);
    // strcpy(simu, buffer);

    // In self file
    strcat(buffer, "You");
    strcat(buffer, " : ");
    strcat(buffer, str);
    strcat(buffer, "\0");

    // printf("%s", buffer);
    fseek(fp, position, 0);

    stringEncryption(buffer);

    fputs(buffer, fp);
    fputc('\0', fp);
    fclose(fp);

    // In connection's file
    char connectionFile[20] = "folder/";
    int trav = connectionNumber;
    node *temp = h->next;
    while (trav && temp)
    {
        trav--;
        temp = temp->next;
    }
    // int un = findUserNumber(g, temp->name) ;
    strcat(connectionFile, g->arr[temp->data]->id);
    // printf("\n%s\n", connectionFile);
    FILE *fc = fopen(connectionFile, "r+");

    if (!fc)
        printf("Error");

    // finding position in connection's file
    node *tr = g->arr[temp->data]->next;
    int userNumber = 0;
    while (tr)
    {
        // printf("temp data : %d\n", tr->data);
        if (tr->data == t)
        {
            break;
        }
        userNumber++;
        tr = tr->next;
    }

    if (!temp)
    {
        printf("something went wrong in functionalities line no. 309 \n");
        return;
    }

    // printf("usernumber %d\n", userNumber);

    position = messageStart + userNumber * messageSize;
    fseek(fc, position, 0);
    strcpy(simu, "");
    fgets(simu, messageSize, fc);
    if (strlen(simu) == 0 || simu[0] == '\0')
    {
        // printf("success 2");
        simu[0] = '#';
    }
    stringDecryption(simu);

    strcat(simu, g->arr[t]->id);
    strcat(simu, " : ");
    strcat(simu, str);

    int offset = findConnectionNumber(g, temp->data, h->id);
    if (offset == -1)
    {
        printf("Error1");
    }
    else
    {
        fseek(fc, messageStart + offset * messageSize, 0);
        stringEncryption(simu);
        fputs(simu, fc);
        fputc('\0', fc);
    }
    fclose(fc);
}

void checkMessages(graph *g, int t)
{
    if (g->arr[t]->count == 0)
    {
        printf("No connections yet !!! \n");
        return;
    }

    head *h = g->arr[t];
    printf("Enter the no. suffix of connections do you want check message \n");

    seeConnections(*g, t);

    int choice;
    scanf("%d", &choice);

    if (choice < 0 || choice >= h->count)
    {
        printf("Enter valid choice \n");
        return;
    }

    int offset = messageStart + messageSize * choice;

    char file[20] = "folder/";
    strcat(file, h->id);
    FILE *fp = fopen(file, "r+");

    if (!fp)
    {
        printf("Error");
        return;
    }

    fseek(fp, offset, 0);
    char buffer[messageSize];
    strcpy(buffer, "");
    fgets(buffer, messageSize, fp);

    if (strlen(buffer) <= 1)
    {
        printf("No recent Messages or Conversation !!!\n");
    }

    // printf("%s", buffer);

    stringDecryption(buffer);

    for (int i = 1; i < strlen(buffer); i++)
    {
        if (buffer[i] == '$')
            printf("\n");
        else
            printf("%c", buffer[i]);
    }
}

void checkPost(graph *g, int t)
{
    if (g->arr[t]->count == 0)
    {
        printf("No connections yet !!! \n");
        return;
    }
    head *h = g->arr[t];
    int noOfConnections = h->count;
    node *temp = h->next;

    // HashMap to store which connection has valid information to share
    hashMap hM;
    hashMap *map = &hM;
    initHash(&map, h->count);

    int postCount = 0; // tells about how many connections uploaded the post
    int i = 0;

    while (noOfConnections > 0)
    {
        char file[20] = "folder/";
        strcat(file, g->arr[temp->data]->id);
        FILE *fp = fopen(file, "r+");
        char buffer[postSize];
        strcpy(buffer, "");
        fseek(fp, postStart, 0);
        fgets(buffer, postSize, fp);
        stringDecryption(buffer);
        if (strlen(buffer) != 0)
        {
            // printf("i %s ", buffer);     // It prints message and user Id
            // printf("i %s\n", file);

            add(&map, i, g->arr[temp->data]->id);
            postCount++;
        }
        i++;
        noOfConnections--;
        temp = temp->next;
    }

    // printf(" ss : %d", postCount);
    if (postCount > 0)
    {
        printf("Following Connections have something to share.\n");
        traverse(map);
        int choice;
        while (1)
        {
            printf("Enter the suffix no. of the connection to see his/her post. Or Enter -1 to exit from this page \n");
            scanf("%d", &choice);
            if (choice == -1)
            {
                break;
            }
            // If hash value corresponding to choice is present then print message otherwise print error code

            char *val = getHashVal(map, choice);
            if (val != NULL)
            {
                printf("          --- Post ---         \n");
                char filePost[20] = "folder/";
                strcat(filePost, val);
                FILE *fc = fopen(filePost, "r+");
                fseek(fc, postStart, 0);
                char message[postSize];
                strcpy(message, "");
                fgets(message, postSize, fc);
                stringDecryption(message);
                printf("%s\n", message);
                fclose(fc);
            }
            else
            {
                printf("Enter valid choice ... \n");
            }
        }
    }

    // here want data structure which maps the no. to the connection to thier name also to their post
    // HashMap : naming of number to the id of the connection
}

void makeNewConnections(graph *g, int t) // based on suggestions
{
    // print suggetions
    // assume sachin want to connect with jishan 5
    // make connection between 0 & 5

    // Step 1 : Suggestions --> 10 suggestions
    hashMap map1; // mapping of id to sr. no
    hashMap map2; // mapping of printed sr. no. to id

    hashMap *mainMap = &map1;
    hashMap *subMap = &map2;

    initHash(&mainMap, g->size);
    initHash(&subMap, 15);

    head *h = g->arr[t];
    int count = h->count;
    node *temp = h->next;
    add(&mainMap, t, h->id);

    for (int i = 0; i < count; i++)
    {
        add(&mainMap, temp->data, g->arr[temp->data]->id);
        temp = temp->next;
    }
    // printf("hii2");
    // Step 2 : call Make Connection
    // traverse(mainMap);
    // printf("hii2");
    // bfs(g, t, mainMap, subMap);
    // for (int i = 0; i < mainMap->size; i++)
    // {
    //     printf("%s ", getHashVal(mainMap, i));
    //     if (getHashVal(mainMap, i) == NULL)
    //         printf("hii");
    // }
    int totalRequests = hashCount(subMap);
    // printf("\n%d hash\n", totalRequests);
    int remaining = 10 - totalRequests;
    // printf("%d hash", remaining);0
    if (remaining > 0)
    {
        remainingSuggestions(g, remaining, mainMap, subMap);
    }
    printf("Enter the suffix no. of the connection to send connection request. Or Enter -1 to exit from this page \n");
    traverse(subMap);
    // printf("success2");

    int choice;
    scanf("%d", &choice);
    if (getHashVal(subMap, choice) == NULL)
    {
        printf("Enter valid suffix \n");
    }
    else
    {
        char *str = getHashVal(subMap, choice);
        int c = find(*g, str);
        sendConnectionRequest(g, t, c); // send connection request
    }

    /* This function takes mainMap and do bfs traversal if it come across any connection which is not in main map, then it add it into submap for printing and also add in the main map for not using it in again in future*/

    // makeConnection(g, 0, 5);
}

void seeRequests(graph *g, int t)
{

    head *h = g->arr[t];

    char file[20] = "folder/";
    strcat(file, h->id);
    FILE *fp = fopen(file, "r+");

    int totalRequests = 0;
    fseek(fp, 300, 0);
    fscanf(fp, "%d ", &totalRequests);
    totalRequests = numberDecryption(totalRequests);
    if (totalRequests == 0)
    {
        printf("No request yet !!! \n");
        return;
    }
    int reqArr[totalRequests];

    for (int i = 0; i < totalRequests; i++)
    {
        fscanf(fp, "%d ", reqArr + i);
        reqArr[i] = numberDecryption(reqArr[i]);
    }

    for (int i = 0; i < totalRequests; i++)
    {
        printf("%d. %s \n", reqArr[i], g->arr[reqArr[i]]->id);
    }
    fclose(fp);

    int count = 0, minus = 0;
    printf("Enter the count of how many requests will you accept \n");
    scanf("%d", &count);
    if (count < 0 || count > totalRequests)
    {
        printf("Enter valid count !!! \n");
        return;
    }
    while (count > 0)
    {
        int sr;
        printf("Enter the suffix no. of the connections whose request do you want to accept \n");
        scanf("%d", &sr);
        for (int i = 0; i < totalRequests; i++)
        {
            if (reqArr[i] == sr)
            {
                reqArr[i] = -1;
                minus++;
                makeConnection(g, t, sr);
                break;
            }
        }
        count--;
    }

    // printf("Connection Request : %s %s \n", h->id, h->pass);

    strcpy(file, "");
    strcat(file, "folder/");
    strcat(file, h->id);
    fp = fopen(file, "r+");
    fseek(fp, 300, 0);
    int remainingRequests = totalRequests - minus;
    int enRemaining = numberEncryption(remainingRequests);
    fprintf(fp, "%d ", enRemaining);
    int start = 0;
    for (int i = 0; i < remainingRequests; i++)
    {
        if (reqArr[start] == -1)
        {
            start++;
            continue;
        }
        int enTemp = numberEncryption(reqArr[start]);
        fprintf(fp, "%d ", enTemp);
        start++;
    }

    fclose(fp);
}

void broadCast(graph *g, int t)
{
    if (g->arr[t]->count == 0)
    {
        printf("No connections yet !!! \n");
        return;
    }

    head *h = g->arr[t];
    node *temp = h->next;

    int broadcastCount = 0;
    printf("Enter with how many connections do you want to do broadcasting ?  \n");
    scanf("%d", &broadcastCount);

    if (broadcastCount <= 0 || broadcastCount > h->count)
        return;

    printf("Enter the no. suffix of connections do you want to message one-by-one \n");
    seeConnections(*g, t);

    int broadcastArr[broadcastCount];

    for (int i = 0; i < broadcastCount; i++)
        scanf("%d", broadcastArr + i);

    char str[messageSize];
    printf("Enter your text message\n");
    scanf(" %[^\n]", str);
    strcat(str, "$");

    for (int i = 0; i < broadcastCount; i++)
    {

        int connectionNumber = broadcastArr[i];
        if (connectionNumber >= h->count || connectionNumber < 0)
        {
            continue;
        }

        char file[20] = "folder/";
        strcat(file, h->id);
        FILE *fp = fopen(file, "r+");

        int position = messageStart + connectionNumber * messageSize; // 10 for storage of count

        char *buffer = (char *)malloc(sizeof(char) * messageSize);

        fseek(fp, position, 0);
        strcpy(buffer, "");
        fgets(buffer, messageSize, fp);
        stringDecryption(buffer);
        if (strlen(buffer) == 0)
        {
            // printf("success 2");
            strcat(buffer, "#");
        }

        // adjustment
        char *simu = (char *)malloc(sizeof(char) * 500);
        // strcpy(simu, buffer);

        // In self file
        strcat(buffer, "You");
        strcat(buffer, " : ");
        strcat(buffer, str);
        strcat(buffer, "\0");

        // printf("%s", buffer);
        fseek(fp, position, 0);
        stringEncryption(buffer);
        fputs(buffer, fp);
        fputc('\0', fp);
        fclose(fp);

        // In connection's file
        char connectionFile[20] = "folder/";
        int trav = connectionNumber;
        node *temp = h->next;
        while (trav && temp)
        {
            trav--;
            temp = temp->next;
        }
        // int un = findUserNumber(g, temp->name) ;
        strcat(connectionFile, g->arr[temp->data]->id);
        // printf("\n%s\n", connectionFile);
        FILE *fc = fopen(connectionFile, "r+");

        if (!fc)
            printf("Error");

        // new insert

        node *tr = g->arr[temp->data]->next;
        int userNumber = 0;
        while (tr)
        {
            // printf("temp data : %d\n", tr->data);
            if (tr->data == t)
            {
                break;
            }
            userNumber++;
            tr = tr->next;
        }

        if (!tr)
        {
            printf("something went wrong in functionalities line no. 309 \n");
            return;
        }

        position = messageStart + userNumber * messageSize;

        // new insert finish

        fseek(fc, position, 0);
        strcpy(simu, "");
        fgets(simu, messageSize, fc);
        stringDecryption(simu);
        if (strlen(simu) == 0)
        {
            // printf("success 2");
            strcat(simu, "#");
        }

        strcat(simu, g->arr[t]->id);
        strcat(simu, " : ");
        strcat(simu, str);

        int offset = findConnectionNumber(g, temp->data, h->id);
        if (offset == -1)
        {
            printf("Error1");
        }
        else
        {
            fseek(fc, messageStart + offset * messageSize, 0);
            stringEncryption(simu);
            fputs(simu, fc);
            fputs('\0', fp);
        }
        free(buffer);
        fclose(fc);
    }
}

void removeChoice(graph *g, int t)
{
    if (g->arr[t]->count == 0)
    {
        printf("No connections yet !!! \n");
        return;
    }

    head *h = g->arr[t];
    node *temp = h->next;

    int suffix = 0;
    printf("Enter the no. suffix of connections do you want to delete \n");
    seeConnections(*g, t);
    scanf("%d", &suffix);

    if (suffix < 0 || suffix >= h->count)
    {
        printf("Enter valid suffix \n");
        return;
    }

    node *tr = h->next;
    for (int i = 0; i < suffix; i++)
    {
        tr = tr->next;
    }
    removeConnection(g, t, tr->data);
    // printf("successful \n");
}

void viewGroup(graph *g, int t)
{

    head *h = g->arr[t];
    // checkGroups
    // choice 1 : see messages
    // choice 2 : do message
    // choice 3 : view participents
    // choice 4 : send request to participents

    // admine -> remove someone from group
    //        -> delete history

    // print groupes

    char file[20] = "folder/";
    strcat(file, h->id);
    FILE *fp = fopen(file, "r+");

    int previousGroupCount = 0, previousNonAdminGroupCount = 0;
    fseek(fp, 450, 0);
    fscanf(fp, "%d ", &previousNonAdminGroupCount);
    fseek(fp, 400, 0);
    fscanf(fp, "%d ", &previousGroupCount);

    previousGroupCount = numberDecryption(previousGroupCount);
    previousNonAdminGroupCount = numberEncryption(previousNonAdminGroupCount);

    if (previousGroupCount == 0 && previousNonAdminGroupCount == 0)
    {
        printf("Not Groups yet !!! \n");
        return;
    }

    char **groupNameArray = (char **)malloc(sizeof(char *) * (previousGroupCount + previousNonAdminGroupCount));
    if (!groupNameArray)
    {
        printf("Memory is not allocated successfully for groupNameArray !!! \n");
        return;
    }

    for (int i = 0; i < previousGroupCount + previousNonAdminGroupCount; i++)
    {
        groupNameArray[i] = (char *)malloc(sizeof(char) * 20);
        if (!groupNameArray[i])
        {
            printf("Memory is not allocated successfully for groupNameArray[i] !!! \n");
            return;
        }
    }

    for (int i = 0; i < previousGroupCount; i++)
    {
        fscanf(fp, "%s ", groupNameArray[i]);
        stringDecryption(groupNameArray[i]);
    }

    fseek(fp, 450, 0);
    fscanf(fp, "%d ", &previousNonAdminGroupCount);
    previousNonAdminGroupCount = numberDecryption(previousNonAdminGroupCount);
    for (int i = previousGroupCount; i < previousGroupCount + previousNonAdminGroupCount; i++)
    {
        fscanf(fp, "%s ", groupNameArray[i]);
        stringDecryption(groupNameArray[i]);
    }

    fclose(fp);

    printf("Enter suffix for selecting group \n");

    for (int i = 0; i < previousGroupCount + previousNonAdminGroupCount; i++)
    {
        printf("%d. %s \n", i, groupNameArray[i]);
    }

    int selection = -1;
    scanf("%d", &selection);

    if (selection < 0 || selection >= previousGroupCount + previousNonAdminGroupCount)
    {
        printf("Enter valid selection choice !!! \n");
        return;
    }

    char *group = groupNameArray[selection];

    strcpy(file, "");
    strcat(file, "Groups/");
    strcat(file, group);

    fp = fopen(file, "r+");
    int members, adminMode, admin;
    fscanf(fp, "%d\n%d\n%d ", &members, &adminMode, &admin);
    members = numberDecryption(members);
    adminMode = numberDecryption(adminMode);
    admin = numberDecryption(admin);
    fclose(fp);

    if (admin == t)
    {
        adminView(g, t, groupNameArray[selection]);
        // decrypted array
    }
    else
    {
        printf("You are not admin \n");
        userView(g, t, groupNameArray[selection]);
    }

    return;
    // while (1)
    // {
    //     printf("%s \n", groupNameArray[selection]);
    //     printf("Enter\n1. To see Messages \n2. To send Message \n3. To view participants  \n");
    //     break;
    //     // do for some methods for user and admin seperate
    // }
}

void adminView(graph *g, int t, char *filename) // filename is offset name of group file in while function
{

    printf("   ---    Welcome to %s Group Admin  %s    ---    \n", filename, g->arr[t]->id);
    char file[20];
    strcpy(file, "");
    strcat(file, "Groups/");
    strcat(file, filename);

    FILE *fp = fopen(file, "r+");
    if (!fp)
    {
        printf("Error in file opening \n");
        return;
    }
    int members, adminMode, admin;

    fscanf(fp, "%d\n%d\n%d ", &members, &adminMode, &admin);
    members = numberDecryption(members);
    adminMode = numberDecryption(adminMode);
    admin = numberDecryption(admin);
    fclose(fp);

    while (1)
    {
        printf("Enter \n0. To change group name \n1. To send message on group\n2. To view messages on group \n3. To view Participants \n4. To add participants in connections \n5. To remove participants \n6. To Exit from the group \n7. Admine Mode Settings\n8. To leave from this page \n");
        int choice = 0;
        scanf("%d", &choice);
        if (choice == 0)
        {
            // changing group's name
            // change actual file name
            // update file name in member's file
            char newName[20];
            strcpy(newName, "");
            strcat(newName, "Groups/");
            char name[20];
            printf("Enter new name for group \n");
            scanf("%s", name);
            strcat(newName, name);

            strcpy(file, "");
            strcat(file, "Groups/");
            strcat(file, filename);
            // printf("%s filme\n", filename);
            if (rename(file, newName) == 0)
            {
                printf("File renamed successfully.\n");
            }
            else
            {
                printf("File rename failed.\n");
                continue;
            }

            // strcpy(file, "");
            // strcat(file, "Groups/");
            // strcat(file, filename);

            fp = fopen(newName, "r+");
            if (!fp)
            {
                printf("Error in file opening \n");
                rename(newName, file);
                return;
            }
            int members, adminMode;
            fscanf(fp, "%d\n%d\n", &members, &adminMode);
            members = numberDecryption(members);
            adminMode = numberDecryption(adminMode);
            int memberSuffix[members + 1];
            int temp;
            for (int i = 0; i < members; i++)
            {
                fscanf(fp, "%d ", &temp);
                memberSuffix[i] = numberDecryption(temp);
                // decrypted array
            }

            fclose(fp);

            for (int i = 0; i < members; i++)
            {
                strcpy(file, "");
                strcat(file, "folder/");
                int userIndex = memberSuffix[i];
                strcat(file, g->arr[userIndex]->id);
                fp = fopen(file, "r+");
                if (!fp)
                {
                    printf("Error in file opening while changing group name in participants file \n");
                    rename(newName, file) == 0;
                    return;
                }
                if (i == 0)
                {
                    fseek(fp, 400, 0);
                    int n;
                    fscanf(fp, "%d ", &n);
                    n = numberDecryption(n);
                    char groups[n][20];
                    for (int i = 0; i < n; i++)
                    {
                        fscanf(fp, "%s ", groups[i]);
                        stringDecryption(groups[i]);

                        // printf("filename : %s in main %s\n", filename, groups[i]);
                        // checking purpose

                        if (strcmp(filename, groups[i]) == 0)
                        {
                            strcpy(groups[i], "");
                            strcat(groups[i], name);
                            // strcpy(filename, "");
                            // strcat(filename, name);
                        }
                    }
                    fseek(fp, 400, 0);
                    int enn = numberEncryption(n);
                    fprintf(fp, "%d ", enn);
                    for (int i = 0; i < n; i++)
                    {
                        stringEncryption(groups[i]);
                        fprintf(fp, "%s ", groups[i]);
                    }
                }
                else
                {
                    fseek(fp, 450, 0);
                    int n;
                    fscanf(fp, "%d ", &n);
                    n = numberDecryption(n);
                    char groups[n][20];
                    for (int i = 0; i < n; i++)
                    {
                        fscanf(fp, "%s ", groups[i]);
                        stringDecryption(groups[i]);
                        // printf("%s %sfile\n", filename, groups[i]);
                        if (strcmp(filename, groups[i]) == 0)
                        {
                            strcpy(groups[i], "");
                            strcat(groups[i], name);
                        }
                    }
                    fseek(fp, 450, 0);
                    int enn = numberEncryption(n);
                    fprintf(fp, "%d ", enn);
                    for (int i = 0; i < n; i++)
                    {
                        stringEncryption(groups[i]);
                        fprintf(fp, "%s ", groups[i]);
                    }
                }
                fclose(fp);
            }
            strcpy(filename, "");
            strcat(filename, name);
        }
        else if (choice == 1)
        {
            char *str = (char *)malloc(sizeof(char) * 2000);
            if (!str)
            {
                printf("Can't alloc memory !!! \n");
                continue;
            }
            strcpy(file, "");
            strcat(file, "Groups/");
            strcat(file, filename);

            fp = fopen(file, "r+");
            if (!fp)
            {
                printf("Can't open file !!! \n");
                free(str);
                continue;
            }

            strcpy(str, "");

            fseek(fp, GroupMessagesStart, 0);
            fgets(str, GroupMessagesSize, fp);
            stringDecryption(str);
            // strcat(str, "$");
            head *h = g->arr[t];
            strcat(str, h->id);
            strcat(str, " : ");
            printf("Enter the text message \n");
            char *text = (char *)(malloc(sizeof(char) * 500));
            if (!text)
            {
                free(str);
                fclose(fp);
                printf("Memory not allocated \n");
                continue;
            }
            scanf(" %[^\n]", text);

            strcat(str, text);
            strcat(str, "$");

            fseek(fp, GroupMessagesStart, 0);
            stringEncryption(str);
            fprintf(fp, "%s", str);
            fclose(fp);
            free(str);
        }
        else if (choice == 2)
        {
            char *str = (char *)malloc(sizeof(char) * 2000);
            if (!str)
            {
                printf("Can't alloc memory !!! \n");
                continue;
            }
            strcpy(file, "");
            strcat(file, "Groups/");
            strcat(file, filename);

            fp = fopen(file, "r+");
            if (!fp)
            {
                printf("Can't open file !!! \n");
                free(str);
                continue;
            }

            fseek(fp, GroupMessagesStart, 0);
            fgets(str, GroupMessagesSize, fp);
            stringDecryption(str);

            for (int i = 0; i < strlen(str); i++)
            {
                if (str[i] == '$')
                {
                    printf("\n");
                }
                else
                {
                    printf("%c", str[i]);
                }
            }

            fclose(fp);
        }
        else if (choice == 3)
        {
            strcpy(file, "");
            strcat(file, "Groups/");
            strcat(file, filename);

            fp = fopen(file, "r+");
            if (!fp)
            {
                printf("Error in file opening \n");
                return;
            }
            fscanf(fp, "%d\n%d\n", &members, &adminMode);
            members = numberDecryption(members);
            int arr[members];
            for (int i = 0; i < members; i++)
            {
                fscanf(fp, "%d ", arr + i);
                arr[i] = numberDecryption(arr[i]);
            }

            for (int i = 0; i < members; i++)
            {
                printf("%d. %s \n", i, g->arr[arr[i]]->id);
            }

            fclose(fp);
        }

        else if (choice == 4)
        {
            // add connection
            head *h = g->arr[t];
            node *trav = h->next;
            int flag = 0;
            int notInGroup[h->count];
            int it = 0;
            while (trav)
            {
                notInGroup[it] = 0; // assume in group
                if (isExistinGroup(filename, trav->data) != 1)
                {

                    if (flag == 0)
                    {
                        printf("You have these many connections which are not part of the Group  \n");
                    }
                    printf("%d. %s\n", it, g->arr[trav->data]->id);
                    notInGroup[it] = 1; // not in group
                    flag = 1;
                }
                it++;
                trav = trav->next;
            }

            if (flag == 0)
            {
                printf("Your all connections are part of group \n");
                continue;
            }
            printf("Enter the suffix of connection to add in group \n");
            // seeConnections(*g, t);
            int suff;
            scanf("%d", &suff);

            if (suff < 0 || suff >= h->count || notInGroup[suff] == 0)
            {
                printf("Enter valid suffix \n");
                continue;
            }

            node *temp = h->next;
            for (int i = 0; i < suff; i++)
            {
                temp = temp->next;
            }

            if (!temp)
            {
                printf("can't add !!! \n");
                continue;
            }

            // changing in Group's file
            strcpy(file, "");
            strcat(file, "Groups/");
            strcat(file, filename);

            fp = fopen(file, "r+");
            if (!fp)
            {
                printf("Error in file opening \n");
                return;
            }
            fscanf(fp, "%d\n%d\n", &members, &adminMode);

            members = numberDecryption(members);

            int arr[members + 1];
            for (int i = 0; i < members; i++)
            {
                fscanf(fp, "%d ", arr + i);
            }
            members++;
            fseek(fp, 0, 0);

            int enMembers = numberEncryption(members);
            fprintf(fp, "%d\n%d\n", enMembers, adminMode);
            arr[members - 1] = numberEncryption(temp->data);
            for (int i = 0; i < members; i++)
            {
                fprintf(fp, "%d ", arr[i]);
            }
            fclose(fp);

            // changing in new participants file
            strcpy(file, "");
            strcat(file, "folder/");
            strcat(file, g->arr[temp->data]->id);
            fp = fopen(file, "r+");
            if (!fp)
            {
                printf("Error in file opening while adding new member \n");
                return;
            }

            fseek(fp, 450, 0);
            int n;
            fscanf(fp, "%d ", &n);
            n = numberDecryption(n);
            char groups[n + 1][20];
            for (int i = 0; i < n; i++)
            {
                fscanf(fp, "%s ", groups[i]);
            }
            strcpy(groups[n], "");
            strcat(groups[n], filename);
            stringEncryption(groups[n]);

            fseek(fp, 450, 0);
            n++;

            int enn = numberEncryption(n);
            fprintf(fp, "%d ", enn);
            for (int i = 0; i < n; i++)
            {
                fprintf(fp, "%s ", groups[i]);
            }

            fclose(fp);

            printf(" --- Connection Successfully added in Group ---  \n");
        }
        else if (choice == 5)
        {

            strcpy(file, "");
            strcat(file, "Groups/");
            strcat(file, filename);

            fp = fopen(file, "r+");
            if (!fp)
            {
                printf("Error in file opening \n");
                return;
            }
            fscanf(fp, "%d\n%d\n", &members, &adminMode);
            members = numberDecryption(members);
            int arr[members];
            for (int i = 0; i < members; i++)
            {
                fscanf(fp, "%d ", arr + i);
                arr[i] = numberDecryption(arr[i]);
            }

            printf("Enter the suffix of connection do you want to remove from group \n");

            for (int i = 1; i < members; i++)
            {
                printf("%d. %s \n", i, g->arr[arr[i]]->id);
            }

            int rm;
            scanf("%d", &rm);
            if (rm <= 0 || rm >= members)
            {
                printf("Enter valid suffix !!!\n");
                continue;
            }

            // to remove arr[rm] wala sr
            fseek(fp, 0, 0);
            int enMembers = numberEncryption(members - 1);
            fprintf(fp, "%d\n%d\n", enMembers, adminMode);
            for (int i = 0; i < members; i++)
            {
                if (i == rm)
                {
                    continue;
                }
                arr[i] = numberEncryption(arr[i]);
                fprintf(fp, "%d ", arr[i]);
            }
            fclose(fp);

            strcpy(file, "");
            strcat(file, "folder/");
            strcat(file, g->arr[arr[rm]]->id);

            fp = fopen(file, "r+");
            if (!fp)
            {
                printf("Error in file opening \n");
                return;
            }

            fseek(fp, 450, 0);
            int cnt;
            fscanf(fp, "%d ", &cnt);
            cnt = numberDecryption(cnt);
            char groups[cnt][20];
            for (int i = 0; i < cnt; i++)
            {
                fscanf(fp, "%s ", groups[i]);
                stringDecryption(groups[i]);
            }

            fseek(fp, 450, 0);
            int encnt = numberEncryption(cnt - 1);
            fprintf(fp, "%d ", encnt);
            for (int i = 0; i < cnt; i++)
            {
                if (strcmp(groups[i], filename) != 0)
                {
                    stringEncryption(groups[i]);
                    fprintf(fp, "%s ", groups[i]);
                }
            }

            fclose(fp);

            printf("     ---    Member %s removed Successfully   --- \n", g->arr[arr[rm]]->id);
        }
        else if (choice == 6)
        {
            // give choice of admin whom to make admin
            // delete it from admin account handle

            printf("Do you really want to exit from this group ? \nPlease confirm by pressing 1 \n");
            int ex = 0;
            scanf("%d", &ex);
            if (ex != 1)
            {
                continue;
            }
            strcpy(file, "");
            strcat(file, "Groups/");
            strcat(file, filename);

            fp = fopen(file, "r+");
            if (!fp)
            {
                printf("Error in file opening \n");
                return;
            }
            fscanf(fp, "%d\n%d\n", &members, &adminMode);
            members = numberDecryption(members);

            int arr[members];
            for (int i = 0; i < members; i++)
            {
                fscanf(fp, "%d ", arr + i);
                arr[i] = numberDecryption(arr[i]);
            }

            for (int i = 1; i < members; i++)
            {
                printf("%d. %s \n", i, g->arr[arr[i]]->id);
            }

            // printf("%d\n", members);

            if (members == 1)
            {

                char fileRemove[20];
                strcpy(fileRemove, "");
                strcat(fileRemove, "Groups/");
                strcat(fileRemove, filename);
                printf("%s\n", fileRemove);

                if (remove(fileRemove) == 0)
                {
                    printf("Group deleted successfully as there is no participants .\n");
                }
                else
                {
                    printf("File removal failed or does not exist.\n");
                }

                // changing previous admin's file

                strcpy(file, "");
                strcat(file, "folder/");
                strcat(file, g->arr[t]->id);

                fp = fopen(file, "r+");
                if (!fp)
                {
                    printf("Error in file opening \n");
                    return;
                }

                fseek(fp, 400, 0);
                int cnt;
                fscanf(fp, "%d ", &cnt);
                cnt = numberDecryption(cnt);
                char groups1[cnt][20];
                for (int i = 0; i < cnt; i++)
                {
                    fscanf(fp, "%s ", groups1[i]);
                    stringDecryption(groups1[i]);
                }

                fseek(fp, 400, 0);
                int encnt = numberEncryption(cnt - 1);
                fprintf(fp, "%d ", encnt);
                for (int i = 0; i < cnt; i++)
                {
                    if (strcmp(groups1[i], filename) != 0)
                    {
                        stringEncryption(groups1[i]);
                        fprintf(fp, "%s ", groups1[i]);
                    }
                }

                fclose(fp);

                return;
            }

            printf("Enter the suffix of connection do you want to be new admin of the Group \n");

            int rm;
            scanf("%d", &rm);
            if (rm <= 0 || rm >= members)
            {
                printf("Enter valid suffix !!!\n");
                continue;
            }

            fseek(fp, 0, 0);
            int enMem = numberEncryption(members - 1);
            fprintf(fp, "%d\n%d\n", enMem, adminMode);
            arr[rm] = numberEncryption(arr[rm]);
            fprintf(fp, "%d ", arr[rm]);
            for (int i = 1; i < members; i++)
            {
                if (i == rm)
                {
                    continue;
                }
                arr[i] = numberEncryption(arr[i]);
                fprintf(fp, "%d ", arr[i]);
            }
            fclose(fp);

            // changing in previous admins file

            strcpy(file, "");
            strcat(file, "folder/");
            strcat(file, g->arr[t]->id);

            fp = fopen(file, "r+");
            if (!fp)
            {
                printf("Error in file opening \n");
                return;
            }
            // printf("herei1\n");
            fseek(fp, 400, 0);
            int cnt;
            fscanf(fp, "%d ", &cnt);
            cnt = numberDecryption(cnt);
            char groups1[cnt][20];
            for (int i = 0; i < cnt; i++)
            {
                fscanf(fp, "%s ", groups1[i]);
                stringDecryption(groups1[i]);
            }

            fseek(fp, 400, 0);
            int enCnt = numberEncryption(cnt - 1);
            fprintf(fp, "%d ", enCnt);
            for (int i = 0; i < cnt; i++)
            {
                if (strcmp(groups1[i], filename) != 0)
                {
                    stringEncryption(groups1[i]);
                    fprintf(fp, "%s ", groups1[i]);
                }
            }

            fclose(fp);

            // printf("here");
            // changing in new admins file

            strcpy(file, "");
            strcat(file, "folder/");
            // printf("arr[rm] = %d \n", arr[rm]);
            arr[rm] = numberDecryption(arr[rm]);
            strcat(file, g->arr[arr[rm]]->id);

            fp = fopen(file, "r+");
            if (!fp)
            {
                printf("Error in file opening \n");
                return;
            }

            fseek(fp, 450, 0);
            cnt = 0;
            fscanf(fp, "%d ", &cnt);
            cnt = numberDecryption(cnt);
            char groups2[cnt][20];
            for (int i = 0; i < cnt; i++)
            {
                fscanf(fp, "%s ", groups2[i]);
                stringDecryption(groups2[i]);
            }
            // printf("here");
            fseek(fp, 450, 0);
            // printf("cnt = %d ss", cnt) ;
            int encnt = numberEncryption(cnt - 1);
            fprintf(fp, "%d ", encnt);
            for (int i = 0; i < cnt; i++)
            {
                if (strcmp(groups2[i], filename) != 0)
                {
                    stringEncryption(groups2[i]);
                    fprintf(fp, "%s ", groups2[i]);
                }
            }
            // printf("here2");
            fseek(fp, 400, 0);
            cnt = 0;
            fscanf(fp, "%d ", &cnt);
            cnt = numberDecryption(cnt);
            char groups3[cnt + 1][20];
            for (int i = 0; i < cnt; i++)
            {
                fscanf(fp, "%s ", groups3[i]);
                stringDecryption(groups3[i]);
            }
            strcpy(groups3[cnt], "");
            strcpy(groups3[cnt], filename);

            fseek(fp, 400, 0);
            cnt++;

            enCnt = numberEncryption(cnt);
            fprintf(fp, "%d ", enCnt);
            for (int i = 0; i < cnt; i++)
            {
                stringEncryption(groups3[i]);
                fprintf(fp, "%s ", groups3[i]);
            }
            fclose(fp);
            return;
        }
        else if (choice == 7)
        {
            strcpy(file, "");
            strcat(file, "Groups/");
            strcat(file, filename);

            FILE *fp = fopen(file, "r+");
            fseek(fp, 0, 0);
            int member, mod;
            fscanf(fp, "%d\n%d\n", &member, &mod);
            mod = numberDecryption(mod);
            if (mod == 1)
            {
                printf("Your current mode : Addmin can send message only \n");
            }
            else
            {
                printf("Your current mode : All can send message \n");
            }

            printf("Enter 1 to change the mode, otherwise enter any number to stay on same mode  \n");
            int ch;
            scanf("%d", &ch);
            if (ch == 1)
            {
                if (mod == 1)
                {
                    mod = 0;
                }
                else
                {
                    mod = 1;
                }
                printf("Mod changed successfully !!! \n");
            }
            // printf("mode : %d st\n", mod);
            fseek(fp, 0, 0);
            mod = numberEncryption(mod);
            fprintf(fp, "%d\n%d\n", member, mod);
            fclose(fp);
        }
        else if (choice == 8)
        {
            break;
        }
        else
        {
            printf("Enter valid choice !!! \n");
        }
    }
}

void userView(graph *g, int t, char *filename)
{

    printf("   ---    Welcome to %s Group Member %s    ---    \n", filename, g->arr[t]->id);
    char file[20];
    strcpy(file, "");
    strcat(file, "Groups/");
    strcat(file, filename);

    FILE *fp = fopen(file, "r+");
    if (!fp)
    {
        printf("Error in file opening \n");
        return;
    }

    int members, adminMode, admin;
    fscanf(fp, "%d\n%d\n%d ", &members, &adminMode, &admin);
    members = numberDecryption(members);
    adminMode = numberDecryption(adminMode);
    admin = numberDecryption(admin);

    fclose(fp);

    while (1)
    {
        printf("Enter \n0. To change group name \n1. To send message on group\n2. To view messages on group \n3. To view Participants \n4. To Exit from the group \n5. To leave from this page \n");
        int choice = 0;
        scanf("%d", &choice);
        if (choice == 0)
        {
            // changing group's name
            // change actual file name
            // update file name in member's file
            char newName[20];
            strcpy(newName, "");
            strcat(newName, "Groups/");
            char name[20];
            printf("Enter new name for group \n");
            scanf("%s", name);
            strcat(newName, name);

            strcpy(file, "");
            strcat(file, "Groups/");
            strcat(file, filename);
            // printf("%s filme\n", filename);
            if (rename(file, newName) == 0)
            {
                printf("File renamed successfully.\n");
            }
            else
            {
                printf("File rename failed.\n");
                continue;
            }

            // strcpy(file, "");
            // strcat(file, "Groups/");
            // strcat(file, filename);

            fp = fopen(newName, "r+");
            if (!fp)
            {
                printf("Error in file opening \n");
                rename(newName, file);
                return;
            }
            int members, adminMode;
            members = numberDecryption(members);
            adminMode = numberDecryption(adminMode);
            fscanf(fp, "%d\n%d\n", &members, &adminMode);
            int memberSuffix[members + 1];
            int temp;
            for (int i = 0; i < members; i++)
            {
                fscanf(fp, "%d ", &temp);
                memberSuffix[i] = numberDecryption(temp);
            }

            fclose(fp);

            for (int i = 0; i < members; i++)
            {
                strcpy(file, "");
                strcat(file, "folder/");
                int userIndex = memberSuffix[i];
                strcat(file, g->arr[userIndex]->id);
                fp = fopen(file, "r+");
                if (!fp)
                {
                    printf("Error in file opening while changing group name in participants file \n");
                    rename(newName, file) == 0;
                    return;
                }
                if (i == 0)
                {
                    fseek(fp, 400, 0);
                    int n;
                    fscanf(fp, "%d ", &n);
                    n = numberDecryption(n);
                    char groups[n][20];
                    for (int i = 0; i < n; i++)
                    {
                        fscanf(fp, "%s ", groups[i]);
                        stringDecryption(groups[i]);

                        // printf("filename : %s in main %s\n", filename, groups[i]);
                        // checking purpose

                        if (strcmp(filename, groups[i]) == 0)
                        {
                            strcpy(groups[i], "");
                            strcat(groups[i], name);
                            // strcpy(filename, "");
                            // strcat(filename, name);
                        }
                    }
                    fseek(fp, 400, 0);
                    int encn = numberEncryption(n);
                    fprintf(fp, "%d ", encn);
                    for (int i = 0; i < n; i++)
                    {
                        stringEncryption(groups[i]);
                        fprintf(fp, "%s ", groups[i]);
                    }
                }
                else
                {
                    fseek(fp, 450, 0);
                    int n;
                    fscanf(fp, "%d ", &n);
                    n = numberDecryption(n);
                    char groups[n][20];
                    for (int i = 0; i < n; i++)
                    {
                        fscanf(fp, "%s ", groups[i]);
                        stringDecryption(groups[i]);
                        // printf("%s %sfile\n", filename, groups[i]);
                        if (strcmp(filename, groups[i]) == 0)
                        {
                            strcpy(groups[i], "");
                            strcat(groups[i], name);
                        }
                    }
                    fseek(fp, 450, 0);
                    int encN = numberEncryption(n);
                    fprintf(fp, "%d ", encN);
                    for (int i = 0; i < n; i++)
                    {
                        stringEncryption(groups[i]);
                        fprintf(fp, "%s ", groups[i]);
                    }
                }
                fclose(fp);
            }
            strcpy(filename, "");
            strcat(filename, name);
        }
        else if (choice == 1)
        {

            strcpy(file, "");
            strcat(file, "Groups/");
            strcat(file, filename);

            fp = fopen(file, "r+");
            if (!fp)
            {
                printf("Can't open file !!! \n");
                continue;
            }
            fseek(fp, 0, 0);
            int members = 0, mode = 0;
            fscanf(fp, "%d\n%d\n", &members, &mode);
            members = numberDecryption(members);
            mode = numberDecryption(mode);

            if (mode == 1)
            {
                printf("Admin only can send message !!! \n");
                continue;
            }

            char *str = (char *)malloc(sizeof(char) * 2000);
            if (!str)
            {
                printf("Can't alloc memory !!! \n");
                continue;
            }

            strcpy(str, "");

            fseek(fp, GroupMessagesStart, 0);
            fgets(str, GroupMessagesSize, fp);
            stringDecryption(str);
            // strcat(str, "$");
            head *h = g->arr[t];
            strcat(str, h->id);
            strcat(str, " : ");
            printf("Enter the text message \n");
            char *text = (char *)(malloc(sizeof(char) * 500));
            if (!text)
            {
                free(str);
                fclose(fp);
                printf("Memory not allocated \n");
                continue;
            }
            scanf(" %[^\n]", text);

            strcat(str, text);
            strcat(str, "$");

            fseek(fp, GroupMessagesStart, 0);
            stringEncryption(str);
            fprintf(fp, "%s", str);
            fputc('\0', fp);
            fclose(fp);
            free(str);
        }
        else if (choice == 2)
        {
            char *str = (char *)malloc(sizeof(char) * 2000);
            if (!str)
            {
                printf("Can't alloc memory !!! \n");
                continue;
            }
            strcpy(file, "");
            strcat(file, "Groups/");
            strcat(file, filename);

            fp = fopen(file, "r+");
            if (!fp)
            {
                printf("Can't open file !!! \n");
                free(str);
                continue;
            }

            fseek(fp, GroupMessagesStart, 0);
            fgets(str, GroupMessagesSize, fp);
            stringDecryption(str);

            for (int i = 0; i < strlen(str); i++)
            {
                if (str[i] == '$')
                {
                    printf("\n");
                }
                else
                {
                    printf("%c", str[i]);
                }
            }

            fclose(fp);
        }
        else if (choice == 3)
        {
            strcpy(file, "");
            strcat(file, "Groups/");
            strcat(file, filename);

            fp = fopen(file, "r+");
            if (!fp)
            {
                printf("Error in file opening \n");
                return;
            }

            fscanf(fp, "%d\n%d\n", &members, &adminMode);
            members = numberDecryption(members);

            int arr[members];
            for (int i = 0; i < members; i++)
            {
                fscanf(fp, "%d ", arr + i);
                arr[i] = numberDecryption(arr[i]);
            }

            for (int i = 0; i < members; i++)
            {
                printf("%d. %s \n", i, g->arr[arr[i]]->id);
            }

            fclose(fp);
        }
        else if (choice == 4)
        {
            // simply remove from both main file and subfile

            printf("Do you really want to exit from this group ? \nPlease confirm by pressing 1 \n");
            int ex = 0;
            scanf("%d", &ex);
            if (ex != 1)
            {
                continue;
            }
            strcpy(file, "");
            strcat(file, "Groups/");
            strcat(file, filename);

            fp = fopen(file, "r+");
            if (!fp)
            {
                printf("Error in file opening \n");
                return;
            }
            fscanf(fp, "%d\n%d\n", &members, &adminMode);
            members = numberDecryption(members);

            int arr[members];
            for (int i = 0; i < members; i++)
            {
                fscanf(fp, "%d ", arr + i);
                arr[i] = numberDecryption(arr[i]);
            }

            fseek(fp, 0, 0);
            int enMemeber = numberEncryption(members - 1);
            fprintf(fp, "%d\n%d\n", enMemeber, adminMode);
            for (int i = 0; i < members; i++)
            {
                if (arr[i] == t)
                {
                    continue;
                }
                arr[i] = numberEncryption(arr[i]);
                fprintf(fp, "%d ", arr[i]);
            }
            fclose(fp);

            // changing in previous parti. file

            strcpy(file, "");
            strcat(file, "folder/");
            strcat(file, g->arr[t]->id);

            fp = fopen(file, "r+");
            if (!fp)
            {
                printf("Error in file opening \n");
                return;
            }

            fseek(fp, 450, 0);
            int cnt;
            fscanf(fp, "%d ", &cnt);
            cnt = numberDecryption(cnt);
            char groups[cnt][20];
            for (int i = 0; i < cnt; i++)
            {
                fscanf(fp, "%s ", groups[i]);
                stringDecryption(groups[i]);
            }

            fseek(fp, 450, 0);
            int enCnt = numberEncryption(cnt - 1);
            fprintf(fp, "%d ", enCnt);
            for (int i = 0; i < cnt; i++)
            {
                if (strcmp(groups[i], filename) != 0)
                {
                    stringEncryption(groups[i]);
                    fprintf(fp, "%s ", groups[i]);
                }
            }

            fclose(fp);

            return;
        }
        else if (choice == 5)
        {
            return;
        }
        else
        {
            printf("Enter valid choice !!! \n");
        }
    }
}