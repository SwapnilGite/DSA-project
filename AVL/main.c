#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AVL.h"
#include "visualizeTree.h"

int main()
{
    AVL t;
    int task;
    char ipAddress[16] = {0};
    char siteName[18] = {0};
    FILE *fptr;
    fptr = fopen("input.txt", "r");
    while (1)
    {
        printf("1.Init tree  2.Insert Nodes    3.Search    4.Display   5.Exit \n");
        printf("Enter Task to perform:\n");
        scanf("%d", &task);
        if (task == 1)
        {
            initAVL(&t);
        }
        else if (task == 2)
        {
            for (int i = 0; i < 30; i++)
            {
                fscanf(fptr, "%s %s\n", siteName, ipAddress);
                insertNode(&t, ipAddress, siteName);
                memset(ipAddress, 0, sizeof(ipAddress));
                memset(siteName, 0, sizeof(siteName));
            }
            fclose(fptr);
            printf("<----------Elements Inserted------------->\n");
            preorder(t);
        }
        else if (task == 3)
        {
            printf("Enter IP address to search: ");
            scanf("%s",ipAddress);
            search(t,ipAddress);
            preorder(t);
        }

        else if (task == 4)
        {
            displayTree(t);
            printf("Image Generated\n");
        }
        else if (task == 5)
        {
            printf("Program Exited\n");
            exit(0);
        }
    }
}