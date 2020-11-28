/**
 * 链式存储二叉树
 */

#ifndef LinkedStorage
#define MAX_TREE_SIZE

typedef struct BiTNode {
    char data;
    struct BiTNode* lchild;
    struct BiTNode* rchild;
}BiTNode, * Bitree;

#endif