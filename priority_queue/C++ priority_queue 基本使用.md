[【c++】STL里的priority_queue用法总结](https://blog.csdn.net/xiaoquantouer/article/details/52015928)<摘抄自csdn>

### **1、头文件**

```c++
#include<queue>
```

### **2、定义**

```c++
priority_queue<int> p;
```

### **3、优先输出大数据**

```tex
priority_queue<Type, Container, Functional>

Type为数据类型， Container为保存数据的容器，Functional为元素比较方式。

如果不写后两个参数，那么容器默认用的是vector，比较方式默认用operator<，也就是优先队列是大顶堆，队头元素最大。
```

例如:

```c++
#include<iostream>
#include<queue>
using namespace std;
 
int main(){
	priority_queue<int> p;
	p.push(1);
	p.push(2);
	p.push(8);
	p.push(5);
	p.push(43);
	for(int i=0;i<5;i++){
		cout<<p.top()<<endl;
		p.pop();
	}
	return 0;
}
```

输出:

```
43
8
5
2
1
```

### **4、优先输出小数据**

```c++
方法一：
priority_queue<int, vector<int>, greater<int> > p;

方法二：自定义优先级，重载默认的 < 符号
#include<iostream>
#include<queue>
#include<cstdlib>
using namespace std;
struct Node{
	int x,y;
	Node(int a=0, int b=0):
		x(a), y(b) {}
};
 
struct cmp{
	bool operator()(Node a, Node b){
		if(a.x == b.x)	return a.y>b.y;
		return a.x>b.x;
	}
};
 
int main(){
	priority_queue<Node, vector<Node>, cmp>p;
	
	for(int i=0; i<10; ++i)
		p.push(Node(rand(), rand()));
		
	while(!p.empty()){
		cout<<p.top().x<<' '<<p.top().y<<endl;
		p.pop();
	}//while
	//getchar();
	return 0;
}
```

