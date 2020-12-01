#include<stdlib.h>
#include<iostream>

#define OK 1
#define ERROR 2
#define OVERFLOW 3
using namespace std;

//动态二叉树结点
typedef struct BiTNode {
    char data;
    struct BiTNode* lchild;  //左孩子
    struct BiTNode* rchild;  //右孩子
    int index;
}BiTNode, * Bitree;

//静态二叉树结点
typedef struct Sta_BiTNode {
    char data;
    int lchild;  //左孩子
    int rchild;  //右孩子
}Sta_BiTNode;

static char Store_Tree[10][100]={'\0'};  //存储层序遍历的结果
static Sta_BiTNode sta_tree[100]={NULL};  //静态存储二叉树
static int dex = -1;  //用于给 tree 的 index 赋值

void CreateBiTree(Bitree &Tree);  //先序输入二叉树的值
void Dynamic_to_Static(Bitree DT, Sta_BiTNode ST[]);  //动态二叉树转静态
void printTree(Bitree tree);  //中序输出二叉树
void prePrintTree(Bitree tree);  //先序输出二叉树
void printStaTree(Sta_BiTNode ST[], int size);  //输出静态二叉树
void Dynamic_to_Level(Bitree DT, char LT[][100], int level=0);  //动态转层次
void printLevelTree(char LT[][100]);  //输出层次二叉树


int main() {
    /**/

    int size;  //存储静态数组的大小
    Bitree tree;  //动态二叉树

    cout<<"请先序输入二叉树 "<< "#"<<" 表示NULL"<<endl;
    CreateBiTree(tree);

    cout<<"------------------------------"<<endl;

    cout<<"中序输出二叉树"<<endl;
    printTree(tree);

    cout<<"------------------------------"<<endl;

    cout<<"先序输出二叉树"<<endl;
    prePrintTree(tree);

    cout<<"------------------------------"<<endl;

    //构造完二叉树之后，要将 dex 归于0
    size = dex;

    //动转静态又需要用到,智为0
    dex = 0;

    cout<<"动态二叉树转换为静态二叉链表"<<endl;
    Dynamic_to_Static(tree, sta_tree);
    printStaTree(sta_tree, size);

    cout<<"------------------------------"<<endl;

    //转成层次二叉树数组
    cout<<"动态二叉树层次输出"<<endl;
    Dynamic_to_Level(tree, Store_Tree, 0);
    printLevelTree(Store_Tree);

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

//按照中序打印二叉树
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

//将动态二叉树转成层次数组
void Dynamic_to_Level(Bitree DT, char LT[][100], int level) {
    if (DT == NULL)
        return ;
    int i;
    for (i = 0; LT[level][i]!='\0'; i++) ;
    LT[level][i] = DT->data;
    level++;
    Dynamic_to_Level(DT->lchild, LT, level);
    Dynamic_to_Level(DT->rchild, LT, level);
}

void printLevelTree(char LT[][100]) {
    for (int i = 0; LT[i][0]!='\0'; i++)
    {
        for (int j = 0; LT[i][j]!='\0'; j++)
            cout<<LT[i][j]<<" ";
        cout<<endl;
    }
}

//先序输出
void prePrintTree(Bitree tree) {
    if (tree ==NULL)
        return ;
    prePrintTree(tree->lchild);
    cout<<"data: "<<tree->data << "    index: "<<tree->index<<endl;
    prePrintTree(tree->rchild);
}