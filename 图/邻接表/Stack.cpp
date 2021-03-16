#include"Stack.h"
#include<iostream>
using namespace std;

int main() {
    SqlStack s;
    int e;
    InitStack(s);
    Push(s, 2);
    Push(s, 1);
    Push(s, 9);
    Push(s, 0);
    Pop(s, e);
    cout<<e<<endl;
    Push(s, 1);
    Push(s, 88);
    Push(s, 54);
    Push(s, 2);
    Pop(s, e);
    cout<<e<<endl;

    while (Pop(s, e)) {
        cout<<e<<endl;
    }
    
    Push(s, 1);
    Push(s, 88);
    Push(s, 54);
    Push(s, 2);
    cout<<"++++++++++++++"<<endl;

    while (Pop(s, e)) {
        cout<<e<<endl;
    }

    return 0;
}
