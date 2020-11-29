#include<stdlib.h>
#include<iostream>

#define OK 1
#define ERROR 2
#define OVERFLOW 3
using namespace std;

typedef struct BiTNode {
    char data;
    struct BiTNode* lchild;  //左孩子
    struct BiTNode* rchild;  //右孩子
    int index;
}BiTNode, * Bitree;

typedef struct Sta_BiTNode {
    char data;
    int lchild;  //左孩子
    int rchild;  //右孩子
}Sta_BiTNode;

static int Store_Tree[10][50];  //存储层序遍历的结果
static Sta_BiTNode sta_tree[100]={NULL};  //静态存储二叉树
static int dex = -1;  //用于给 tree 的 index 赋值
void CreateBiTree(Bitree &Tree);  //先序输入二叉树的值
void Dynamic_to_Static(Bitree DT, Sta_BiTNode ST[]);  //动态二叉树转静态
void printTree(Bitree tree);  //先序输出二叉树
void printStaTree(Sta_BiTNode ST[], int size);  //输出静态二叉树
void Dynamic_to_Level(Bitree DT, int LT[][100]);  //动态转层次


int main() {

    //-+a##*b##-c##d##/e##f##

    int size;  //存储静态数组的大小
    Bitree tree;
    CreateBiTree(tree);
    printTree(tree);
    //构造完二叉树之后，要将 dex 归于0
    size = dex;
    dex = 0;
    Dynamic_to_Static(tree, sta_tree);
    printStaTree(sta_tree, size);
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
        dex++;
        Tree->data = ch;
        Tree->index = dex;
        CreateBiTree(Tree->lchild);
        CreateBiTree(Tree->rchild);
    }
}

void Dynamic_to_Static(Bitree DT, Sta_BiTNode ST[]) {
    //如果指针为NULL 直接返回
    if (DT == NULL)
        return ;
    
    //将这个节点的data存入数组
    ST[dex].data = DT->data;
    
    //康康左右孩子 如果不是NULL就让 ST[index] 指向他们 
    if (DT->lchild != NULL)
        ST[dex].lchild = DT->lchild->index;

    if (DT->rchild != NULL)
        ST[dex].rchild = DT->rchild->index;
    
    dex++;  //别忘了给标志加加

    Dynamic_to_Static(DT->lchild, ST);
    Dynamic_to_Static(DT->rchild, ST);
}

//按照先序打印二叉树
void printTree(Bitree tree) {
    //如果指针为NULL 直接返回
    if (tree ==NULL)
        return ;
    cout<<"data: "<<tree->data << "    index: "<<tree->index<<endl;
    printTree(tree->lchild);
    printTree(tree->rchild); 
}

void printStaTree(Sta_BiTNode ST[], int size) {
    for (int i = 0; i <= size; i++) {
        cout<<"data:"<<ST[i].data<<"   lchild:"<<ST[i].lchild<<"   rchild:"<<ST[i].rchild<<endl;
    }
}

void Dynamic_to_Level(Bitree DT, int LT[][100]) {
    
}