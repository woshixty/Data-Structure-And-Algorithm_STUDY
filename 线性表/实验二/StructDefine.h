#ifndef STRUCTDEFINE
#define STRUCTDEFINE

typedef struct PLNODE
{
    double dbCoef;          //系数域
    int nExpn;              //指数域
    struct PLNODE *next;    //指针域，指向下一节点
}PLONDE;
typedef PLNODE *PLinkList;

#endif