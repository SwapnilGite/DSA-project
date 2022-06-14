typedef struct node // for BST tree
{
    int dispnum;        // label to be used when generating image for tree
    char website[18];   // name of the website
    char ipAddr[16];    // ip address of the website
    struct node *left;  // left child
    struct node *right; // right child
    int number;         // number of searches
    struct node *parent;
} node;
typedef struct node *bst;

void initBST(bst *root);
void insert(bst *root, char* ipaddress, char *name);
void search(bst root, char* ipaddress);
// void Inorder(bst root);
void preorder(bst root);
