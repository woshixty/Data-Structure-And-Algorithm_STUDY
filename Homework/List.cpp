#include"List.h"
#include"Object.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

int rand_number() {
    int number=rand();
    return number%4;
}

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
    right_head=down_head=first=NULL;
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
    if(first==NULL) {
        cout<<"生态系统为空"<<endl;
        return ;
    }
    down_head=right_head=first;
    for( ; down_head!=NULL; down_head=down_head->down) {
        for (right_head=down_head; right_head!=NULL; right_head=right_head->right) {
            if(right_head->space->name=='2') {
                if(right_head->space->gender==0) {
                    cout<<" "<<'a';
                } else {
                    cout<<" "<<'A';
                }
            } else if(right_head->space->name=='3') {
                if(right_head->space->gender==0) {
                    cout<<" "<<'b';
                } else {
                    cout<<" "<<'B';
                }
            } else if(right_head->space->name=='1'){
                cout<<" "<<'+';
            }else {
                cout<<" "<<right_head->space->name;
            }
        } 
        cout<<'\n';
    }
}

void List::Clear() {
    down_head=right_head=first;
    for( ; down_head!=NULL; down_head=down_head->down) {
        for (right_head=down_head; right_head!=NULL; right_head=right_head->right) {
            right_head->space->action=false;
        } 
    }
}

void List::Grass_Multiply(Node *p) {
    if(p->space->action)
        return ; 

    Node *find_node=Circle(p, ' ');

    if (find_node == NULL)
        return ;

    delete find_node->space;
    find_node->space=new Grass();
    p->space->action=true;
    find_node->space->action=true;
}

Node * List::Circle(Node * p, char ch) {
    int number,flag=1;
    number=rand_number();
    while(flag<=4) {
        switch (number) {
            case 0:
                if (p->up!=NULL && p->up->space->name == ch ) {
                    return p->up;
                }
                if(p->up!=NULL && p->up->right!=NULL && p->up->right->space->name == ch ) {
                    return p->up->right;
                }
                break;

            case 1:
                if (p->right!=NULL && p->right->space->name == ch ) {
                    return p->right;
                }
                if(p->right!=NULL && p->right->down!=NULL && p->right->down->space->name == ch ) {
                    return p->right->down;
                }
                break;

            case 2:
                if (p->down!=NULL && p->down->space->name == ch ) {
                    return p->down;
                }
                if(p->down!=NULL && p->down->left!=NULL && p->down->left->space->name == ch ) {
                    return p->down->left;
                }
                break;

            case 3:
                if (p->left!=NULL && p->left->space->name == ch ) {
                    return p->left;
                }
                if(p->left!=NULL && p->left->up!=NULL && p->left->up->space->name == ch ) {
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
    return NULL;
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

bool List::Herbiovre_Multiply(Node *p, char ch) {
    if(p->space->gender==1)
        return false;
    Node *p_find;
    Herbivore *p_her=(Herbivore *)p->space;
    if(p_her->pregnancy==1) {
        p_find=Circle(p, '3');
        if(p_find!=NULL)
            return false;
        if(find_male(p, '2')) {
            p_her->pregnancy=0;
            p_her->action=true;
            return true;
        }
    } else if(p_her->pregnancy==0) {
        p_find=Circle(p, ' ')   ;
        if(p_find==NULL) {
            p_find=Circle(p, '1');
            if(p_find==NULL) 
                return false;
            else {
                delete p_find->space;
                p_find->space=new Herbivore();
                p_her->action=true;
                p_find->space->action=true;
                p_her->pregnancy=1;
                return true;
            }
        } else {
            delete p_find->space;
            p_find->space=new Herbivore();
            p_her->action=true;
            p_find->space->action=true;
            p_her->pregnancy=1;
            return true;
        }
    }
    return false;
}

bool List::Predator_Multiply(Node *p, char ch) {
    if(p->space->gender==1)
        return false;
    Node *p_find;
    Predator *p_her=(Predator *)p->space;
    if(p_her->pregnancy==1) {
        if(find_male(p, '3')) {
            p_her->pregnancy=0;
            p_her->action=true;
            return true;
        }
    } else if(p_her->pregnancy==0) {
        p_find=Circle(p, ' ');
        if(p_find==NULL) {
            p_find=Circle(p, '1');
            if(p_find==NULL) 
                return false;
            else {
                delete p_find->space;
                p_find->space=new Predator();
                p_find->space->action=true;
                p_her->action=true;
                p_her->pregnancy=1;
                return true;
            }
        } else {
            delete p_find->space;
            p_find->space=new Predator();
            p_find->space->action=true;
            p_her->action=true;
            p_her->pregnancy=1;
            return true;
        }
    }
    return false;
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

void List::move(Node *p) {
    Node *sp=Circle(p, ' ');
    if(sp==NULL) 
        sp=Circle(p, '1');
    if(sp!=NULL) {
        Herbivore *p2;
        Predator *p3;
        delete sp->space;
        sp->space=p->space;
        p->space=new Area();
        sp->space->action=true;
        if(sp->space->name=='2') {
            p2=(Herbivore *)sp->space;
            p2->age_down();
        } else {
            p3=(Predator *)sp->space;
            p3->age_down();
        }
        return ;
    }
}

void List::Herbivore_bout(Node *p) {
    if(p->space->action)
        return ; 
    Herbivore *p_her=(Herbivore *)p->space;
    if(p->space->gender==0 && p_her->pregnancy==0)
        if(Herbiovre_Multiply(p, '2'))
            return ;
    if(Eating(p, '1')) 
        return ; 
    if(Herbiovre_Multiply(p, '2'))
        return ;
    move(p);
}

void List::Predator_bout(Node *p) {
    if(p->space->action)
        return ;
    Predator *p_pre=(Predator *)p->space;
    if(p->space->gender==0 && p_pre==0)
        if(Predator_Multiply(p, '3'))
            return ;
    if(Eating(p, '2'))
        return ;
    if(Predator_Multiply(p, '3'))
        return ;
    move(p);
}

void List::one_bout() {
    down_head=right_head=first;
    for( ; down_head!=NULL; down_head=down_head->down) {
        for (right_head=down_head; right_head!=NULL; right_head=right_head->right) {
            if(right_head->space->name=='1') {
                Grass_Multiply(right_head);
                Grass *p_gra=(Grass *)right_head->space;
                if(p_gra->age_down()) {
                    delete right_head->space;
                    right_head->space=new Area();
                }
            }
        } 
    }

    down_head=right_head=first;
    for( ; down_head!=NULL; down_head=down_head->down) {
        for (right_head=down_head; right_head!=NULL; right_head=right_head->right) {
            switch (right_head->space->name)
            {
            case '2':{
                Herbivore_bout(right_head);
                Herbivore *p_her=(Herbivore *)right_head->space;
                if(p_her->age_down()) {
                    delete right_head->space;
                    right_head->space=new Area();
                }
                break;
            }
            
            case '3':{
                Predator_bout(right_head);
                Predator *p_her=(Predator *)right_head->space;
                if(p_her->age_down()) {
                    delete right_head->space;
                    right_head->space=new Area();
                }
                break;
            }

            default:
                break;
            }
        } 
    }
    Clear();
}

void List::menu() {
    cout<<"生态系统规则:"<<endl;
    cout<<"进食: 食草动物与食肉动物只能捕食九宫格内的食物"<<endl;
    cout<<"繁殖: 草可以在九宫格内的空地上繁殖子代草; 磁性动物要先经过受精才能繁殖,也就是十字格内要有雄性动物,然后下个回合才会繁殖子代; 若食草动物九宫格内有食肉动物,则不会受精"<<endl;
    cout<<"移动: 动物可以移动到九宫格内空地与草的地方"<<endl;
    cout<<"-----------------------------------------------------------------"<<endl;
    cout<<"指令信息:"<<endl;
    cout<<"1.生成一个生态系统"<<endl;
    cout<<"2.读取一个生态系统"<<endl;
    cout<<"3.打印该生态系统"<<endl;
    cout<<"4.存储该生态系统"<<endl;
    cout<<"5.删除该生态系统"<<endl;
    cout<<"6.生态系统演化x轮"<<endl;
    cout<<"7.退出系统"<<endl;
}

void List::delete_list() {
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
    right_head=down_head=first=NULL;
}

bool List::judge_null() {
    if(first==NULL)
        return true;
    return false;
}


bool List::read_file() {
    char ch,s;
    if(!judge_null()) {
        cout<<"是否删除已经存在的生态系统(y/n)"<<endl;
        cin>>ch;
        s=getchar();
        if(ch=='y')
            delete_list();
        else
            return false;
    }

    char data[100];
    ifstream infile;
    string name;

    cout<<"请输入读入文件名:"<<endl;
    cin>>name;
    ch=getchar();
    infile.open(name);
    Node *p_tail;
    Node *p_before;

    infile.getline(data, 100);
    while(data[0]!='\0') {
        p_before=NULL;
        down_head=NULL;
        for (int i = 0; data[i]!='\0'; i++){
            p_tail=new Node(data[i]);

            if(down_head==NULL && right_head==NULL)
                first=right_head=down_head=p_tail;

            if(down_head==NULL)
                down_head=p_tail;

            if(p_before==NULL) {
                p_before=p_tail;
            } else {
                p_before->right=p_tail;
                p_tail->left=p_before;
                p_before=p_tail;
            }
        }

        if(right_head!=down_head) {
            Node *p1,*p2;
            p1=right_head;
            p2=down_head;
            while (p1!=NULL && p2!=NULL) {
                p1->down=p2;
                p2->up=p1;
                p1=p1->right;
                p2=p2->right;
            }
            right_head=right_head->down;
        }

        infile.getline(data, 100);
    }

    if(first==NULL) {
        cout<<"文件为空"<<endl;
        return false;
    }
    return true;
}

bool List::save_file() {
    if(judge_null()) {
        cout<<"生态系统为空"<<endl;
        return false;
    }

    char ch;
    ofstream outfile;
    string name;

    cout<<"请输入保存文件名:"<<endl;
    cin>>name;
    ch=getchar();
    outfile.open(name);

    down_head=right_head=first;
    for( ; down_head!=NULL; down_head=down_head->down) {
        for (right_head=down_head; right_head!=NULL; right_head=right_head->right) {
            if(right_head->space->name=='2') {
                if(right_head->space->gender==0) {
                    outfile<<'a';
                } else {
                    outfile<<'A';
                }
            } else if(right_head->space->name=='3') {
                if(right_head->space->gender==0) {
                    outfile<<'b';
                } else {
                    outfile<<'B';
                }
            } else if(right_head->space->name=='1'){
                outfile<<'+';
            }else {
                outfile<<right_head->space->name;
            }
        }
        outfile<<"\n"; 
    }

    return true;
}




