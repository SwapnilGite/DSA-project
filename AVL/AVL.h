typedef struct node
{
    int dispnum;        // label to be used when generating image for tree
    char website[18];   // name of the website
    char ipAddr[16];    // ip address of the website
    struct node *left;  // left child
    struct node *right; // right child
    int number;         // number of searches
    struct node *parent;
    int bFactor;
} node;
typedef struct node *AVL;
void initAVL(AVL *t);
node *newNode(char *ipaddress,char *website);
void preorder(AVL t);
int height(AVL t);
void updateBF(AVL t);
node *imbalance_node(AVL t);
void RRimbalance(AVL *root, AVL *t);
void LLimbalance(AVL *root, AVL *t);
void RLimbalance(AVL *root, AVL *t);
void LRimbalance(AVL *root, AVL *t);
void insertNode(AVL *root, char *ipaddress,char *website);
void search(AVL root,char *ipaddress);
