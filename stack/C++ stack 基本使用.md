[C++ STL容器——stack用法介绍](https://www.cnblogs.com/MarkKobs-blog/p/10347746.html)



### **简介**

stack是一种容器适配器，专门设计用于在LIFO上下文中操作（后进先出），其中元素仅从容器的一端插入和删除。

容器适配器，而不是一种容器。

它是容器适配器是指，只要支持一系列方法的容器(empty, size, back, push_back, pop_back)，都能作为stack使用。

stack 有可能实际上是一个 vector, deque 或 list. 如果没有特殊指明，将使用 deque作为stack的实际容器。



### **成员函数**

**empty()**

测试栈是否为空，为空返回true，否则返回false。

```
bool empty() const;
```

**size()**

返回栈中元素的个数

```c++
size_type size() const;
```

**top()**

返回栈顶元素(最后push进来的那个)的引用。

```c++
referenc& top();
```

**push(val)**

压一个值到栈中，其值将被初始化为 val

```c++
void push(const value_type& val);
```

**pop()**

将栈顶元素弹出，注意这个函数无返回值，如果需要获取栈顶元素，应先调用top()，再pop()

**swap()**

swap将两个 stack的内容交换。这两个 stack的模板参数 T和 Container必须都相同。

```c++
void swap(stack& x)　重载1：x.swap(y)

void swap(stack& x, stack& y)  重载2: swap(x, y)
```

