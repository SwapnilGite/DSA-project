typedef struct node node;
typedef struct node* bst; //typedefining the node*
typedef struct queueNode
{
    bst data;
    struct queueNode *next;
}queue;

void enqueue(bst, queue**, queue**);
bst dequeue(queue**, queue**);