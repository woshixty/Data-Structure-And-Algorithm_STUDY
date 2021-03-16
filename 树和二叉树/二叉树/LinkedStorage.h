/**
 * 链式存储二叉树
 */

#ifndef LinkedStorage
#define LinkedStorage

typedef struct BiTNode {
    char data;
    struct BiTNode* lchild;
    struct BiTNode* rchild;
}BiTNode, * Bitree;

#endif