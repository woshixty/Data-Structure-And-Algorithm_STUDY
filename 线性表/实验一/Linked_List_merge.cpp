#include<stdio.h>
#include<stdlib.h>

typedef struct NODE {
    int data;
    struct NODE* next;
}LNode, *PNode;


void insert( int data, PNode &head ) {

    PNode p = head;
    PNode pre;
    PNode NewNode = (PNode) malloc(sizeof(LNode));

    //分配空间失败
    if (NewNode == NULL) {
        exit(0);
    }

    //初始化
    NewNode->data = data;
    NewNode->next = NULL;

    //头指针为NULL
    if(head == NULL) {
        head = NewNode;
        return ;
    }

    //新节点data比头指针小
    if (NewNode->data <= head->data) {

        //有相等的元素
        if (NewNode->data == p->data) {
            return ;
        }
        NewNode->next = head;
        head = NewNode;
        return ;
    }
    

    //按从小到大插入
    for ( ; p!=NULL; p=p->next) {
        if (NewNode->data <= p->data) {

            //有相等的元素
            if (NewNode->data == p->data) {
                return ;
            }
            
            pre->next = NewNode;
            NewNode->next = p;
            return ;
        }
        pre = p;
    }

    pre->next = NewNode;
    return ;
}

void merge(PNode &pa, PNode pb) {

    //遍历pa的指针
    PNode a = pa;

    //pa的前一个指针
    PNode pre = NULL;

    //遍历b
    for ( ; pb != NULL; pb=pb->next) {

        //如果b比a的头要小
        if (a!=NULL && pb->data < a->data && pre == NULL ) {
            PNode c = (PNode) malloc(sizeof(LNode));
            if (c==NULL) 
                exit(0);
            *c = *pb;
            c->next = pa;
            pa = c;
            a = pa;
        }
        
        //遍历a找合适的位置插入
        for ( ; a!=NULL; a = a->next ) {

            if (pb->data <= a->data) {

                if (pb->data == a->data) 
                    break;
                
                PNode c = (PNode) malloc(sizeof(LNode));
                if (c==NULL) 
                    exit(0);
                *c = *pb;
                pre->next = c;
                c->next = a;
                pre = pre->next;
                break;
            }
            pre = a;
        }
        
        if (a==NULL) {
            PNode c = (PNode) malloc(sizeof(LNode));
            if (c==NULL)
                exit(0);
            c->data = pb->data;
            pre->next = c;
            c->next = NULL;
            pre = pre->next;
        }
        
    }
    
}

void print(PNode p) {
    for ( ; p!= NULL; p = p->next)
        printf("%d ", p->data);
    printf("\n");
}

void init(PNode &p, int num) {
    int data;
    for (int i = 0; i < num; i++) {
        scanf("%d", &data);
        insert(data, p);
    }
}

int main() {

    PNode pa = NULL;
    PNode pb = NULL;
    int num;

    printf("输入第一个链表的节点数:");
    scanf("%d", &num);
    init(pa, num);

    printf("输入第二个链表的节点数:");
    scanf("%d", &num);
    init(pb, num);

    printf("第一个链表:");
    print(pa);
    printf("第二个链表:");
    print(pb);

    merge(pa, pb);
    printf("归并之后:");
    print(pa);

    return 0;
}