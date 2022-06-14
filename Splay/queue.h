typedef struct node node;
typedef struct node* sTree; //typedefining the node*
typedef struct queueNode
{
    sTree data;
    struct queueNode *next;
}queue;

void enqueue(sTree, queue**, queue**);
sTree dequeue(queue**, queue**);