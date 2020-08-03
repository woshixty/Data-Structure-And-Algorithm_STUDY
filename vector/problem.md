### Uva 101 the block problem 木块问题

#### 题目大意：

```tex
输入n，得到编号为0~n-1的木块，分别摆放在顺序排列编号为0~n-1的位置。现对这些木块进行操作，操作分为四种。

1、move a onto b：把木块a、b上的木块放回各自的原位，再把a放到b上；

2、move a over b：把a上的木块放回各自的原位，再把a发到含b的堆上；

3、pile a onto b：把b上的木块放回各自的原位，再把a连同a上的木块移到b上；

4、pile a over b：把a连同a上木块移到含b的堆上。

当输入quit时，结束操作并输出0~n-1的位置上的木块情况
```

#### Sample Input 

```tex
10
move 9 onto 1
move 8 over 1
move 7 over 1
move 6 over 1
pile 8 over 6
pile 8 over 5
move 2 over 1
move 4 over 9
quit
```

#### Sample Output

```tex
 0: 0
 1: 1 9 2 4
 2:
 3: 3
 4:
 5: 5 8 7 6
 6:
 7:
 8:
 9:
```

