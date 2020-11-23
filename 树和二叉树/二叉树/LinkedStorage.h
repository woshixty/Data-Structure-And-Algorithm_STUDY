/**
 * 链式存储二叉树
 */

#ifndef LinkedStorage

#include<stdio.h>
#define LinkedStorage
#define MAX_TREE_SIZE

typedef struct BiTNode {
    int data;
    struct BiTNode* lchild;
    struct BiTNode* rchild;
}BiTNode, * Bitree;

void printHello() {
    printf("hello world");
}

#endif