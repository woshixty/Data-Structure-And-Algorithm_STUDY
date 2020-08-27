#include <iostream>
#include <cstdlib>
using namespace std;

int rand_number() {
    int number=rand();
    return number%4;
}

class Space {
    public:
        char name;
        bool action;
        int gender;
        Space(char n){
            name=n;
            action=false;
            gender=rand_number()%2;
        }
        ~Space(){}
};

class Area :public Space{
    public:
        Area():Space(' '){}
        ~Area();
};

class Grass :public Space{
    private:
        int age;
    public:
        Grass():Space('1'){ age=50; }
        ~Grass();
        void multiply(){ action=false; }
        bool age_down(){ 
            age--;
            if(age<=0) 
                return true;
            return false; 
        }
};

class Herbivore :public Space{
    public:
        int age;
        int pregnancy; 
        Herbivore():Space('2'){ 
            pregnancy=0;
            age=8;
        }
        ~Herbivore();
        void multiply();
        void move();
        void eat();
        bool age_down(){ 
            age--;
            if(age<=0) 
                return true;
            return false; 
        }
        void age_up(){
            age=8;
        }
};

class Predator :public Space{
    public:
        int age;
        int pregnancy;
        Predator():Space('3'){
            pregnancy=0;
            age=6;
        }
        ~Predator();
        void multiply();
        void move();
        void eat();
        bool age_down(){ 
            age--;
            if(age<=0) 
                return true;
            return false; 
        }
        void age_up(){
            age=6;
        }
};

class Node{
    public:
        Space *space;
        Node *up;
        Node *down;
        Node *left;
        Node *right;
        Node(int name){
            switch (name)
            {

            case 1:
                space=new Grass();
                break;

            case 2:
                space=new Herbivore();
                break;

            case 3:
                space=new Predator();
                break;
            
            default:
                space=new Area();       //name为4
                break;
            }
            up=down=left=right=NULL;
        }
};





//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------


class List{
    private:
        Node *first, *down_head, *right_head;
    public:
        List();
        ~List();
        void Make_list(int x);
        void Print();
        // void Print1();
        // void Print2();
        void Clear();
        void Grass_Multiply(Node *p);
        Node * Circle(Node *p, char ch);
        void test();
        // void test2();
        bool Eating(Node *p, char ch);
        bool Animal_Multiply(Node *p, char ch);
        bool find_male(Node *p, char ch);
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

void List::Make_list(int x) {
    Node *p=NULL;
    Node *tail=NULL;
    for (int i = 1; i <= x; i++) {

        for (int j = 1; j <= x; j++) {
            if(j==1) {
                if(i==1)
                    first=down_head=right_head=new Node(rand_number());
                else
                    right_head=new Node(rand_number());
                tail=right_head;
            } else {
                p=new Node(rand_number());
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
            cout<<" "<<right_head->space->name;
        } 
        cout<<'\n';
    }
}

// void List::Print1() {
//     right_head=first;
//     for( ; right_head->right!=NULL; )
//         right_head=right_head->right;
//     for( ; right_head!=NULL; ) {
//         cout<<right_head->space->name<<endl;
//         right_head=right_head->down;
//     } 
// }

// void List::Print2() {
//     down_head=first;
//     down_head=down_head->down;
//     down_head=down_head->down;
//     for( ; down_head!=NULL; ) {
//         cout<<down_head->space->name<<"  ";
//         down_head=down_head->right;
//     }
//     cout<<'\n';
// }

void List::Clear() {
    down_head=right_head=first;
    for( ; down_head!=NULL; down_head=down_head->down) {
        for (right_head=down_head; right_head!=NULL; right_head=right_head->right) {
            right_head->space->action=false;
        } 
    }
}

Node * List::Circle(Node * p, char ch) {
    int number,flag=1;
    number=rand_number();
    // cout<<'('<<number<<' '<<flag<<')'<<endl;
    while(flag<=4) {
        // cout<<number<<"  "<<flag<<endl;
        switch (number) {
            case 0:
                if (p->up!=NULL && p->up->space->name == ch ) {
                    // cout<<"上边"<<endl;
                    return p->up;
                }
                if(p->up!=NULL && p->up->right!=NULL && p->up->right->space->name == ch ) {
                    // cout<<"上右"<<endl;
                    return p->up->right;
                }
                break;

            case 1:
                if (p->right!=NULL && p->right->space->name == ch ) {
                    // cout<<"右边"<<endl;
                    return p->right;
                }
                if(p->right!=NULL && p->right->down!=NULL && p->right->down->space->name == ch ) {
                    // cout<<"右下"<<endl;
                    return p->right->down;
                }
                break;

            case 2:
                if (p->down!=NULL && p->down->space->name == ch ) {
                    // cout<<"下边"<<endl;
                    return p->down;
                }
                if(p->down!=NULL && p->down->left!=NULL && p->down->left->space->name == ch ) {
                    // cout<<"下左"<<endl;
                    return p->down->left;
                }
                break;

            case 3:
                if (p->left!=NULL && p->left->space->name == ch ) {
                    // cout<<"左边"<<endl;
                    return p->left;
                }
                if(p->left!=NULL && p->left->up!=NULL && p->left->up->space->name == ch ) {
                    // cout<<"左上"<<endl;
                    return p->left->up;
                }
                break;
            
            default:
                break;
        }
        number++;
        number=number%4;
        flag++;
    }
    // cout<<"没找着"<<endl;
    return NULL;
}

bool List::find_male(Node * p, char ch) {

    if(p->up!=NULL && p->up->space->name==ch) {
        if(p->up->space->gender==1)
            return true;
    }

    if(p->right!=NULL && p->right->space->name==ch) {
        if(p->right->space->gender==1)
            return true;
    }

    if(p->down!=NULL && p->down->space->name==ch) {
        if(p->down->space->gender==1)
            return true;
    }

    if(p->left!=NULL && p->left->space->name==ch) {
        if(p->left->space->gender==1)
            return true;
    }

    return false;
}

void List::Grass_Multiply(Node *p) {
    if(p->space->action)
        return ; 

    // cout<<1<<endl;

    Node *find_node=Circle(p, ' ');

    // cout<<2<<endl;

    if (find_node == NULL)
        return ;

    // cout<<3<<endl;

    delete find_node->space;
    find_node->space=new Grass();
    p->space->action=true;
    find_node->space->action=true;

    // cout<<4<<endl;
}

bool List::Eating(Node *p, char ch) {
    Node * find=Circle(p, ch);
    if(find==NULL)
        return false;
    
    Herbivore *p2;
    Predator *p3;
    if(p->space->name=='2') {
        p2=(Herbivore *)p->space;
        p2->age_up();
        p2->action=true;
        delete find->space;
        find->space=p2;
    } else {
        p3=(Predator *)p->space;
        p3->age_up();
        p3->action=true;
        delete find->space;
        find->space=p3;
    }
    p->space=new Area();
    return true;
}


// void List::test() {
//     down_head=right_head=first;
//     for( ; down_head!=NULL; down_head=down_head->down) {
//         for (right_head=down_head; right_head!=NULL; right_head=right_head->right) {
//             if(right_head->space->name=='1') {
//                 // cout<<"++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
//                 // cout<<"hello"<<endl;
//                 Grass_Multiply(right_head);
//             }
//         } 
//     }
// }

// void List::test2() {
//     down_head=right_head=first;
//     for( ; down_head!=NULL; down_head=down_head->down) {
//         for (right_head=down_head; right_head!=NULL; right_head=right_head->right) {
//             if(right_head->space->name=='2') {
//                 cout<<"++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
//                 Node *find=Circle(right_head, '1');
//                 if(find!=NULL)
//                     cout<<"yes"<<endl;
//                 else
//                     cout<<"no"<<endl;
//             }
//         } 
//     }
// }

void List::test() {
    down_head=right_head=first;
    for( ; down_head!=NULL; down_head=down_head->down) {
        for (right_head=down_head; right_head!=NULL; right_head=right_head->right) {
            if(right_head->space->name=='2' && !right_head->space->action) {
                // cout<<"++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
                // cout<<"hello"<<endl;
                Eating(right_head, '1');
            }
        } 
    }
}

bool List::Animal_Multiply(Node *p, char ch) {
    if(ch=='2') {
        Node *p_find=Circle(p, '3');
        if(p_find!=NULL)
            return false;
    }
    return false;
}




int main() {
    srand(time(NULL));
    List list;
    list.Make_list(8);
    list.Print();
    list.test();
    cout<<"----------------------------"<<endl;
    // list.Print();
    // list.test2();
    list.Print();
    return 0;
}