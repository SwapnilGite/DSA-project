#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"bst.h"
#include"visualizeTree.h"

int main()
{	

    bst root;
    char ipAddress[16] = {0};
    char siteName[18] = {0};
    FILE *fptr;
    fptr = fopen("input.txt", "r");
	 while (1)
    {
        printf("1.Init BST 2.Insert Nodes  3.Search  4.Display 5.Quit\n");
        printf("Enter Function to perform: ");
        int task;
        
        scanf("%d", &task);

        if (task == 1)
        {
            initBST(&root);
            printf("Root Initialized\n");
        }

        else if (task == 2)
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

        else if (task == 3)
        {
            printf("Enter IP address to search: ");
            scanf("%s",ipAddress);
            search(root,ipAddress);
            preorder(root);
        }

        else if (task == 4)
        {
            displayTree(root);
            printf("Image Generated\n");
        }

        else if (task == 5)
        {
            printf("Program Exited\n");
            exit(0);
        }

    }

    return 0;
}