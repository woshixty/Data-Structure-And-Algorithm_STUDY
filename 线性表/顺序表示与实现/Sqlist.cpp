#define LIST_INTT_SIZE 100
#define LISTINCREASEMENT 10

#include<stdio.h>
#include<stdlib.h>

typedef struct {
   int *elem;
   int length;
   int listsize;    
}SqList;

void InitList_Sq(SqList &L) {
   L.elem=(int *) malloc(LIST_INTT_SIZE* sizeof(int));
   if (!L.elem)
   {
    exit(0);
   }

   L.length=0;
   L.listsize=LIST_INTT_SIZE;
}

int ListInsert_Sq(SqList &L, int i, int e) {
   //在顺序表L中第i个位置之前插入新的元素e
   //i的合法值为 1<=i<=ListLength_Sq(L)+1
   
   if (i<1 || i>L.length+1)
   {
      return -1;
   }

   if (L.length>=L.listsize)
   {
      int *newbase=(int *)realloc(L.elem, (L.listsize+LISTINCREASEMENT)*sizeof(int));
      if (!newbase)
      {
         exit(0);
      }
      L.elem=newbase;
      L.listsize+=LISTINCREASEMENT; //增加数字
   }


   //我的实现方式
   int j;
   for ( j = L.length; j > i; j--)
   {
      L.elem[j]=L.elem[j-1];
   }
   L.elem[j]=e;
   L.length++;
   return i;


//   int *q =&L.elem[i-1], *p;
//   for (p=& ( L.elem[L.length-1] ); p>=q; --p) *(p+1)=*p;
//   *q=e;
//   L.length++;
//   return i;
}

void ListDelete_Sq(SqList &L, int i, int e) {
   //删除线性表中的第i个元素并用e返回值
   //i的合法值为1<i<length
   if ((i<1) || (i>L.length))
   {
      return ;
   }
   int *p = &(L.elem[i-1]);
   e = *p;
   int *q =L.elem+L.length-1;

}

void Print_Sqlist(SqList &L) {
   for (int i = 0; i < L.length; i++)
      printf("%d  ", L.elem[i]);
}

int main() {
   SqList list;

   InitList_Sq(list);
   ListInsert_Sq(list, 1, 1);
   ListInsert_Sq(list, 1, 1);
   ListInsert_Sq(list, 1, 1);
   ListInsert_Sq(list, 1, 1);
   ListInsert_Sq(list, 4, 0);

   Print_Sqlist(list); 
   printf("%d", list.length);
   return 0;
}