typedef struct node
{
  int dispnum; //label to be used when generating image for tree
  char website[18]; // name of the website
  char ipAddr[16]; // ip address of the website
  struct node *left; // left child
  struct node *right; // right child
  int number; // number of searches
  struct node* parent;
}node;

typedef struct node* sTree;
void init_Tree(sTree *root);
sTree newNode(char *ipaddress, char *name);
void rightRotation(sTree* root,sTree node);
void leftRotation(sTree* root,sTree node);
void Splay(sTree* root,sTree node);
void insert(sTree *root,char *ipaddress, char *name);
void preorder(sTree root);
void search(sTree* root,char *ipAddress);