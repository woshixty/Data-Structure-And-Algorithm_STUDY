#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<iostream>
#include"StructDefine.h"
using namespace std;

bool GetInt(int &value);
void AddPolyn(PLinkList &ppa, PLinkList &ppb);
void CreatePolyn(PLinkList &sPloyn);
void ListInsert(PLinkList sPolyn, PLNODE sNewNode);
void PrintPolyn(PLinkList &sPloyn);
void PrintPoly(PLNODE sPTemp);

int main() {
    
    PLinkList pa, pb;
    
    CreatePolyn(pa);
    CreatePolyn(pb);

    if (pa==NULL || pb==NULL) {
        printf("pa pb 为空\n");
    }
    



    printf("相加之前pa:");
    PrintPolyn(pa);
    PrintPolyn(pb);



    AddPolyn(pa, pb);
    
    return 0;
}

//将两个一元多项式相加
void AddPolyn(PLinkList &ppa, PLinkList &ppb) {

    printf("pa pb 开始相加啦\n");

    PLinkList pa = ppa;
    PLinkList pb = ppb; 

    //创建空链表
    PLinkList p;



printf("pa %d %d\n", pa->dbCoef, pa->nExpn);
printf("pb %d %d\n", pb->dbCoef, pb->nExpn);

    

    //因为带有头节点，故跨过一个
    pa=pa->next;
    pb=pb->next;

    if (pa==NULL || pb==NULL) {
        printf("pa pb 为空\n");
    }

    while (pa!=NULL && pb!=NULL) {






printf("pa %d %d\n", pa->dbCoef, pa->nExpn);
printf("pb %d %d\n", pb->dbCoef, pb->nExpn);





        //如果p还未插入过节点
        //指数相等
        if (pa->nExpn == pb->nExpn) {

            PLNODE sNewNode;
            sNewNode.dbCoef = pa->dbCoef + pb->dbCoef;
            sNewNode.nExpn = pa->nExpn;
            //如果节点相加之后为0
            if ( sNewNode.dbCoef != 0 ) {
                ListInsert(p, sNewNode);


printf("%d  %d\n",pa->dbCoef, pa->nExpn);
printf("sNewNode %d\n",sNewNode.nExpn);
printf("插入成功\n");



            }

            //同时向后移一位
            pa = pa->next;
            pb = pb->next;
        }

        //pa指数大
        if (pa->nExpn > pb->nExpn) {
            PLNODE sNewNode = *pb;
            ListInsert(p, sNewNode);
            pb = pb->next;
        }
        
        //pb指数大
        if (pb->nExpn > pa->nExpn) {
            PLNODE sNewNode = *pa;
            ListInsert(p, sNewNode);
            pa = pa->next;
        }
    }

    while (pa != NULL) {
        PLNODE sNewNode = *pa;
        ListInsert(p, sNewNode);
        pa = pa->next;
    }

    while (pb !=NULL ) {
        PLNODE sNewNode = *pb;
        ListInsert(p, sNewNode);
        pb = pb->next;
    }

    printf("相加之后为：");
    PrintPolyn(p);
}

/**
 * 输入以及检验是否为整数
 * 使用 get_s() 获取用户的输入，获取输入之前用 fflush(stdin) 函数来清空缓存区
 * 使用 for 循环判断输入的字符是否为整数要素
 * 若确实为整数则将对应的数字字符转换为整数
 **/
bool GetInt(int &value) {

    char str[256] = {0};

    fflush(stdin);  //清空缓存

    fgets(str, 256, stdin);  //输入数据，并将数据存到 str 中

    //去掉换行符
    char* find;
    find = strchr(str, '\n');
    if (find) {
        *find = '\0';
    }
    

    unsigned int index = 1;
    int nTemp = 0;

    if (str[0] =='-')  //判断输入的数据是否为负数
        nTemp = 1;

    //判断每一位是否为数字字符，不是则返回false
    for ( index = nTemp; index < strlen(str); index++)
        if (str[index]<'0' || str[index]>'9')
            return false;
        
    value = atoi(str);  //将字符串转为数字
    return true;
}

//创建链表
void CreatePolyn(PLinkList &sPloyn) {
    sPloyn=(PLinkList)malloc(sizeof(PLNODE));

    //判断头节点是否为空
    if (sPloyn == NULL) {
        exit(0);
    }
    
    sPloyn->dbCoef = 0;
    sPloyn->nExpn = 0;
    sPloyn->next=NULL;

    PLinkList p = sPloyn;

    printf("请输入项数\n");
    //使用GetInt()函数输入项数并检测项数是否为整数，且指数需大于0
    int num;
    GetInt(num);

    PLNODE sNewNode;  //定义新的结点

    for (int i = 0; i < num; i++) {
        printf("请输入第%d项的 系数 和 指数\n", i+1);
        //使用 cin.fail() 检测系数是否合法
        int dbCoef;
        cin>>dbCoef;
        if (cin.fail() && dbCoef==0) {
            printf("检测系数不合法\n");
            return ;
        }
        
        //使用getInt检测输入的指数是否合法
        int nExpn;
        GetInt(nExpn);

        //存入数据
        sNewNode.dbCoef = dbCoef;
        sNewNode.nExpn = nExpn;
        ListInsert(p, sNewNode);
    }

    //打印多项式链表
    printf("多项式为：");
    PrintPolyn(p);
    return ;

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
    cout<<endl;
}

//打印输出单个节点
void PrintPoly(PLNODE sPTemp) {

    //判断系数
    if (sPTemp.dbCoef < 0) {
        printf("");
    } else if (sPTemp.dbCoef > 0) {
        printf("+");
    } else {
        return ;
    }

    if (sPTemp.nExpn == 0) {  //指数为零，直接输出系数
        cout<<sPTemp.dbCoef;
    } else if(sPTemp.dbCoef==1) {  //当系数为1时
        if (sPTemp.nExpn == 1) {
            cout<<"x";
        } else {
            cout<<"x^"<<sPTemp.nExpn;
        }
    } else if (sPTemp.dbCoef == -1) {
        if (sPTemp.nExpn == 1) {
            cout<<"x";
        } else{
            cout<<"x^"<<sPTemp.nExpn;
        }
    } else {
        if (sPTemp.nExpn == 1) {
            cout<<sPTemp.dbCoef<<"x";
        } else {
            cout<<sPTemp.dbCoef<<"x^"<<sPTemp.nExpn;
        }
    }
}
