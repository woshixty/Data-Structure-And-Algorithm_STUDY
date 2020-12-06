#include<iostream>
#include<string.h>
#include<stdlib.h>
#include"Vertex.h"

using std::cin;
using std::cout;
using std::endl;


int main() {
    ALGraph g;
    CreateGraph(g);
    PrintDGraph(&g);
    DFSTraverse(&g);
    return 0;
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
        G.vertices[i].firstarc = NULL;
        G.vertices[i].tag = NO;
    }

    //依次输入各顶点的弧
    for (int i = 0; i < G.arcnum; i++) {
        int begin=-1, end=-1;
        cout<<"请输入第"<<i+1<<"条弧的起点与终点对应的节点的数字"<<endl;
        cin>>begin>>end;
        begin--;
        end--;

        ArcNode *arcNode = (ArcNode *)malloc(sizeof(arcNode));  //新开辟一块空间存储 begin 顶点对应的弧
        arcNode->adjvex = end;
        arcNode->nextarc = NULL;

        if (G.vertices[begin].firstarc == NULL) {  //如果 G.vertices[i] 为 NULL
            G.vertices[begin].firstarc = arcNode;
            continue;
        }
        
        ArcNode *GARC;
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
    return OK;
}

Status CreateDN(ALGraph &G) {
    
    //初始化图
    cout<<"请输入无向图的顶点数"<<endl;
    cin>>G.vexnum;
    cout<<"请输入无向图的弧数"<<endl;
    cin>>G.arcnum;

    //输入各个顶点名称
    cout<<"开始构造无向图，请依次输入各个顶点名称"<<endl;
    for (int i = 0; i < G.vexnum; i++) {
        cout<<"请输入第"<<i+1<<"个顶点的名称"<<endl;
        cin>>G.vertices[i].VNodeName;
        G.vertices[i].firstarc = NULL;
        G.vertices[i].tag = NO;
    }

    //依次输入各顶点的弧
    for (int i = 0; i < G.arcnum; i++) {
        int begin=-1, end=-1;
        cout<<"请输入第"<<i+1<<"条弧的起点与终点对应的节点的数字"<<endl;
        cin>>begin>>end;
        begin--;
        end--;

        //由于是无向图，所以要换过来再来一次
        for (int k = 0; k < 2; k++) {

            // end 与 begin 换一换
            // 由于放末尾有 continue 故放在一开始
            int j = end;
            end = begin;
            begin = j;

            ArcNode *arcNode = (ArcNode *)malloc(sizeof(arcNode));  //新开辟一块空间存储 begin 顶点对应的弧
            arcNode->adjvex = end;
            arcNode->nextarc = NULL;

            if (G.vertices[begin].firstarc == NULL) {  //如果 G.vertices[i] 为 NULL
                G.vertices[begin].firstarc = arcNode;
                continue;
            }
            
            ArcNode *GARC;
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
    return OK;
}

Status PrintDGraph(ALGraph *G) {
    for (int i = 0; i < G->vexnum; i++) {  //遍历每个顶点的下标
        //打印输出一下顶点
        switch (G->kind) {

        case DG:
            cout<<"第"<<i+1<<"个顶点: "<<G->vertices[i].VNodeName<<" 指向的点有: [";
            break;

        case DN:
            cout<<"与第"<<i+1<<"个顶点: "<<G->vertices[i].VNodeName<<" 相连接顶点有: [";
            break;

        default:
            break;
        }
        
        //遍历输出第 i+1 个顶点所指向的 顶点
        ArcNode *j;
        for ( j = G->vertices[i].firstarc; j != NULL; j=j->nextarc)
            cout<<" "<<G->vertices[j->adjvex].VNodeName<<" ";
        cout<<" ]"<<endl;
    }
    return OK;
}

Status CreateGraph(ALGraph &G) {
    cout<<"你想要构造嘛图？ 1.有向图 2.无向图"<<endl;
    cin>>G.kind;
    switch (G.kind) {
    
    case DG:            //有向图
        CreateDG(G);
        break;

    case DN:            //无向图
        CreateDN(G);
        break;

    default:
        break;

    }
    return OK;
}


bool Visited(ALGraph *G, int v) {
    if (G->vertices[v].tag == NO) return false;  //结点未被访问过
    return true;
}

bool FindAdjVex(ALGraph *G, int v, int &e) {

    ArcNode *arcNode = G->vertices[v].firstarc;
    for ( ; arcNode != NULL; arcNode = arcNode->nextarc) {
        if ( !Visited(G, arcNode->adjvex) ) {
            e = arcNode->adjvex;
            return true;    //找到了未被访问的结点
        }
    }
    e=-1;
    return false;    //实在找不到未被访问的结点

}

Status DFSTraverse(ALGraph *G) {
    for (int i = 0; i < G->vexnum; i++) G->vertices[i].tag = NO;
    for (int i = 0; i < G->vexnum; i++)
        if (G->vertices[i].tag == NO) {
            DFS(G, i);
        }
    return OK;
}

Status Visit(ALGraph *G, int v) {
    G->vertices[v].tag = YES;
    cout<<G->vertices[v].VNodeName<<endl;
    return OK;
}

Status DFS(ALGraph *G, int v) {

    int e;
    //先判断一下 是否已经被访问过了
    if ( Visited(G, v) ) {  //如果被访问过了
        return OK;
    }
    
    //未被访问 则访问这个顶点
    Visit(G, v);

    for ( ; FindAdjVex(G, v, e); ) {
        DFS(G, e);
    }
    return OK;
}