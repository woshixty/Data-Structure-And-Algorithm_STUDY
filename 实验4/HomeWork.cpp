#include<iostream>
#include<stdlib.h>

using std::cin;
using std::cout;
using std::endl;

#define MAX_VERTEX_NUM 20

typedef int Status;		//返回状态
typedef char NodeName[MAX_VERTEX_NUM];	//顶点名称
#define STACK_INIT_SIZE 100     //栈的空间初始分配量
#define STACKINCREMENT 10       //栈的空间分配增量

//状态码
#define OK 0
#define FALSE 1

enum VisitedTag{YES=1, NO=0};  //深度优先遍历时判断是否已被访问过

//线路
typedef struct ArcNode {
    int adjvex;     //该公交线路所指向的站点
    struct ArcNode *nextarc;    //指向下一个站点
    int num;     //是哪一辆公交的线路
}ArcNode;

typedef struct VNode {
    NodeName VNodeName;     //顶点名称
    ArcNode *firstarc;  //指向第一条依附该站点的指针
    VisitedTag tag;    //该节点是否被访问过
}VNode, AdjList[MAX_VERTEX_NUM];

typedef struct {
    AdjList vertices;
    int vexnum;     //图当前的站点数
    int arcnum;     //图当前的公交线路
    int NumOfBus;   //公交车数量
}ALGraph;

//栈的顺序存储
typedef ArcNode* StackType;
typedef struct Stack {
    int *base;          //基指针 在栈构造之前和销毁之后都为NULL 存Node的下标
    int *top;           //栈顶指针 指向栈顶 存Node的下标
    int stackSize;      //栈的大小
}SqlStack;


void manue();
Status CreateGraph(ALGraph &G);  //构造公交线路图
Status PrintPaths(ALGraph *G);  //打印公交线路图
Status PrintOnePath(ALGraph *G, int BusNum, int v);  //打印某一路公交车
bool FindAdjVex(ALGraph *G, int v, int BusNum, int &e);  //寻找某一路公交车的下一个站点
bool Visited(ALGraph *G, int v);  //判断是否已经访问
void clearVisited(ALGraph *G);  //清除所有已经访问过的结点
Status Visit(ALGraph *G, int v);  //访问某个结点
Status FindWay(ALGraph *G, int begin, int end);
void testPrint(ALGraph *G);

// 栈
Status InitStack(SqlStack &s);        //创造一个空栈
bool StackEmpty(SqlStack &s);     //若s为空栈返回TRUE 否则返回FALSE
Status Push(SqlStack &s, int e);  //插入e为新的栈顶元素
bool Pop(SqlStack &s, int &e);  //若栈不为空，删除栈顶元素并用e返回值并返回true 否则返回false
Status StackTraverse(SqlStack s);  //遍历栈
void PrintStack(SqlStack s, ALGraph *G, int end);  //打印栈

//全局栈
static SqlStack s;
//判断有没有被访问过
int num=0;

int main() {
    /* hello 数据 结构 啊哈 机网 world java c++ c 汇编 牛逼 
     a b c d e f g
     1 3 1 3 5 1 5 6 1 2 3 2 3 4 2 4 5 2 5 7 2
     A B C D E F G H I J K L M
     1 5 1 5 6 1 6 7 1 7 8 1 8 9 1 2 5 2 5 6 2 6 10 2 10 11 2 11 7 2 7 8 2 8 12 2 3 5 3 5 13 3 13 10 3 10 11 3 4 8 4 8 11 4 11 13 4 
     */

    ALGraph G;
    CreateGraph(G);
    cout<<"******************************"<<endl;
    PrintPaths(&G);
    int a,b;
    cout<<"请输入起点与终点"<<endl;
    cin>>a>>b;
    FindWay(&G, --a, --b);
    if (num ==0) {
        cout<<"没有路径"<<endl;
    }
}

Status CreateGraph(ALGraph &G) {

    //输入图的 站点数 线路数
    cout<<"请输入公交车数量"<<endl;
    cin>>G.NumOfBus;
    cout<<"请输入公交线路图的站点数"<<endl;
    cin>>G.vexnum;
    cout<<"请输入公交线路图的线路数"<<endl;
    cin>>G.arcnum;

    //输入各个站点名称
    cout<<"开始构造公交线路图，请依次输入各个站点名称"<<endl;
    for (int i = 0; i < G.vexnum; i++) {
        cout<<"请输入第"<<i+1<<"个站点的名称"<<endl;
        cin>>G.vertices[i].VNodeName;
        G.vertices[i].firstarc = NULL;
        G.vertices[i].tag = NO;
    }

    //依次输入各条路线
    for (int i = 0; i < G.arcnum; i++) {

        int begin=-1, end=-1;
        cout<<"请输入第"<<i+1<<"条线路的起点与终点对应的站点的数字"<<endl;
        cin>>begin>>end;
        begin--;
        end--;

        int number;  //对应哪一辆公交车
        cout<<"请输入该线路对应哪一辆公交车"<<endl;
        cin>>number;

        //由于公交线路图是无向图，所以来两次
        for (int k = 0; k < 2; k++) {
            
            // end 与 begin 换一换
            // 由于放末尾有 continue 故放在一开始
            int j = end;
            end = begin;
            begin = j;

            ArcNode *arcNode = (ArcNode *)malloc(sizeof(arcNode));  //新开辟一块空间存储 begin 顶点对应的弧

            arcNode->adjvex = end;
            arcNode->nextarc = NULL;
            arcNode->num = number;   //公交车路数

            if (G.vertices[begin].firstarc == NULL) {  //如果 G.vertices[i] 为 NULL
                G.vertices[begin].firstarc = arcNode;
                continue;
            }
            
            ArcNode *GARC;  //用来遍历邻接站点的
            for (GARC = G.vertices[begin].firstarc ; GARC != NULL && GARC->nextarc!=NULL; GARC = GARC->nextarc); //到顶点的最后一个弧

            GARC->nextarc = arcNode;  //最后一个节点指向新建立的结点
        }
    }
    return 0;
}

Status PrintPaths(ALGraph *G) {
    //遍历输出每一路公交车
    for (int i = 0; i < G->NumOfBus; i++) {
        clearVisited(G);
        cout<<"这是"<<i+1<<"路公交车路线: ";
        PrintOnePath(G, i+1, i);
        cout<<endl;
        clearVisited(G);
    }
    return 0;
}

Status PrintOnePath(ALGraph *G, int BusNum, int v) {

    //如果公交车号不等 且 已被访问 则返回
    if (G->vertices[v].tag ==YES) {
        return 0; 
    }

    Visit(G, v);
    cout<<"-"<<G->vertices[v].VNodeName;
    int e;

    for ( ; FindAdjVex(G, v, BusNum, e); ) {
        PrintOnePath(G, BusNum, e);
    }
    
    return 0;
}

bool FindAdjVex(ALGraph *G, int v, int BusNum, int &e) {

    ArcNode *arcNode = G->vertices[v].firstarc;
    for ( ; arcNode != NULL; arcNode = arcNode->nextarc) {
        if ( !Visited(G, arcNode->adjvex)  && arcNode->num == BusNum ) {
            e = arcNode->adjvex;
            return true;    //找到了未被访问的站点
        }
    }
    e=-1;
    return false;    //实在找不到未被访问的站点
}

bool Visited(ALGraph *G, int v) {
    if (G->vertices[v].tag == NO) return false;  //站点未被访问过
    return true;
}

void clearVisited(ALGraph *G) {
    for (int i = 0; i < G->vexnum; i++) G->vertices[i].tag = NO;
}

Status Visit(ALGraph *G, int v) {
    G->vertices[v].tag = YES;
    return 0;
}

Status FindWay(ALGraph *G, int begin, int end) {

    //如果已被访问 则返回
    if (G->vertices[begin].tag ==YES)
        return 0;
    
    //如果找到了这个点,就打印栈 返回
    if (begin == end) {
        PrintStack(s, G, end);
        return 0;
    }

    //设置结点已经访问过
    Visit(G, begin);
    Push(s, begin);

    ArcNode * w;
    for ( w=G->vertices[begin].firstarc; w!=NULL; w=w->nextarc) {
        if (!Visited(G, w->adjvex)) {
            FindWay(G, w->adjvex, end);
        }
    }

    //退栈
    Pop(s, begin);
    return OK;
}

// 栈的函数
Status InitStack(SqlStack &s) {
    //给栈分配空间
    s.base = (int *) malloc(STACK_INIT_SIZE*sizeof(int));
    if (!s.base) exit(3);  //给栈分配空间失败
    s.top = s.base;  //首尾指针指同一个
    s.stackSize = STACK_INIT_SIZE;
    return OK;
}

bool StackEmpty(SqlStack &s) {
    if ( s.base!=NULL && s.base!=s.top )
        return false;
    return true;
}

Status Push(SqlStack &s, int e) {
    //判断栈满，追加存储空间
    if (s.top-s.base>=s.stackSize) {
        s.base = (int *) realloc(s.base, (s.stackSize + STACKINCREMENT )*sizeof(int));
        if (!s.base) exit(3);
        s.top = s.base+s.stackSize;  //顶部指针重新指
        s.stackSize+=STACKINCREMENT;  //栈总空间加上STACKINCREMENT
    }
    *s.top = e;
    s.top++;
    return OK;
}

bool Pop(SqlStack &s, int &e) {
    //判断栈是否为空
    if (StackEmpty(s)) return false;
    s.top--;
    e = *s.top;
    return true;
}

void PrintStack(SqlStack s, ALGraph *G, int end) {
    num++;
    int *a = s.base;
    cout<<"第"<<num<<"路径：";
    for (; a!=s.top; a++)
        cout<<G->vertices[*a].VNodeName<<" ";
    cout<<G->vertices[end].VNodeName<<endl;
}


///////
void testPrint(ALGraph *G) {
    for (int i = 0; i < G->vexnum; i++) {
        cout<< G->vertices[i].VNodeName<<": ";
        for (ArcNode *w = G->vertices[i].firstarc; w!=NULL; w=w->nextarc) {
            cout<<"["<<G->vertices[w->adjvex].VNodeName<<w->num<<"路"<<" ";
        }
        cout<<"]"<<endl;
    }
}