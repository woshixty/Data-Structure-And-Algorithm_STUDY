#ifndef _LIST_H_
#define _LIST_H_
#include"Object.h"

class List{
    private:
        Node *first, *down_head, *right_head;
    public:
        List();
        ~List();
        void Make_list(int x);
        void Print();
        void Clear();
        void Grass_Multiply(Node *p);
        Node * Circle(Node *p, char ch);
        bool Eating(Node *p, char ch);
        bool Herbiovre_Multiply(Node *p, char ch);
        bool Predator_Multiply(Node *p, char ch);
        bool find_male(Node *p, char ch);
        void move(Node *p);
        void Herbivore_bout(Node *p);
        void Predator_bout(Node *p);
        void one_bout();
        void menu();
        void delete_list();
        bool judge_null();
        bool read_file();
        bool save_file();
};
 
#endif