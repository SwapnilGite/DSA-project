#include<stdio.h>
#include<stdlib.h>
#include"queue.h"
#include"splayTree.h"
/* Function to add a node to the Queue */
void enqueue(sTree node, queue **first, queue **rear)
{
    queue *link = (queue*)malloc(sizeof(queue));
    link->data = node;
    link->next = NULL;

    if (*first == NULL)
    {
        *first = *rear = link;
    }

    else
    {
        (*rear)->next = link;
        (*rear) = link;
    }
}

/* Function to delete a node from the Queue */

sTree dequeue(queue **first, queue **rear)
{
    queue *temp;
    sTree retVal;
    temp = *first;

    if (temp == NULL)
    {
        return NULL;
    }

    else
    {
        retVal = temp->data;

        if ((*first) == (*rear))
        {
            (*first) = (*rear) = NULL;
        }

        else
        {
            (*first) = temp->next;
        }

        free(temp);
        return retVal;
    }
}