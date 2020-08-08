[C++中的STL中map用法详解](https://www.cnblogs.com/fnlingnzb-learner/p/5833051.html)<摘抄自博客园>

### **1、map简介**

```tex
map是一类关联式容器。它的特点是增加和删除节点对迭代器的影响很小，除了那个操作节点，对其他的节点都没有什么影响。

对于迭代器来说，可以修改实值，而不能修改key。
```

###  **2、map的功能**

```tex
自动建立Key － value的对应。key 和 value可以是任意你需要的类型。

根据key值快速查找记录，查找的复杂度基本是Log(N)，如果有1000个记录，最多查找10次，1,000,000个记录，最多查找20次。

快速插入Key -Value 记录。

快速删除记录

根据Key 修改value记录。

遍历所有记录。
```

### **3、使用map**

```tex
使用map得包含map类所在的头文件

#include <map>  //注意，STL头文件没有扩展名.h

map对象是模板类，需要关键字和存储对象两个模板参数：

std:map<int,string> personnel;

这样就定义了一个用int作为索引,并拥有相关联的指向string的指针.

为了使用方便，可以对模板类进行一下类型定义，

typedef map<int,CString> UDT_MAP_INT_CSTRING;

UDT_MAP_INT_CSTRING enumMap;
```

### **4、map的构造函数**

```tex
map共提供了6个构造函数，这块涉及到内存分配器这些东西，略过不表，在下面我们将接触到一些map的构造方法，这里要说下的就是，我们通常用如下方法构造一个map：

map<int, string> mapStudent;
```

### **5、数据的插入**

```tex
map<int, string> mapStudent;

第一种：用insert函数插入pair数据
mapStudent.insert(pair<int, string>(1, "student_one"));

第二种：用insert函数插入value_type数据
mapStudent.insert(map<int, string>::value_type (1, "student_one"));

第三种：用数组方式插入数据
mapStudent[1] = "student_one";
```

### **6、map的大小**

```tex
可以用size函数
Int nSize = mapStudent.size();
```

### **7、数据的遍历**

```tex
第一种：应用前向迭代器
for(iter = mapStudent.begin(); iter != mapStudent.end(); iter++)
	cout<<iter->first<<' '<<iter->second<<endl;

第二种：应用反相迭代器
for(iter = mapStudent.rbegin(); iter != mapStudent.rend(); iter++)
	cout<<iter->first<<"  "<<iter->second<<endl;
	
第三种，用数组的形式
for(int nindex = 1; nindex <= nSize; nindex++)
	cout<<mapStudent[nindex]<<endl;
```

### **8、查找并获取map中的元素**

```tex
第一种：用count函数来判定关键字是否出现，其缺点是无法定位数据出现位置,由于map的特性，一对一的映射关系，就决定了count函数的返回值只有两个，要么是0，要么是1，出现的情况，当然是返回1了

第二种：用find函数来定位数据出现位置，它返回的一个迭代器，当数据出现时，它返回数据所在位置的迭代器，如果map中没有要查找的数据，它返回的迭代器等于end函数返回的迭代器。

#include <map>  
#include <string>  
#include <iostream>   
using namespace std;  
  
int main()  
  
{
    map<int, string> mapStudent;
    mapStudent.insert(pair<int, string>(1, "student_one"));
    mapStudent.insert(pair<int, string>(2, "student_two"));
    mapStudent.insert(pair<int, string>(3, "student_three"));  
  
    map<int, string>::iterator iter;
    iter = mapStudent.find(1);  
  
    if(iter != mapStudent.end())
       cout<<"Find, the value is "<<iter->second<<endl;
    else  
       cout<<"Do not Find"<<endl;  
      
    return 0;  
}  

```

## **map的基本操作函数**

```tex
		 begin()         返回指向map头部的迭代器

     clear(）        删除所有元素

     count()         返回指定元素出现的次数

     empty()         如果map为空则返回true

     end()           返回指向map末尾的迭代器

     equal_range()   返回特殊条目的迭代器对

     erase()         删除一个元素

     find()          查找一个元素

     get_allocator() 返回map的配置器

     insert()        插入元素

     key_comp()      返回比较元素key的函数

     lower_bound()   返回键值>=给定元素的第一个位置

     max_size()      返回可以容纳的最大元素个数

     rbegin()        返回一个指向map尾部的逆向迭代器

     rend()          返回一个指向map头部的逆向迭代器

     size()          返回map中元素的个数

     swap()           交换两个map

     upper_bound()    返回键值>给定元素的第一个位置

     value_comp()     返回比较元素value的函数
```

