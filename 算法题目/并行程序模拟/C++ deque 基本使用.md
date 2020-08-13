[deque用法总结](https://blog.csdn.net/sevenjoin/article/details/88530962)<摘自csdn>

### deque 简介

```tex
deque容器为一个给定类型(可以是用户自定义类型)的元素进行线性处理，像向量一样，它能够快速地随机访问任一个元素，并且能够高效地插入和删除容器的尾部元素。但它又与vector不同，deque支持高效插入和删除容器的头部元素，因此也叫做双端队列。
```



### deque的创建和初始化

```c++
deque共提供了6个构造函数, 头文件包含在，这块涉及到内存分配器这些东西，略过不表，在下面我们将接触到一些deque的构造方法，这里要说下的就是，我们通常用如下几种方法构造一个deque：

std::deque<int> dq;	//创建一个empty的int型队列
std::deque<int> dq(8);  //创建一个有8个元素的int型队列，默认初始化值(value)为0
std::deque<int> dq(8, 50);  //创建一个有8个元素的int型队列，默认初始化值(value)都设为50
std::deque<int> dq(dq.begin(), dq.end()); //通过迭代器创建队列
std::deque<int> dq1(dq);	//通过拷贝构造创建队列
```



### deque函数

##### (1)构造函数

```c++
deque():创建一个空deque

deque(int nSize):创建一个deque,元素个数为nSize

deque(int nSize,const T& t):创建一个deque,元素个数为nSize,且值均为t

deque(const deque &):复制构造函数
```

##### (2)增加函数

```c++
void push_front(const T& x):双端队列头部增加一个元素X

void push_back(const T& x):双端队列尾部增加一个元素x

iterator insert(iterator it,const T& x):双端队列中某一元素前增加一个元素x

void insert(iterator it,int n,const T& x):双端队列中某一元素前增加n个相同的元素x

void insert(iterator it,const_iterator first,const_iteratorlast):双端队列中某一元素前插入另一个相同类型向量的[forst,last)间的数据
```

##### (3)删除函数

```c++
Iterator erase(iterator it):删除双端队列中的某一个元素

Iterator erase(iterator first,iterator last):删除双端队列中[first,last）中的元素

void pop_front():删除双端队列中最前一个元素

void pop_back():删除双端队列中最后一个元素

void clear():清空双端队列中最后一个元素
```

##### (4)遍历函数

```c++
reference at(int pos):返回pos位置元素的引用

reference front():返回手元素的引用

reference back():返回尾元素的引用

iterator begin():返回向量头指针，指向第一个元素

iterator end():返回指向向量中最后一个元素下一个元素的指针（不包含在向量中）

reverse_iterator rbegin():反向迭代器，指向最后一个元素

reverse_iterator rend():反向迭代器，指向第一个元素的前一个元素
```

##### (5)判断函数

```c++
bool empty() const:向量是否为空，若true,则向量中无元素
```

##### (6)大小函数

```c++
Int size() const:返回向量中元素的个数

int max_size() const:返回最大可允许的双端对了元素数量值
```

##### (7)其他函数

```c++
void swap(deque&):交换两个同类型向量的数据

void assign(int n,const T& x):向量中第n个元素的值设置为x
```

