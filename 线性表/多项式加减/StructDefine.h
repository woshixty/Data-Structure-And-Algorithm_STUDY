#ifndef STRUCTDEFINE
#define STRUCTDEFINE

typedef struct PLNODE
{
    double dbCoef;      //系数域
    int nExpn;          //指数域
    struct PLNODE *NODE; 
}PLONDE;
typedef PLNODE *PLinkList;

#endif 