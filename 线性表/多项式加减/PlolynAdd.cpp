#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<iostream>
#include"StructDefine.h"
#include"Polyn.h"
using namespace std;


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

//用于输入数据，创建一元多项式并打印输出
void InputData(int nOrder, PLinkList &sPolyn) {
    
    //创建空链表
    CreatePolyn(sPolyn);

    printf("请输入项数\n");
    //使用GetInt()函数输入项数并检测项数是否为整数，且指数需大于0
    int num;
    GetInt(num);

    PLNODE sNewNode;  //定义新的结点

    int a[100];  //存放输入过的指数

    for (int i = 0; i < num; i++) {
        printf("请输入第%d项的系数\n", i+1);
        //使用 cin.fail() 检测系数是否合法
        int dbCoef;
        cin>>dbCoef;
        if (cin.fail() && dbCoef==0)
            return ;
        
        printf("请输入第%d项的指数\n", i+1);
        //使用getInt检测输入的指数是否合法
        int nExpn;
        GetInt(nExpn);

        //存入数据
        sNewNode.dbCoef = dbCoef;
        sNewNode.nExpn = nExpn;
        ListInsert(sPolyn, sNewNode);
    }

    //打印多项式链表
    PrintPolyn(sPolyn);
}

int main() {
    PLinkList p;
    InputData(1, p);
    return 0;
}