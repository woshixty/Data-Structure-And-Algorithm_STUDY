#include"LinkedStorage.h"
#include<iostream>
#include<stdlib.h>
#include<stdio.h>

#define OK 1
#define ERROR 2
#define OVERFLOW 3

using namespace std;

//先序构造二叉树
void CreateBiTree(Bitree &Tree);
//先序输出二叉树
void BeforePrint(Bitree Tree);

int main() {
    Bitree tree = NULL;
    CreateBiTree(tree);
    BeforePrint(tree);
    return OK;
}

void CreateBiTree(Bitree &Tree) {
    //先序输入二叉树的值，“#”表示NULL
    //构造二叉链表表示的树 tree
    char ch='#';
    cin>>ch;
    if (ch == '#')
        Tree = NULL;
    else {
        if (!( Tree = (Bitree) malloc(sizeof(BiTNode) ) ) )
            exit(OVERFLOW);
        Tree->data = ch;
        CreateBiTree(Tree->lchild);
        CreateBiTree(Tree->rchild);
    }
}

void BeforePrint(Bitree Tree) {
    if (Tree == NULL)
        return ;
    //若不为空，则打印输出
    cout<<Tree->data;
    BeforePrint(Tree->lchild);
    BeforePrint(Tree->rchild);
}