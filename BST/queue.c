#include<stdio.h>
#include<stdlib.h>
#include"queue.h"
#include"bst.h"
/* Function to add a node to the Queue */
void enqueue(bst node, queue **first, queue **rear)
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

bst dequeue(queue **first, queue **rear)
{
    queue *temp;
    bst retVal;
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