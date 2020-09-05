#include"Object.h"
#include <cstdlib>

int rand_number() {
    int number=rand();
    return number%4;
}

Space::Space(char n){
    name=n;
    action=false;
    gender=rand_number()%2;
}

Space::Space(char n, int i){
    name=n;
    action=false;
    gender=i;
}

void Grass::multiply(){ 
    action=false; 
}

bool Grass::age_down(){ 
    age--;
    if(age<=0) 
        return true;
    return false; 
}

bool Herbivore::age_down(){ 
            age--;
            if(age<=0) 
                return true;
            return false; 
        }

void Herbivore::age_up(){
            age=8;
        }

bool Predator::age_down(){ 
            age--;
            if(age<=0) 
                return true;
            return false; 
        }

void Predator::age_up(){
            age=6;
        }

Node::Node(int name){
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

Node::Node(char ch){
            switch (ch)
            {
            case 'A':
                space=new Herbivore(1);
                break;

            case 'a':
                space=new Herbivore(0);
                break;

            case '+':
                space=new Grass();
                break;

            case ' ':
                space=new Area();
                break;

            case 'B':
                space=new Predator(1);
                break;

            case 'b':
                space=new Predator(0);
                break;
                        
            default:
                break;
            }
            up=down=left=right=NULL;
        }













