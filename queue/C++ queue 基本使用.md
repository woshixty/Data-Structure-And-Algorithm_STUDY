 [C++queue容器学习(详解)](https://www.cnblogs.com/ECJTUACM-873284962/p/6741205.html)

### 一.queue模版类的定义在<queue>头文件中

```tex
queue与stack模版非常类似，queue模版也需要定义两个模版参数，一个是元素类型，一个是容器类型，元素类型是必要的，容器类型是可选的，默认为dqueue类型。

定义queue对象的示例代码如下：

queue<int>q1;

queue<double>q2;

queue的基本操作有：

1.入队：如q.push(x):将x元素接到队列的末端；

2.出队：如q.pop() 弹出队列的第一个元素，并不会返回元素的值；

3,访问队首元素：如q.front()

4,访问队尾元素，如q.back();

5,访问队中的元素个数，如q.size();
```

### 二.优先队列

```tex
在<queue>头文件中，还定义了一个非常有用的模版类priority_queue(优先队列），优先队列与队列的差别在于优先队列不是按照入队的顺序出队，而是按照队列中元素的优先权顺序出队（默认为大者优先，也可以通过指定算子来指定自己的优先顺序）。

priority_queue模版类有三个模版参数，元素类型，容器类型，比较算子。其中后两个都可以省略，默认容器为vector，默认算子为less，即小的往前排，大的往后排（出队时序列尾的元素出队）。

定义priority_queue对象的示例代码如下：

priority_queue<int >q1;

priority_queue<pair<int,int> >q2;

priority_queue<int,vector<int>，greater<int> >q3;//定义小的先出队

priority_queue的基本操作均与queue相同

初学者在使用priority_queue时，最困难的可能就是如何定义比较算子了。如果是基本数据类型，或已定义了比较运算符的类，可以直接用STL的less算子和greater算子——默认为使用less算子，即小的往前排，大的先出队。如果要定义自己的比较算子，方法有多种，这里介绍其中的一种：重载比较运算符。优先队列试图将两个元素x和y代入比较运算符(对less算子，调用x<y，对greater算子，调用x>y)，若结果为真，则x排在y前面，y将先于x出队，反之，则将y排在x前面，x将先出队。
```

