#include <iostream>
#include<string.h>

using std::cin;
using std::cout;
using std::endl;

#define MAX_VERTEX_NUM 20

typedef int Status;				//返回状态
typedef int VRType;       		//顶点关系类型
typedef char InfoType;   		//信息类型
typedef char VertexType[MAX_VERTEX_NUM];	//顶点类型

enum GraphKind{DG,DN};  //图的种类 

typedef struct ArcNode {
    int adjvex;                 //该弧所指向的顶点的位置
    struct ArcNode *nextarc;    //指向下一条弧的指针
    InfoType *info;             //信息类型
}ArcNode;

typedef struct VNode {
    VertexType VNodeName;       //顶点名称
    ArcNode *firstarc;          //指向第一条依附该节点的指针
}VNode, AdjList[MAX_VERTEX_NUM];

typedef struct {
    AdjList vertices;
    int vexnum;     //图当前的顶点数
    int arcnum;     //图当前的弧数
    int kind;       //图的种类
}ALGraph;

Status PrintALGraph(ALGraph &g);
Status CreateGraph(ALGraph &G);
Status CreateDG(ALGraph &G);        //构造有向图
Status CreateDN(ALGraph &G);        //构造无向图

int main() {
}

Status CreateDG(ALGraph &G) {

    //初始化图
    cout<<"请输入有向图的顶点数"<<endl;
    cin>>G.vexnum;
    cout<<"请输入有向图的弧数"<<endl;
    cin>>G.arcnum;

    //构造有向图
    //输入各个顶点名称
    cout<<"开始构造有向图，请依次输入各个顶点名称"<<endl;
    for (int i = 0; i < G.vexnum; i++) {
        cout<<"请输入第"<<i+1<<"个顶点的名称"<<endl;
        cin>>G.vertices[i].VNodeName;
        G.vertices = NULL;
    }
    //依次输入各顶点的弧
    for (int i = 0; i < G.vexnum; i++) {
        int begin=-1, end=-1;
        cout<<"请输入第"<<i+1<<"条弧的起点与终点对应的下标"<<endl;
        cin>>begin>>end;

        ArcNode *arcNode = malloc(sizeof(arcNode));  //新开辟一块空间存储 begin 顶点对应的弧
        arcNode->adjvex = end;

        ArcNode *GARC;
        for (GARC = G.vertices[begin].firstarc ; GARC!=NULL; GARC = GARC->nextarc) ;  //到顶点的最后一个弧
    }
}