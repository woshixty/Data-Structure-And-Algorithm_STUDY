#include <iostream>
using namespace std;

class father {
    public:
    father(){ data=1; }
    ~father(){}
        int data;
        void out(){ cout<<data<<endl; }
};

class son :public father{
    public:
        son(){ age=2; }
        ~son(){}
        int age;
        void hhh(){ cout<<age<<endl; }
};

int main() {
    father *f=new son();
    son *s=(son *)f;
    s->hhh();
    s->out();
}