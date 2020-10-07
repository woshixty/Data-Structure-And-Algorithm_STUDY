#include <stdio.h>

typedef struct PloyNode *Ploynimial;
struct PloyNode
{
    int coef;       //系数
    int expon;      //指数
    Ploynimial link;
};

