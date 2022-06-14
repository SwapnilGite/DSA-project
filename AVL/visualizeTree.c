#include <stdio.h>
#include <stdlib.h>
#include "visualizeTree.h"
#include "AVL.h"
#include "queue.h"
void displayTree(AVL root)
{
    if (root == NULL)
    {
        printf("\nTree Empty !");
        return;
    }

    else
    {
        FILE *fileOp = fopen("temp.dot", "w");

        fprintf(fileOp, "digraph AVL\n{\n");
        // Creating the Label at the Bottom
        fprintf(fileOp, "label = \"IP Network using AVL\"\n");

        // Format to write to temp.dot file , Writing root with red color
        fprintf(fileOp, "%d [label=\"%s\\n%s\\nVisits=%d\", shape = box, color = \"#ff0000\"];\n", root->dispnum, root->ipAddr, root->website, root->number);

        int nullCount = 0;

        // Writing all left children of root in Temp.dot file
        preorderVisual(fileOp, root->left);

        // Writing all right children of root in Temp.dot file
        preorderVisual(fileOp, root->right);

        // Creating the pointers to the front and the rear of the Queue
        queue *front, *rear;
        front = rear = NULL;

        // Adding the Root to the Queue
        enqueue(root, &front, &rear);

        while (front != NULL)
        {
            AVL current = dequeue(&front, &rear);

            /*
            Writing the Leaf Nodes to the File.
            Checking if there are no children to the node.
            The leaf nodes have a blue border
            */
            if ((!current->left) && (!current->right) && (current != root))
            {
                fprintf(fileOp, "%d[color = \"blue\"];", current->dispnum);
                fprintf(fileOp, "%d->%d;", current->dispnum, current->parent->dispnum);
            }

            /* Checking if the Left Child Exists
               If it exists then we are adding it to the queue
               for further steps
            */
            if (current->left)
            {
                if (current->parent == NULL)
                {
                    // printf("root made\n");
                    fprintf(fileOp, "%d -> %d ;\n", current->dispnum, current->left->dispnum);
                    enqueue(current->left, &front, &rear);
                }
                else
                {
                    fprintf(fileOp, "%d -> %d;\n", current->dispnum, current->left->dispnum);
                    fprintf(fileOp, "%d -> %d;\n", current->dispnum, current->parent->dispnum);
                    enqueue(current->left, &front, &rear);
                }
            }

            else
            {
                nullCount++;
                fprintf(fileOp, "NULL%d [shape=point];\n %d -> NULL%d;\n", nullCount, current->dispnum, nullCount);
            }

            /* Checking if the Right Child Exists
               If it exists then we are adding it to the queue
               for further steps
            */
            if (current->right)
            {
                if (current->parent == NULL)
                {
                    fprintf(fileOp, "%d -> %d;\n", current->dispnum, current->right->dispnum);
                    enqueue(current->right, &front, &rear);
                }
                else
                {
                    fprintf(fileOp, "%d -> %d;\n", current->dispnum, current->right->dispnum);
                    fprintf(fileOp, "%d -> %d;\n", current->dispnum, current->parent->dispnum);
                    enqueue(current->right, &front, &rear);
                }
            }

            else
            {
                nullCount++;
                fprintf(fileOp, "NULL%d [shape=point];\n %d -> NULL%d;\n", nullCount, current->dispnum, nullCount);
            }
        }

        fprintf(fileOp, "\n}");
        fclose(fileOp);

        system("dot -Tpng temp.dot -o AVL.png");
        system("BST.png");
    }
}

// preorder traversal
void preorderVisual(FILE *fileOp, AVL t)
{
    if (t != NULL)
    {
        fprintf(fileOp, "%d [label=\"%s\\n%s\\nVisits=%d\"];\n", t->dispnum, t->ipAddr, t->website, t->number);
        preorderVisual(fileOp, t->left);
        preorderVisual(fileOp, t->right);
    }
}
