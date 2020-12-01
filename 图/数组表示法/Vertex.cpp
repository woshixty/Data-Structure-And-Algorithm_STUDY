#include <iostream>
#include<string.h>

using std::cin;
using std::cout;
using std::endl;

#define INFINITY 0                          //两个顶点之间无边或弧时的数值
#define MAX_VERTEX_NUM 26                   //最大顶点个数
#define MAX_INFO    10                      //弧相关信息的字符串的最大长度
#define TRUE  1
#define FALSE 0
#define ERROR 0
#define OK    1

typedef int Status;				//返回状态
typedef int VRType;       		//顶点关系类型
typedef char InfoType;   		//信息类型
typedef char VertexType[MAX_VERTEX_NUM];	//顶点类型

enum GraphKind{DG,DN,UDG,UDN};
 
//有向图，有向网，无向图，无线网
typedef struct {
	VRType adj;                        	// VRType是顶点关系类型，对无权图，用1或0, 表示相邻否，对带权图，则为权值类型
    InfoType *info;                    	// 该弧相关信息的指针, 存储与该弧相关的信息
} ArcCell, AdjMartix[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; 

typedef struct {
	VertexType vexs[MAX_VERTEX_NUM];   	//顶点向量
	AdjMartix arcs;                    	//邻接矩阵
    int vexnum, arcnum;                	//图的当前顶点个数和弧数
	GraphKind kind;                     //图的种类标志
} MGraph;

int LocateVex(MGraph G, VertexType u)	//若图中存在顶点u，则返回该顶点在图中的位置；否则返回其他信息
{
    for(int i = 0; i < G.vexnum; ++i)
	    if(strcmp(u,G.vexs[i]) == 0)
		    return i;
	return -1;
}

Status CreateDG(MGraph &G)				//采用数组（邻接矩阵）表示法，构造有向图
{
	int i,j,k,l,IncInfo;
	char a[MAX_INFO];
	VertexType va,vb;

	cout << "**********************************有向图*************************************" << endl;
	cout << "请输入有向图的顶点数，边数，以及边是否含有其它信息（是：1，否：0）：" << endl;
	cout << "请输入顶点数： ";
	cin >> G.vexnum;
	cout << "请输入弧数： " << endl;
	cin >> G.arcnum ;
	cout << "请输入边是否含有其它信息（是：1，否：0）： " << endl;
	cin >> IncInfo;
	cout << "开始构造有向图：\n" << "逐一输入顶点向量" << endl;
	
	for(i = 0;i < G.vexnum;++i)
	{
		cout << "请输入第"<<i+1<<"个顶点的向量: "<<endl;
		cin >> G.vexs[i];
	}

	for(i = 0; i < G.vexnum; ++i)		//初始化邻接矩阵
		for(j = 0; j < G.vexnum; ++j) {
			G.arcs[i][j].adj = INFINITY;	//有向图
			G.arcs[i][j].info = NULL;
		}

		cout << "请输入"  << G.arcnum << "条弧的弧头和弧尾" << endl;

		for(k = 0; k < G.arcnum; ++k) {       
			cout << "请输入第" << k + 1 << "条弧的弧尾：" << endl;
			cin >> va ;
			cout << "请输入第" << k + 1 << "条弧的弧头：" << endl;
			cin >> vb;
			i = LocateVex(G,va);
			j = LocateVex(G,vb);
			G.arcs[i][j].adj = 1;	//有向图
			if(IncInfo)
			{
				cout << "请输入该边的相关信息(" << MAX_INFO  << "个字符）";
				cin >> a;
				l = strlen(a);
				if(l)
				{
					G.arcs[i][j].info = (char *)malloc( (l+1)*sizeof(char) );	//有向图
					strcpy(G.arcs[i][j].info,a);
				}
			}
		}
		
		G.kind = DG;
		return OK;
}

Status CreateDN(MGraph &G)		//采用数组（邻接矩阵），构造有向网
{
	int i, j, k, w, IncInfo;
	char a[MAX_INFO];
	VertexType va,vb;
	cout << "**********************************有向网*************************************" << endl;
	cout << "请输入有向网的顶点数，弧数、权值以及边是否含有其它信息（是：1，否：0）：" << endl;
	cout << "请输入顶点数： ";
	cin >> G.vexnum;
	cout << "请输入弧数： " << endl;
	cin >> G.arcnum ;
	cout << "请输入边是否含有其它信息（是：1，否：0）： " << endl;
	cin >> IncInfo;
	cout << "开始构造有向网： \n" << "逐一输入顶点向量" << endl;
	for(i = 0;i < G.vexnum;++i)
	{
		cout << "请输入第"<<i+1<<"个顶点的向量: "<<endl;
		cin >> G.vexs[i] ;
		
	}
	for(i = 0; i < G.vexnum; ++i)			//初始化邻接矩阵
		for(j = 0; j < G.vexnum; ++j)
		{
			G.arcs[i][j].adj = INFINITY;	//有线网
			G.arcs[i][j].info = NULL;
		}
		cout << "请输入"  << G.arcnum << "条弧的弧尾、弧头和权值" << endl;
		for(k = 0; k < G.arcnum; ++k)
		{
			
			cout << "请输入第" << k + 1 << "条弧的弧尾：" << endl;
			cin >> va ;
			cout << "请输入第" << k + 1 << "条弧的弧头：" << endl;
			cin >> vb;
			cout << "请输入该弧的权值： " << endl;
			cin >> w;
			i = LocateVex(G,va);
			j = LocateVex(G,vb);
			G.arcs[i][j].adj = w;		//有向网
			if(IncInfo)
			{
				cout << "请输入该边的相关信息(" << MAX_INFO  << "个字符）";
				cin >> a;
				w = strlen(a);
				if(w)
				{
					G.arcs[i][j].info = (char *)malloc((w+1)*sizeof(char));		//有向网
					strcpy(G.arcs[i][j].info,a);
				}
			}
		}
		G.kind = DN;
		return OK;
}
 
Status CreateUDG(MGraph &G)		//用数组（邻接矩阵）表示法，构造无向图
{
	int i,j,k,l,IncInfo;
	char a[MAX_INFO];
	VertexType va,vb;
	cout << "**********************************无向图*************************************" << endl;
	cout << "请输入无向图的顶点数，边数，以及边是否含有其它信息（是：1，否：0）：" << endl;
	cout << "请输入顶点数： ";
	cin >> G.vexnum;
	cout << "请输入边数： " << endl;
	cin >> G.arcnum ;
	cout << "请输入边是否含有其它信息（是：1，否：0）： " << endl;
	cin >> IncInfo;
	cout << "开始构造无向图： \n" << "逐一输入顶点向量……" << endl;

	for(i = 0;i < G.vexnum;++i)	{
		cout << "请输入第"<<i+1<<"个顶点的向量: "<<endl;
		cin >> G.vexs[i] ;
	
	}

   	for(i = 0; i < G.vexnum; ++i)		//初始化邻接矩阵
		for(j = 0; j < G.vexnum; ++j) {
			G.arcs[i][j].adj = INFINITY;
			G.arcs[i][j].info = NULL;
		}

	for (k = 0; k < G.arcnum; ++k) {

		cout << "请输入第" << k + 1 << "条边的第一个顶点：" << endl;
		cin >> va ;

		cout << "请输入第" << k + 1 << "条边的第二个顶点：" << endl;
		cin >> vb;

		i = LocateVex(G,va);
		j = LocateVex(G,vb);

		G.arcs[i][j].adj = G.arcs[j][i].adj = 1;	// 无向图

		if(IncInfo) {
			cout << "请输入该边的相关信息(" << MAX_INFO  << "个字符）";
			cin >> a;
			l = strlen(a);
		  	if (l) {
				G.arcs[i][j].info = G.arcs[j][i].info = (char *)malloc( (l + 1)*sizeof(char) );  //给相关信息分配内存空间
				strcpy(G.arcs[i][j].info,a);			//无向图，两个指针指向同一个信息
		  	}
		}
	}
	G.kind = UDG;
	return OK;
}

Status CreateUDN(MGraph &G)		//采用数组（邻接矩阵）表示法，构造无向网
{
    int i,j,k,w,IncInfo;
    char a[MAX_INFO];
    VertexType va,vb;
    cout << "**********************************无向网*************************************" << endl;
    cout << "请输入无向网的顶点数、边数和权值，以及边是否含有其它信息（是：1，否：0）：" << endl;
    cout << "请输入顶点数： ";
    cin >> G.vexnum;
    cout << "请输入边数： " << endl;
    cin >> G.arcnum ;
    cout << "请输入边是否含有其它信息（是：1，否：0）： " << endl;
     cin >> IncInfo;
    cout << "开始构造无向网： \n" << "逐一输入顶点向量" << endl;
   
    for(i = 0;i < G.vexnum;++i) {
	    cout << "请输入第"<<i+1<<"个顶点的向量: "<<endl;
	    cin >> G.vexs[i] ;
    }

    for(i = 0; i < G.vexnum; ++i)		//初始化邻接矩阵
	    for(j = 0; j < G.vexnum; ++j) {
		    G.arcs[i][j].adj = INFINITY;		//无线网
		    G.arcs[i][j].info = NULL;
	    }
   
    for (k = 0; k < G.arcnum; ++k)
    {
	    cout << "请输入第" << k + 1 << "条边的第一个顶点：" << endl;
	    cin >> va ;
	    cout << "请输入第" << k + 1 << "条边的第二个顶点：" << endl;
	    cin >> vb;
	    cout << "请输入该边的权值： " << endl;
	    cin >> w;
	    i =LocateVex(G,va);
	    j =LocateVex(G,vb);
	    G.arcs[i][j].adj = G.arcs[j][i].adj = w;	//无向网
	    if (IncInfo)
	    {
		    cout << "请输入该边的相关信息(" << MAX_INFO  << "个字符）";
		    cin >> a;
		    w = strlen(a);
		    if (w)
		    {
			    G.arcs[i][j].info = G.arcs[j][i].info = (char *)malloc((w+1)*sizeof(char));   //无向网，两个指针指向同一个信息
			    strcpy(G.arcs[i][j].info,a);
		    }
	    }
    }
    G.kind = UDN;
    return OK;
}
 
 
Status CreateGraph(MGraph &G)
{
	cout << "请输入图G的类型\n"  << "有向图：0\n" << "有向网：1\n" << "无向图：2\n" << "无向网：3\n";
	scanf("%d",&G.kind);
	switch(G.kind) {
	case DG:  CreateDG(G);       //有向图
		break;
	case DN:  CreateDN(G);       //有向网
		break;
	case UDG: CreateUDG(G);      //无向图
		break;
	case UDN: CreateUDN(G);      //无向网
		break;
	}
	return OK;
}

Status DestroyGraph(MGraph &G)     //若图存在，则销毁图G
{
	int i,j,k = 0;
	if(G.kind % 2)			// 网
		k = INFINITY;      	// K为两顶点之间无边或无弧时邻接矩阵元素的值
	for(i = 0; i < G.vexnum; ++i)
		if(G.kind < 2) {  	//有向
            for(j = 0; j < G.vexnum; ++j)
		   	if(G.arcs[i][j].adj != k)    //两顶点之间有弧
			if(G.arcs[i][j].info) {
				free(G.arcs[i][j].info);
				G.arcs[i][j].info = NULL;    
			}
		} else {
			for (j = i + 1; j < G.vexnum; ++j) {
				if (G.arcs[i][j].adj != k)
					if(G.arcs[i][j].info) {
						free(G.arcs[i][j].info);
						G.arcs[i][j].info = G.arcs[j][i].info = NULL;
					}
			}
		}
		G.vexnum = 0;
		G.vexnum = 0;
	return OK;
}

void Display(MGraph &G) {
     for(int i = 0; i < G.vexnum; ++i)
	    for(int j = 0; j < G.vexnum; ++j) {
			cout << G.arcs[i][j].adj << ' ';
			if((j+1)%G.vexnum == 0)
				cout << endl;
		}
}

int main()
{
	int i,j,k,n;
	MGraph G;
	CreateGraph( G);
	Display(G);
	DestroyGraph(G);
	return 0;
}  