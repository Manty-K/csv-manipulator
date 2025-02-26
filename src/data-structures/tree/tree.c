#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

TREENODE *createTreeNode(void *data, unsigned int childCount)
{
    TREENODE *node = malloc(sizeof(TREENODE));

    if (node == NULL)
    {
        fprintf(stderr, "Creating TreeNode failed\n");
        return NULL;
    }

    node->data = data;
    node->childCount = childCount;
    node->children = (TREENODE **)calloc(childCount, sizeof(TREENODE *));

    return node;
}

void _displayTreeHelper(TREENODE *node, unsigned int level, PrintFunc printFunc)
{
    if (node == NULL)
    {
        return;
    }

    for (unsigned int i = 0; i < level; i++)
    {
        printf("\t");
    }

    printFunc(node->data);
    printf("\n");

    for (unsigned int i = 0; i < node->childCount; i++)
    {
        _displayTreeHelper(node->children[i], level + 1, printFunc);
    }
}

void displayTree(TREENODE *node, PrintFunc printFunc)
{
    _displayTreeHelper(node, 0, printFunc);
}

void freeTree(TREENODE *node, FreeFunc freeFunc)
{
    if (node == NULL)
        return;

    for (unsigned int i = 0; i < node->childCount; i++)
    {
        freeTree(node->children[i], freeFunc);
    }
    free(node->children);
    if (freeFunc)
    {
        freeFunc(node->data);
    }
    free(node);
}