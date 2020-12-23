/** 有向图的十字链表存储表示 **/

#define MAX_VERTEX_NUM 20

typedef char InfoType;
typedef int VertexType;

//这是弧的定义
typedef struct ArcBox {
    int tailvex, headvex;  //该弧的尾和头顶点的位置
    struct ArcNode *hlink, *tlink;  //分别为弧头相同和弧尾相同的弧的链域
    InfoType info[10];  //信息类型
} ArcBox;

//顶点的定义
typedef struct VexNode {
    VertexType data;
    ArcNode *firsttin, *firstout;  //分别指向该顶点的第一条入弧和初弧
} VexNode;

//十字链表的定义
typedef struct {
    VexNode xlist[MAX_VERTEX_NUM];  //表头向量
    int vexnum, arcnum;  //有向图当前顶点数和弧数
} OLGraph;