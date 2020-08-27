#include <iostream>
using namespace std;

class Node{
    public:
        int data;
        Node *up;
        Node *down;
        Node *left;
        Node *right;
        Node(int da=0){
            data=da;
            up=down=left=right=NULL;
        }
};

class List{
    private:
        Node *first, *down_head, *right_head;
    public:
        List();
        ~List();
        void Insert(int x);
        void Print();
};

List::List() {
    first=down_head=right_head=NULL;
}

List::~List() {
    down_head=first;
    while (down_head!=NULL) {
        first=first->down;
        right_head=down_head;
        Node *p;
        while(right_head!=NULL) {
            p=right_head;
            right_head=right_head->right;
            delete p;
        }
        down_head=first;
    }
}

void List::Insert(int x) {
    Node *p=NULL;
    Node *tail=NULL;
    for (int i = 1; i <= x; i++) {

        for (int j = 1; j <= x; j++) {
            if(j==1) {
                if(i==1)
                    first=down_head=right_head=new Node(i);
                else
                    right_head=new Node(i);
                tail=right_head;
            } else {
                p=new Node(i);
                tail->right=p;
                p->left=tail;
                tail=tail->right;
            }
        }

        if(i!=1) {
            Node *p1=down_head,*p2=right_head;
            for(; down_head!=NULL; ) {

                down_head->down=right_head;
                right_head->up=down_head;

                down_head=down_head->right;
                right_head=right_head->right;
            }

            down_head=p1;
            right_head=p2;
            down_head=down_head->down;
        }

    }
}

void List::Print() {
    down_head=right_head=first;
    for( ; down_head!=NULL; down_head=down_head->down) {
        for (right_head=down_head; right_head!=NULL; right_head=right_head->right) {
            cout<<" "<<right_head->data<<" ";
        } 
        cout<<'\n';
    }
}

int main() {
    List list;
    list.Insert(5);
    list.Print();
    return 0;
}