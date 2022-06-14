#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "splayTree.h"
int count = 0; // count used for labelling while generating a png image of tree

void init_Tree(sTree *root) // function to init tree
{
    *root = NULL;
    return;
}

sTree newNode(char *ipaddress, char *name)
{
    sTree newNode = (sTree)malloc(sizeof(node)); // allocating memory to the node
    newNode->number = 0;                         // initializing visited number
    newNode->dispnum = count + 1;                // label to be used while displaying tree
    count++;
    newNode->parent = NULL; // initialized number of searches to 0
    newNode->left = newNode->right = NULL;
    strcpy(newNode->website, name);     // stored website name
    strcpy(newNode->ipAddr, ipaddress); // stored ipAddress
    return newNode;
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

void rightRotation(sTree *root, sTree node) // right rotation
{
    sTree temp = node->left;
    node->left = temp->right;
    if (temp->right != NULL)
    {
        temp->right->parent = node;
    }
    temp->parent = node->parent;
    if (node->parent == NULL)
    {
        *root = temp;
    }
    else if (node == node->parent->right)
    {
        node->parent->right = temp;
    }
    else
    {
        node->parent->left = temp;
    }
    temp->right = node;
    node->parent = temp;
    return;
}

void leftRotation(sTree *root, sTree node) // left rotation
{
    sTree temp = node->right;
    node->right = temp->left;
    if (temp->left != NULL)
    {
        temp->left->parent = node;
    }
    temp->parent = node->parent;
    if (node->parent == NULL)
    {
        *root = temp;
    }
    else if (node == node->parent->left)
    {
        node->parent->left = temp;
    }
    else
    {
        node->parent->right = temp;
    }
    temp->left = node;
    node->parent = temp;
    return;
}

void Splay(sTree *root, sTree node) // splay operation for the tree
{
    sTree parent;
    sTree grandParent;
    while (node->parent != NULL)
    {
        if (node->parent == *root)
        {
            if (node == node->parent->left)
            {
                rightRotation(root, node->parent);
            }
            else
            {
                leftRotation(root, node->parent);
            }
        }
        else
        {
            parent = node->parent;
            grandParent = parent->parent;
            if (node == node->parent->left && parent == parent->parent->left)
            {
                rightRotation(root, grandParent);
                rightRotation(root, parent);
            }
            else if (node == node->parent->right && parent == node->parent->parent->right)
            {
                leftRotation(root, grandParent);
                leftRotation(root, parent);
            }
            else if (node == node->parent->right && parent == parent->parent->left)
            {
                leftRotation(root, parent);
                rightRotation(root, grandParent);
            }
            else
            {
                rightRotation(root, parent);
                leftRotation(root, grandParent);
            }
        }
    }
    return;
}

void insert(sTree *root, char *ipaddress, char *name) // insert ,same as BST insertion
{
    sTree temp = *root;
    sTree prev = NULL;
    sTree node = newNode(ipaddress, name);
    while (temp != NULL)
    {
        prev = temp;

        if (compare(temp->ipAddr, node->ipAddr) > 0)
        {
            temp = temp->left;
        }
        else if (compare(temp->ipAddr, node->ipAddr) < 0)
        {
            temp = temp->right;
        }
    }
    node->parent = prev;
    if (prev == NULL)
    {
        *root = node;
    }
    else if (compare(node->ipAddr, prev->ipAddr) > 0)
    {
        prev->right = node;
    }
    else if (compare(node->ipAddr, prev->ipAddr) < 0)
    {
        prev->left = node;
    }

    Splay(root, node); // splaying newly inserted node
    return;
}

void preorder(sTree root)
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
sTree searchTree(sTree root, char *ipAddress) //returns pointer to searched node
{
    if (root == NULL)
    {
        return NULL;
    }
    if (strcmp(root->ipAddr, ipAddress) == 0)
    {
        return root;
    }
    else if (compare(root->ipAddr, ipAddress) > 0)
    {
        searchTree(root->left, ipAddress);
    }
    else if (compare(root->ipAddr, ipAddress) < 0)
    {
        searchTree(root->right, ipAddress);
    }

    // return NULL;
}
void search(sTree *root, char *ipAddress) //searches for the node and splays it to the root
{
    sTree node = searchTree(*root, ipAddress);
    if (node)
    {
        Splay(root, node);
        node->number++;
        printf("\n<--------------Node Found----------------->\n");
        printf("IP Address :  %s\n", node->ipAddr);
        printf("WebSite Name :  %s\n", node->website);
        printf("Number Of Visits : %d\n", node->number);
        printf("\n");
    }
    else
    {
        printf("Not Found\n");
    }
    return;
}
