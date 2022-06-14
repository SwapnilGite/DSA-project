typedef struct node node;
typedef struct node* AVL; //typedefining the node*
typedef struct queueNode
{
    AVL data;
    struct queueNode *next;
}queue;

void enqueue(AVL, queue**, queue**);
AVL dequeue(queue**, queue**);