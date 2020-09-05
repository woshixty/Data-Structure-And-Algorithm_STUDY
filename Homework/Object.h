#ifndef _OBJECT_H_
#define _OBJECT_H_

class Space {
    public:
        char name;
        bool action;
        int gender;
        Space(char n);
        Space(char n, int i);
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
        void multiply();
        bool age_down();
};

class Herbivore :public Space{
    public:
        int age;
        int pregnancy; 
        Herbivore():Space('2'){ 
            pregnancy=1;
            age=8;
        }
        Herbivore(int i):Space('2', i){
            pregnancy=1;
            age=8;
        }
        ~Herbivore();
        bool age_down();
        void age_up();
}; 


class Predator :public Space{
    public:
        int age;
        int pregnancy;
        Predator():Space('3'){
            pregnancy=1;
            age=6;
        }
        Predator(int i):Space('3', i){
            pregnancy=1;
            age=6;
        }
        ~Predator();
        bool age_down();
        void age_up();
};

class Node{
    public:
        Space *space;
        Node *up;
        Node *down;
        Node *left;
        Node *right;
        Node(int name);
        Node(char ch);
};

#endif