#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "splayTree.h"
#include "visualizeTree.h"

int main()
{
    sTree root;
    char ipAddress[16] = {0};
    char siteName[18] = {0};
    int choice;
    FILE *fptr;
    fptr = fopen("input.txt", "r");
    while (1)
    {
        printf("1.Init.\n");
        printf("2.Insert into Splay Tree.\n");
        printf("3.Search In the Splay Tree.\n");
        printf("4.Display.\n");
        printf("5.Exit.\n");
        scanf("%d", &choice);

        if (choice == 1)
        {
            init_Tree(&root);
            printf("<-------Tree Initialized------>\n");
        }
        else if (choice == 2)
        {

            for (int i = 0; i < 30; i++)
            {
                fscanf(fptr, "%s %s\n", siteName, ipAddress);
                insert(&root, ipAddress, siteName);
                memset(ipAddress, 0, sizeof(ipAddress));
                memset(siteName, 0, sizeof(siteName));
            }
            fclose(fptr);
            printf("<----------Elements Inserted------------->\n");
            preorder(root);
        }
        else if (choice == 3)
        {
            printf("Enter the Ip Address: ");
            scanf(" %s", ipAddress);
            search(&root, ipAddress);
            preorder(root);
        }
        else if (choice == 4)
        {
            displayTree(root);
            printf("\nImage Generated\n");
        }
        else if (choice == 5)
        {
            exit(0);
        }
    }

    return 0;
}