#ifndef POLYN_H
#define POLYN_H
#include<stdlib.h>
#include<iostream>
#include"StructDefine.h"
using namespace std;


//创建空链表
void CreatePolyn(PLinkList &sPloyn) {
    sPloyn=(PLinkList)malloc(sizeof(PLNODE));

    //判断头节点是否为空
    if (sPloyn == NULL) {
        exit(0);
    }
    
    sPloyn->next=NULL;
}

//将结点插入链表尾部
void ListInsert(PLinkList sPolyn, PLNODE sNewNode) {

    PLinkList sTemp = sPolyn;
    PLinkList psNewNode = (PLinkList)malloc(sizeof(PLNODE));

    //判断psNewNode是否为空
    if (psNewNode == NULL) {
        exit(0);
    }
    
    //将指针对象所指的值改为sNewNode
    
    for ( ; sTemp->next!=NULL; sTemp=sTemp->next) ;

    sTemp->next = psNewNode;  //将结点插入链表尾部
    psNewNode = NULL;   //将尾结点的指向置为空
}

//将链表按指数从小到大排序
PLinkList ListSort();

//打印输出单个节点
void PrintPoly(PLNODE sPTemp) {
    if (sPTemp.nExpn) {  //指数为零，直接输出系数
        cout<<sPTemp.dbCoef;
    } else if(sPTemp.dbCoef==1) {  //当系数为1时
        if (sPTemp.nExpn == 1) {
            cout<<"x";
        } else {
            cout<<"x^"<<sPTemp.nExpn;
        }
    } else if (sPTemp.dbCoef == -1) {
        if (sPTemp.nExpn == 1) {
            cout<<"-x";
        } else{
            cout<<"-x^"<<sPTemp.nExpn;
        }
    } else {
        if (sPTemp.nExpn == 1) {
            cout<<sPTemp.dbCoef<<"x"<<endl;
        } else {
            cout<<sPTemp.dbCoef<<"x^"<<sPTemp.nExpn;
        }
    }
}
//打印输出整个一元多项式
void PrintPolyn(PLinkList &sPloyn) {
    PLinkList &s = sPloyn;
    for ( ; s->next!=NULL; s=s->next) {
        PrintPoly(*s);
    }
}

//将两个一元多项式相加
PLinkList AddPolyn();

//释放链表
void FreePolyn();

#endif