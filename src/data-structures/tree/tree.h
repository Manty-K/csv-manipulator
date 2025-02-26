#ifndef TREE_H
typedef struct treeNode
{

    void *data;
    struct treeNode **children;
    unsigned int childCount;

} TREENODE;

typedef void (*PrintFunc)(void *data);
typedef void (*FreeFunc)(void *data);

TREENODE *createTreeNode(void *data, unsigned int childCount);

void displayTree(TREENODE *node, PrintFunc);
void freeTree(TREENODE *node, FreeFunc freeFunc);
#endif