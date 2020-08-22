#include <stdio.h>
#include <stdlib.h>

typedef struct LNode *List; 
struct LNode
{
    int data;
    List next;
};
struct LNode L;
List Ptrl;

//广义表
/*
typedef struct GNode *GList;
struct GNode {
    int Tag;
    union {
        int data;
        GList SubList;
    }URegion;
    GList next;
};
*/

//求表长
int Length(List Ptrl)
{
    List p=Ptrl;
    int j=0;
    while(p) {
        p=p->next;
        j++;
    }
    return j;
}

//查找(序号)
List FindKth(int K, List Ptrl)
{
    List p=Ptrl;
    int i;
    for (i = 0; i < K; i++) {
        p=p->next;
        if(p==NULL)
            break;
    }
    if(i==K) return p; 
    return NULL;
}

//查找(值)
List Find(int K, List Ptrl)
{
    List p=Ptrl;
    for (; ;) {

        if(p->data==K)
            return p;
        
        p=p->next;

        if(p==NULL)
            return NULL;
    }
}

//插入
List Insert(int X, int i, List Ptrl) {
    List p, s;
    if(i==1) {
        s=(List) malloc(sizeof(struct LNode));
        s->data=X;
        s->next=Ptrl;
        return s;
    }
    p=FindKth(i-1, Ptrl);
    if(p==NULL) {
        printf("参数错误");
        return NULL;
    } else {
        s = (List) malloc(sizeof(struct LNode));
        s->data=X;
        s->next=p->next;
        p->next=s;
        return Ptrl;
    }
}

//删除(序号)
List Delete(int i, List Ptrl)
{
    List p, s;
    if(i==1) {
        s=Ptrl;
        if(Ptrl!=NULL)
            Ptrl=s->next;
        else 
            return NULL;
        free(s);
        return Ptrl;
    } 
    p=FindKth(i-1, Ptrl);
    if(p==NULL) {
        printf("第%d个节点不存在", i-1);
        return NULL;
    } else if(p->next==NULL) {
        printf("第%d个节点不存在", i);
        return NULL;
    } else {
        s=p->next;
        p->next=s->next;
        free(s);
        return Ptrl;
    }
    
}

int main() {
}