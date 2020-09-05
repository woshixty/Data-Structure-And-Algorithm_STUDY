#include"List.h"
#include"Object.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

void one(List &p_list) {

    char ch,s;
    if(!p_list.judge_null()) {
        cout<<"是否删除已经存在的生态系统(y/n)"<<endl;
        cin>>ch;
        s=getchar();
        if(ch=='y')
            p_list.delete_list();
        else
            return ;
    }

    int count=1;
    cout<<"请输入生态系统大小"<<endl;
        do {
            if(count<1)
                cout<<"大小必须大于0"<<endl;
            cin>>count;
        } while (count<1);
    p_list.Make_list(count);
}

void six(List &p_list) {
    if(p_list.judge_null()) {
        cout<<"生态系统为空"<<endl;
        return ;
    }

    int x=1;
    cout<<"请输入生态系统演化轮次"<<endl;
        do {
            if(x<1)
                cout<<"最小为1"<<endl;
            cin>>x;
        } while (x<1);
    
    for (int i = 0; i < x; i++) 
        p_list.one_bout();
    
}

int main() {
    srand(time(NULL));
    List list;
    list.menu();
    int ins=1;
    while(true) {
        cout<<"++++++++++++++++++++++++++++++++++++++++++"<<endl;
        cout<<"请输入指令编号"<<endl;
        do {
            if(ins>7 || ins<1)
                cout<<"无效指令:"<<endl;
            cin>>ins;
        } while (ins>7 || ins<1);

        switch (ins) {
        case 1:
            one(list);
            break;

        case 2:
            if(list.read_file())
                cout<<"读取成功!"<<endl;
            else
                cout<<"读入失败!"<<endl;
            break;

        case 3:
            list.Print();
            break;

        case 4:
            if(list.save_file())
                cout<<"保存成功!"<<endl;
            else
                cout<<"保存失败!"<<endl;
            break;

        case 5:
            list.delete_list();
            break;

        case 6:
            six(list);
            break;

        case 7:
            exit(0);
            break;
        
        default:
            break;
        }

        ins=1;
    }
    return 0;
}