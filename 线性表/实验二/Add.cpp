#include<stdio.h>
#include<stdlib.h>

typedef struct PLNODE
{
    int dbCoef;             //系数域
    int nExpn;              //指数域
    struct PLNODE *next;    //指针域，指向下一节点
}PLONDE;
typedef PLNODE *PLinkList;

void PrintPolyn(PLinkList &sPloyn);
void PrintPoly(PLNODE sPTemp);
void ListInsert(PLinkList sPolyn, PLNODE sNewNode);
void CreatePolyn(PLinkList &sPloyn);
void AddPolyn(PLinkList &a, PLinkList &b, PLinkList &c);
void FreePolyn(PLinkList &a);
void action();

int main() {
    action();
    return 0;
}

void action() {
    PLinkList a=NULL;
    PLinkList b=NULL;
    //建两条链表
    CreatePolyn(a);
    CreatePolyn(b);
    //打印多项式链表
    printf("第一条多项式为: ");
    PrintPolyn(a);
    printf("第二条多项式为: ");
    PrintPolyn(b);
    //想家之后的链表
    PLinkList c=(PLinkList)malloc(sizeof(PLNODE));
    c->dbCoef=0;
    c->nExpn=0;
    c->next=NULL;
    AddPolyn(a, b, c);
    //加完打印康康
    printf("加完以后: ");
    PrintPolyn(c);
    //释放资源啦
    FreePolyn(a);
    FreePolyn(b);
    FreePolyn(c);
    printf("资源释放完毕\n");
}

//释放链表
void FreePolyn(PLinkList &a) {
    PLinkList b = a;
    for (a=a->next; a!=NULL; a=a->next) {
        free(b);
        b=a;
    }
    free(b);
}

//将两个一元多项式相加
void AddPolyn(PLinkList &a, PLinkList &b, PLinkList &pc) {
    PLinkList c = pc;

    PLinkList pa = a;
    PLinkList pb = b; 
    //因为带有头节点，故跨过一个
    pa=pa->next;
    pb=pb->next;

    while (pa!=NULL && pb!=NULL) {
        //指数相等
        if (pa->nExpn == pb->nExpn) {
            PLNODE sNewNode;
            sNewNode.dbCoef = pa->dbCoef + pb->dbCoef;
            sNewNode.nExpn = pa->nExpn;
            //如果节点相加之后为0
            if ( sNewNode.dbCoef != 0 ) {
                ListInsert(c, sNewNode);
            }
            //同时向后移一位
            pa = pa->next;
            pb = pb->next;
        }else if (pa->nExpn > pb->nExpn) {
            PLNODE sNewNode = *pb;
            ListInsert(c, sNewNode);
            pb = pb->next;
        } else if (pb->nExpn > pa->nExpn) {
            PLNODE sNewNode = *pa;
            ListInsert(c, sNewNode);
            pa = pa->next;
        }
    }

    while (pa != NULL) {
        PLNODE sNewNode = *pa;
        ListInsert(c, sNewNode);
        pa = pa->next;
    }

    while (pb !=NULL ) {
        PLNODE sNewNode = *pb;
        ListInsert(c, sNewNode);
        pb = pb->next;
    }
}

//创建链表
void CreatePolyn(PLinkList &sPloyn) {
    sPloyn=(PLinkList)malloc(sizeof(PLNODE));
    //判断头节点是否为空,空间是否分配成功
    if (sPloyn == NULL) {
        exit(0);
    }
    //初始化
    sPloyn->dbCoef = 0;
    sPloyn->nExpn = 0;
    sPloyn->next=NULL;
    //新建一个指针
    PLinkList p = sPloyn;

    printf("请输入多项式有多少项\n");
    //todo 检测项数是否为整数，且指数需大于0
    int num;
    scanf("%d", &num);

    PLNODE sNewNode;  //定义新的结点

    for (int i = 0; i < num; i++) {
        printf("请输入第%d项的 系数 和 指数\n", i+1);
        //todo 检测系数是否合法
        int dbCoef,nExpn;
        scanf("%d%d",&dbCoef, &nExpn);

        //存入数据
        sNewNode.dbCoef = dbCoef;
        sNewNode.nExpn = nExpn;
        ListInsert(p, sNewNode);
    }
}

//将结点插入链表尾部，按照指数升序排列
void ListInsert(PLinkList sPolyn, PLNODE sNewNode) {

    PLinkList sTemp = sPolyn;
    PLinkList psNewNode = (PLinkList)malloc(sizeof(PLNODE));

    //判断psNewNode是否为空
    if (psNewNode == NULL) {
        exit(0);
    }
    
    //将指针对象所指的值改为sNewNode
    *psNewNode = sNewNode;
    
    //pre为stemp前一个指针
    PLinkList pre = sPolyn;
    for ( sTemp = sTemp->next ; sTemp!=NULL; sTemp=sTemp->next) {

        //如果系数相等就相加
        if (sNewNode.nExpn == sTemp->nExpn) {
            //对应系数相加
            sTemp->dbCoef+=sNewNode.dbCoef;
            //如果相加之和为0，则删除该节点
            if (sTemp->dbCoef == 0) {
                pre->next = sTemp->next;
                free(sTemp);
                return ;
            }
            return ;
        }

        //但凡有系数小于，就插入到前一个
        if (sNewNode.nExpn < sTemp->nExpn) {
            psNewNode->next = sTemp;
            pre->next = psNewNode;
            return ;
        }
        //移动pre指针
        pre = sTemp;
    }

    pre->next = psNewNode;  //将结点插入链表尾部
    psNewNode->next = NULL;   //将尾结点的指向置为空
}

//打印输出整个一元多项式
void PrintPolyn(PLinkList &sPloyn) {
    PLinkList s = sPloyn;
    for ( s=s->next ; s!=NULL; s=s->next) {
        PrintPoly(*s);
    }
    printf("\n");
}

//打印输出单个节点
void PrintPoly(PLNODE sPTemp) {
    printf(" ");
    //判断系数
    if (sPTemp.dbCoef < 0) {
        printf("");
    } else if (sPTemp.dbCoef > 0) {
        printf("+");
    } else {
        return ;
    }

    if (sPTemp.nExpn == 0) {  //指数为零，直接输出系数
        printf("%d",sPTemp.dbCoef);
    } else if(sPTemp.dbCoef==1) {  //当系数为1时
        if (sPTemp.nExpn == 1) {
            printf("x");
        } else {
            printf("x^%d",sPTemp.nExpn);
        }
    } else if (sPTemp.dbCoef == -1) {
        if (sPTemp.nExpn == 1) {
            printf("-x");
        } else{
            printf("-x^%d",sPTemp.nExpn);
        }
    } else {
        if (sPTemp.nExpn == 1) {
            printf("%dx",sPTemp.dbCoef);
        } else {
            printf("%dx^%d",sPTemp.dbCoef, sPTemp.nExpn);
        }
    }
    printf(" ");
}