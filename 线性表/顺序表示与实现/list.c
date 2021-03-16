#define LIST_INTT_SIZE 100
#define LISTINCREASEMENT 10

#include<stdio.h>
#include<stdlib.h>

typedef struct Student {
    int *elem;
    int length;
    int size;
}list;

void InitList(list *L) {
    L->elem=(int *)malloc(LIST_INTT_SIZE*(sizeof(int)));
    if (!L->elem)
    {
        exit(0);
    }
    L->length=0;
    L->size=LIST_INTT_SIZE;
}

//按照从小到大的顺序进行插入
int ListInsert(list *L, int e) {
    if (L->length>=L->size)
    {
        int *newbase=(int *)realloc(L->elem, (L->size+LISTINCREASEMENT)*sizeof(int));
        if(!newbase)
        {
            exit(0);
        }
        L->elem=newbase;
        L->size+=LISTINCREASEMENT; 
    }

    int i;
    for (i = 0; i < L->length; i++)
    {
        if (e<L->elem[i])
            break;
    }

    int ex;
    int j=0;
    for (j = i; j < L->length; j++) {
        ex=L->elem[j];
        L->elem[j]=e;
        e=ex;
    }

    L->elem[j] = e;
    L->length++;
    return i; 
}

void ListPrint(list * L) {
    for (int i = 0; i < L->length; i++)
    {
        printf("%d\n", L->elem[i]);
    }
    
}

int main() {
    list *list_sq;
    InitList(list_sq);

    ListInsert(list_sq, 1);
    ListInsert(list_sq, 5);
    ListInsert(list_sq, 4);
    ListInsert(list_sq, 2);
    ListInsert(list_sq, 3);
    ListInsert(list_sq, 6);
    
    ListPrint(list_sq);
    return 0;
}

