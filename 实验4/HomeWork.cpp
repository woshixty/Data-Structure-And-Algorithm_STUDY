#include<iostream>
#include<stdlib.h>

using std::cin;
using std::cout;
using std::endl;

#define MAX_VERTEX_NUM 20

typedef int Status;		//返回状态
typedef char NodeName[MAX_VERTEX_NUM];	//顶点名称

enum Visited{YES=1, NO=0};  //深度优先遍历时判断是否已被访问过
enum Number{G301=0, G302=1, G303=2};

//线路
typedef struct ArcNode {
    int adjvex;     //该公交线路所指向的站点
    struct ArcNode *nextarc;    //指向下一个站点
    Number num;     //是哪一辆公交的线路
}ArcNode;

typedef struct VNode {
    NodeName VNodeName;     //顶点名称
    ArcNode *firstarc;  //指向第一条依附该站点的指针
    Visited tag;    //该节点是否被访问过
}VNode, AdjList[MAX_VERTEX_NUM];

typedef struct {
    AdjList vertices;
    int vexnum;     //图当前的站点数
    int arcnum;     //图当前的公交线路
}ALGraph;

Status CreateGraph(ALGraph &G);  //构造公交线路图



Status CreateGraph(ALGraph &G) {

    //输入图的 站点数 线路数
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
        cout<<"请输入该线路对应哪一辆公交车[0 1 2]"<<endl;
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
            arcNode->num = number;

            if (G.vertices[begin].firstarc == NULL) {  //如果 G.vertices[i] 为 NULL
                G.vertices[begin].firstarc = arcNode;
                continue;
            }
            
            ArcNode *GARC;  //用来遍历邻接站点的
            int flag = 0;
            for (GARC = G.vertices[begin].firstarc ; GARC->nextarc!=NULL; GARC = GARC->nextarc) {
                if (GARC->adjvex == arcNode->adjvex) {  //如果有相同的弧,则忽略它
                    flag = 1;
                    break;
                }
            }  //到顶点的最后一个弧

            if (flag == 1 || GARC->adjvex == arcNode->adjvex) continue;  //如果有相同的弧
            
            GARC->nextarc = arcNode;  //最后一个节点指向新建立的结点
        }
    }
}