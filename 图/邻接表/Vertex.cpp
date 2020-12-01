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

typedef struct ArcNode {
    int adjvex;                 //该弧所指向的顶点的位置
    struct ArcNode *nextarc;    //指向下一条弧的指针
    InfoType *info;             //信息类型
}ArcNode;

typedef struct VNode {
    VertexType data;            //顶点名称
    ArcNode *firstarc;          //指向第一条依附该节点的指针
}VNode, AdjList[MAX_VERTEX_NUM];

typedef struct {
    AdjList vertices;
    int vexnum, arcnum;     //图当前的顶点数和弧数
    int kind;       //图的种类
}ALGraph;

void CreateALGraph(ALGraph &g);
void PrintALGraph(ALGraph &g);

int main() {

}

void CreateALGraph(ALGraph &g) {
    
}