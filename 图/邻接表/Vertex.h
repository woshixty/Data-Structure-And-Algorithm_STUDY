#ifndef VERTEX_H
#define VERTEX_H
#include"Stack.h"

#define MAX_VERTEX_NUM 20

typedef int Status;				//返回状态
typedef int VRType;       		//顶点关系类型
typedef char InfoType;   		//信息类型
typedef char VertexType[MAX_VERTEX_NUM];	//顶点名称

enum Visited{YES=1, NO=0};  //深度优先遍历时判断是否已被访问过
enum GraphKind{DG=1,DN=2};  //图的种类

typedef struct ArcNode {
    int adjvex;                 //该弧所指向的顶点的位置
    struct ArcNode *nextarc;    //指向下一条弧的指针
    InfoType *info;             //信息类型
}ArcNode;

typedef struct VNode {
    VertexType VNodeName;       //顶点名称
    ArcNode *firstarc;          //指向第一条依附该节点的指针
    Visited tag;
}VNode, AdjList[MAX_VERTEX_NUM];

typedef struct {
    AdjList vertices;
    int vexnum;     //图当前的顶点数
    int arcnum;     //图当前的弧数
    int kind;       //图的种类
}ALGraph;

Status PrintALGraph(ALGraph &g);
Status CreateGraph(ALGraph &G);     //在其中选择构造什么样的图
Status CreateDG(ALGraph &G);        //构造有向图
Status CreateDN(ALGraph &G);        //构造无向图
Status PrintDGraph(ALGraph *G);     //打印输出有向图
Status DFSTraverse(ALGraph *G);     //深度优先遍历图
bool FindAdjVex(ALGraph *G, int v, int &e);  //寻找未被访问过的结点 并将下标传回 若全被访问过 则返回 false
bool Visited(ALGraph *G, int v);  //判断某个节点是否被访问过了
Status Visit(ALGraph *G, int v);  //访问某个节点
Status DFS(ALGraph *G, int v);  //递归访问图

#endif