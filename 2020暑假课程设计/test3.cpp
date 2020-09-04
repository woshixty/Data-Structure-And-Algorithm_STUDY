#include <fstream>
#include <iostream>
using namespace std;
 
int main ()
{
    
   char data[300];
   char ch;
 
   // 以写模式打开文件
   ofstream outfile;

   // outfile.open("afile.dat");
   string name("test.txt");
   cin>>name;
   ch=getchar();
   // outfile.open(name);
 
//    cout << "Writing to the file" << endl;
//    cout << "Enter your name: "; 
//    cin.getline(data, 100);

//    outfile<<"hello"<<endl;
 
   // 向文件写入用户输入的数据
//    outfile << data << endl;
 
//    cout << "Enter your age: "; 
//    cin >> data;
//    cin.ignore();
   
   // 再次向文件写入用户输入的数据
//    outfile << data << endl;
 
   // 关闭打开的文件
//    outfile.close();
 
   // 以读模式打开文件
   ifstream infile; 
   infile.open(name); 
 
   cout << "Reading from the file" << endl; 
//    infile >> data; 
 
   // 在屏幕上写入数据
//    cout << data << endl;
   
   // 再次从文件读取数据，并显示它
//    infile >> data; 
//    cout << data << endl; 
 
    // infile>>data;
    // cout<<data<<endl;
   // 关闭打开的文件
   
    // cout<<data[1];
//    cout<<data[3];
    // if(data[3]=='\0')
    //     cout<<"hello"<<endl;
    // cout<<data[2];
    infile.getline(data,100);

    // infile>>data;
    cout<<data<<endl;
    // cout<<data[3];
    // cout<<data[2];

    // cout<<data[6];
   //  if(data[5]=='\0')
   //      cout<<endl;
   //  infile>>data;
   //  cout<<data;

   // infile.close();
   // cout<<endl;

   // char c1,c2;

   //  scanf("%c\n", &c1);
   // c2=getchar();

   // cout<<"--------"<<endl;
   // cout<<c1<<"  "<<c2<<endl;

   infile.getline(data, 100);
   cout<<data<<endl;
 
   return 0;
}