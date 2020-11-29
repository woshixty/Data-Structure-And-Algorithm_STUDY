#include<stdlib.h>
#include<stdio.h>

typedef enum PointerTag { Link, Thread }; // Link == 0, Thread == 1 :线索

//线索二叉树的存储结构
typedef struct BiThrNode {
    int data;
    struct BiThrNode *lchild, *rchild;  //左右孩子指针
    PointerTag LTag, RTag;
}BiThrNode, *BiThrTree;

int main() {
    
}