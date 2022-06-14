#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AVL.h"
int count = 0;

void initAVL(AVL *t) // init avl
{
    *t = NULL;
    return;
}
node *newNode(char *ipaddress, char *website) // create a tree node
{
    node *nn = (node *)malloc(sizeof(node));
    nn->bFactor = 0;
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
void preorder(AVL root)
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
int height(AVL t) // returns height of the tree
{
    if (!t)
    {
        return 0;
    }
    int x = height(t->left);
    int y = height(t->right);

    return x > y ? x + 1 : y + 1;
}
void updateBF(AVL t) // returns the balance factor
{
    if (!t)
    {
        return;
    }
    t->bFactor = height(t->left) - height(t->right);
    updateBF(t->parent);
}
node *imbalance_node(AVL t) // finds and returns the imbalanced node
{
    node *p = t;
    while (p)
    {
        if (abs(p->bFactor) > 1)
        {
            break;
        }
        else
        {
            p = p->parent;
        }
    }
    return p;
}
void RRimbalance(AVL *root, AVL *t)
{
    AVL A = (*t);
    AVL B = ((*t)->right);
    AVL BL = B->left;
    B->left = A;
    A->right = BL;
    B->parent = A->parent;
    if (BL)
        BL->parent = A;
    A->parent = B;
    B->bFactor = 0;
    A->bFactor = 0;
    if ((*root) == A)
    {
        (*root) = B;
        return;
    }
    if (B->parent->left == A)
        B->parent->left = B;
    else
        B->parent->right = B;
    return;
}
void LLimbalance(AVL *root, AVL *t)
{
    AVL A = (*t);
    AVL B = ((*t)->left);
    AVL BR = B->right;
    B->right = A;
    A->left = BR;
    B->parent = A->parent;
    if (BR)
        BR->parent = A;
    A->parent = B;
    B->bFactor = 0;
    A->bFactor = 0;
    if ((*root) == A)
    {
        (*root) = B;
        return;
    }
    if (B->parent->left == A)
        B->parent->left = B;
    else
        B->parent->right = B;
    return;
}
void RLimbalance(AVL *root, AVL *t)
{
    LLimbalance(root, &(*t)->right);
    RRimbalance(root, t);
}
void LRimbalance(AVL *root, AVL *t)
{
    RRimbalance(root, &(*t)->left);
    LLimbalance(root, t);
}
void insertNode(AVL *root, char *ipaddress, char *website)
{
    AVL newnode = newNode(ipaddress, website);
    if (!newnode)
        return;

    // strcpy(newnode->month, month);
    if (!(*root))
    {
        (*root) = newnode;
        return;
    }
    AVL p, q;
    q = NULL;
    p = (*root);
    while (p)
    {
        q = p;
        if (compare(p->ipAddr, ipaddress) > 0)
            p = p->left;
        else if (compare(p->ipAddr, ipaddress) < 0)
            p = p->right;
        else
            return;
    }

    newnode->parent = q;
    if (compare(q->ipAddr, ipaddress) > 0)
        q->left = newnode;
    else
        q->right = newnode;

    updateBF(q);
    AVL unbal = NULL;
    unbal = imbalance_node(q);
    do
    {
        if (!unbal)
            return;
        AVL parentofunbal = unbal->parent;

        if (unbal->bFactor == 2 && unbal->left->bFactor == 1)
            LLimbalance(root, &unbal);
        else if (unbal->bFactor == 2 && unbal->left->bFactor == -1)
            LRimbalance(root, &unbal);
        else if (unbal->bFactor == -2 && unbal->right->bFactor == 1)
            RLimbalance(root, &unbal);
        else if (unbal->bFactor == -2 && unbal->right->bFactor == -1)
        {
            RRimbalance(root, &unbal);
        }

        updateBF(parentofunbal);
        unbal = imbalance_node(parentofunbal);
    } while (unbal);

    return;
}
void search(AVL root, char *ipaddress)
{
    if (root == NULL)
    {
        return;
    }
    if (strcmp(root->ipAddr, ipaddress) == 0)
    {
        printf("<----------------Node Found------------->\n");
        root->number++;
        return;
    }
    else if (compare(root->ipAddr, ipaddress) > 0)
    {
        search(root->left, ipaddress);
    }
    else if (compare(root->ipAddr, ipaddress) < 0)
    {
        search(root->right, ipaddress);
    }
}