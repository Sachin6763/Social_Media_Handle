
#include "login_page.h"
#include <string.h>
#include <stdlib.h>

int logi(graph *g)
{
    while (1)
    {
        printf("Enter \n1. To Login \n2. To Signup \n");
        int choice;
        scanf("%d", &choice);
        if (choice == 1)
        {
            while (1)
            {
                char id1[20], pass1[20];
                printf("Enter your Id \n");
                scanf("%s", id1);
                int status = checkIdExit(g, id1);
                if (status == -1)
                {
                    printf("Id doesn't exit !!! \n");
                    break;
                }
                else
                {
                    printf("Enter the password \n");
                    scanf("%s", pass1);
                    if (strcmp(g->arr[status]->pass, pass1) == 0)
                    {
                        printf("\nlogging ...\n\n");
                        return status;
                    }
                    printf("your password is incorrect \nEnter 1 for back \n2 for login again\n");
                    int option;
                    scanf("%d", &option);
                    if (option == 1)
                        break;
                }

                // search connections
                // true
                // next page
                // false
                // continue with this page
            }
        }
        else if (choice == 2)
        {
            printf("Enter the id \n");
            char id[20];
            int exit = 0;
            while (1)
            {
                scanf("%s", id);

                int status1 = isValidId(id);
                int status2 = checkIdExit(g, id);

                if (status1 == -1)
                {
                    printf("Enter strong Id having following protocols \n1. Cannot start with no. \n2. Having symbols in given range i.e. alphanumericals and special character including ('!', '@', '#', '$', '%', '^', '&','*') . \n3. Length should be at least 8 and cannot grater than 16. \n");
                    printf("If you want to exit from this page press -1 please ... otherwise place any number you like to stay on same\n");
                    exit = 0;
                    scanf("%d", &exit);
                    if (exit == -1)
                        break;
                }
                else if (status2 != -1)
                {
                    printf("Enter another Id. This is is taken by some user. !!! \n");
                    continue;
                }
                else
                {
                    break;
                }
            }
            if (exit != -1)
            {

                printf("Enter the password \n");
                char pass[20];
                int status = -1;
                while (1)
                {
                    scanf("%s", pass);
                    status = isValidPassword(pass);
                    if (status == -1)
                    {
                        printf("Enter strong password having following protocols \n1. Cannot start with no. \n2. Having at least one uppercase symbol. \n3. Having one non-alphanumberical symbol.\n4. Remaing all should be alphabets only. \n5. Contain exactly 8 letters\n");
                        printf("If you want to exit from this page press -1 please ... otherwise place any number you like to stay on same\n");
                        exit = 0;
                        scanf("%d", &exit);
                        if (exit == -1)
                            break;
                    }
                    else
                    {
                        break;
                    }
                }
                if (status != -1)
                {
                    init_id(g, id, pass);
                    printf("Congratulations !!! You have successfully created your account !!! Please login again now. \n");
                }
            }
            // insert node
        }
    }

    return -1;
}

void afterLogin(graph *g, int t)
{

    while (1)
    {
        printf("Enter \n0 To see Profile \n1 To see connections \n2 Upload post \n3 Message particular connection \n4 check messages \n5 see posts of other connections \n6 Send request to make new connections \n7 To see connection requests  \n8 BroadCasting the Message to multiple connections\n9 To remove particular acc form connection\n10 To check Groups \n11 To logout\n");

        int activity = 0;
        scanf("%d", &activity);
        if (activity == 0)
        {
            int signout = seeProfile(&g, t);
            if (signout == 1)
            {
                return;
            }
        }
        else if (activity == 1)
        {
            seeConnections(*g, t);
        }
        else if (activity == 2)
        {
            uploadPost(g, t);
        }
        else if (activity == 3)
        {
            privateMessage(g, t);
        }
        else if (activity == 4)
        {
            checkMessages(g, t);
        }
        else if (activity == 5)
        {
            checkPost(g, t);
        }
        else if (activity == 6)
        {
            makeNewConnections(g, t);
        }
        else if (activity == 7)
        {
            seeRequests(g, t);
        }
        else if (activity == 8)
        {
            broadCast(g, t);
        }
        else if (activity == 9)
        {
            removeChoice(g, t);
        }
        else if (activity == 10)
        {
            // checkGroups
            // choice 1 : see messages
            viewGroup(g, t);
            // choice 2 : do message
            // choice 3 : view participents
            // choice 4 : send request to participents

            // admine -> remove someone from group
            //        -> delete history
        }
        else if (activity == 11)
        {
            return;
        }
        else
        {
            printf("Enter valid choice");
        }
    }
}