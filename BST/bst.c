#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"
int count = 0;

void initBST(bst *root)
{
    *root = NULL;
    return;
}
node *newNode(char *ipaddress, char *website) // create a tree node
{
    node *nn = (node *)malloc(sizeof(node));
    // nn->bFactor = 0;
    nn->dispnum = count + 1;
    count++;
    nn->left = NULL;
    nn->right = NULL;
    nn->parent = NULL;
    strcpy(nn->website, website);
    strcpy(nn->ipAddr, ipaddress);
    return nn;
}

long long int strToInt(char *ipAddress) // converts ip adress to long long int, used to compare two ip addresses
{
    int i = 0;
    long long int ip = 0;
    while (i < strlen(ipAddress))
    {
        if (ipAddress[i] != '.')
        {
            ip = ip * 10 + (ipAddress[i] - '0');
            i++;
        }
        else
        {
            i++;
        }
    }
    return ip;
}
int compare(char *ip1, char *ip2) // comapares two ip addresses
{
    long long int intIp1, intIp2;
    int flag = 1; // assuming ip1 > ip2
    intIp1 = strToInt(ip1);
    intIp2 = strToInt(ip2);

    if ((intIp1 - intIp2) < 0)
    {
        flag = -1;
    }
    return flag;
}


void insert(bst *root, char *ipaddress, char *name)
{
    bst nn = newNode(ipaddress, name);

    if (!nn)
    {
        return;
    }

    if (*root == NULL)
    {
        *root = nn;
        return;
    }
    node *p = *root;
    node *prev = NULL;
    while (p != NULL)
    {
        prev = p;
        if (strcmp(p->ipAddr, ipaddress) == 0) // data already exist
        {
            return;
        }
        if (compare(p->ipAddr, ipaddress) > 0)
        {
            p = p->left;
        }
        else if (compare(p->ipAddr, ipaddress) < 0)
        {
            p = p->right;
        }
    }
    nn->parent = prev;
    if (compare(prev->ipAddr, ipaddress) > 0)
    {
        prev->left = nn;
    }
    else if (compare(prev->ipAddr, ipaddress) < 0)
    {
        prev->right = nn;
    }
    return;
}

void search(bst root, char *ipaddress)
{
    if (root == NULL) // if tree is empty, return 0
    {
        return ;
    }
    else if (strcmp(root->ipAddr, ipaddress) == 0)
    {
        printf("<-----------------Node Found------------>\n");
        root->number++;
        return;
    }
    else if (compare(root->ipAddr, ipaddress) > 0) // if key is less than root, then go to left
    {
        search(root->left, ipaddress);
    }
    else if (compare(root->ipAddr, ipaddress) < 0) // if key is greater then root, then move to right
    {
        search(root->right, ipaddress);
    }
}

void preorder(bst root)
{

    if (root != NULL)
    {
        printf("IP Address :  %s\n", root->ipAddr);
        printf("WebSite Name :  %s\n", root->website);
        printf("Number Of Searches for this website : %d\n", root->number);
        if (root->parent)
            printf("Parent is %s\n", root->parent->website);
        printf("\n");
        preorder(root->left);
        preorder(root->right);
    }
}

