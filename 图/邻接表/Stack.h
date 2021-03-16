#ifndef STACH_H
#define STACH_H
#include"Vertex.h"
#include<iostream>
#include<stdlib.h>

#define STACK_INIT_SIZE 100     //栈的空间初始分配量
#define STACKINCREMENT 10       //栈的空间分配增量

//状态码
#define OK 0
#define FALSE 1
#define OVERFLOW 2

typedef int Status;				//返回状态

//栈的顺序存储
typedef struct Stack {
    int *base;          //基指针 在栈构造之前和销毁之后都为NULL 存Node的下标
    int *top;           //栈顶指针 指向栈顶 存Node的下标
    int stackSize;      //栈的大小
}SqlStack;

Status InitStack(SqlStack &s);        //创造一个空栈
Status DestoryStack(SqlStack &s);      //销毁一个栈 栈将不存在
bool StackEmpty(SqlStack &s);     //若s为空栈返回TRUE 否则返回FALSE
Status Push(SqlStack &s, int e);  //插入e为新的栈顶元素
bool Pop(SqlStack &s, int &e);  //若栈不为空，删除栈顶元素并用e返回值并返回true 否则返回false
Status StackTraverse(SqlStack s);  //遍历栈


Status InitStack(SqlStack &s) {
    //给栈分配空间
    s.base = (int *) malloc(STACK_INIT_SIZE*sizeof(int));
    if (!s.base) exit(OVERFLOW);  //给栈分配空间失败
    s.top = s.base;  //首尾指针指同一个
    s.stackSize = STACK_INIT_SIZE;
    return OK;
}

bool StackEmpty(SqlStack &s) {
    if ( s.base!=NULL && s.base!=s.top )
        return false;
    return true;
}

Status Push(SqlStack &s, int e) {
    //判断栈满，追加存储空间
    if (s.top-s.base>=s.stackSize) {
        s.base = (int *) realloc(s.base, (s.stackSize + STACKINCREMENT )*sizeof(int));
        if (!s.base) exit(OVERFLOW);
        s.top = s.base+s.stackSize;  //顶部指针重新指
        s.stackSize+=STACKINCREMENT;  //栈总空间加上STACKINCREMENT
    }
    *s.top = e;
    s.top++;
    return OK;
}

bool Pop(SqlStack &s, int &e) {
    //判断栈是否为空
    if (StackEmpty(s)) return false;
    s.top--;
    e = *s.top;
    return true;
}

#endif