// init
#include <stdio.h>
#include <unistd.h>
// #include "graphs.h"
#include "../header_files/login_page.h"

int main()
{
    graph g;
    graph *gp = &g;

    if (access("main.txt", F_OK) == 0)
    {
        printf("File exists.\n");
        init("main.txt", gp); // create graph and files for indivisual user
    }
    else
    {
        FILE *fp = fopen("main.txt", "w");
        fseek(fp, 0, 0);
        int initialUsers = 0;
        int en = numberEncryption(initialUsers);
        fprintf(fp, "%d ", en);
        fclose(fp);
        init("main.txt", gp);
        // printf("File does not exist.\n");
    }

    // printf("hii");
    // init_files(gp);
    // printGraph(gp);

    while (1)
    {
        int t = logi(&g);
        afterLogin(&g, t);
    }

    return 0;
}
