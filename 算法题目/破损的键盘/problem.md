### UVA11988 Broken Keyboard

[UVA11988 Broken Keyboard](https://blog.csdn.net/lianai911/article/details/41831645)<摘自csdn>



> 这道关于链表题说实话挺有意思的
>
> 反正让我大吃一惊
>
> 改天抽时间还得仔细研究研究



##### Description

````tex
You're typing a long text with a broken keyboard. Well it's not so badly broken. The only problem with the keyboard is that sometimes the "home" key or the "end" key gets automatically pressed (internally).

You're not aware of this issue, since you're focusing on the text and did not even turn on the monitor! After you finished typing, you can see a text on the screen (if you turn on the monitor).

In Chinese, we can call it Beiju. Your task is to find the Beiju text.
````

##### Input

```tex
There are several test cases. Each test case is a single line containing at least one and at most 100,000 letters, underscores and two special characters '[' and ']'. '[' means the "Home" key is pressed internally, and ']' means the "End" key is pressed internally. The input is terminated by end-of-file (EOF). The size of input file does not exceed 5MB.
```

##### Output

```tex
For each case, print the Beiju text on the screen.
```

##### Sample Input

```tex
This_is_a_[Beiju]_text
[[]][][]Happy_Birthday_to_Tsinghua_University
```

##### Output for the Sample Input

```tex
BeijuThis_is_a__text
Happy_Birthday_to_Tsinghua_University
```

##### 题目大意：

```tex
你在输入文章的时候，键盘上的Home键和End键出了问题，会不定时的按下。

给你一段按键的文本，其中'['表示Home键，']'表示End键，输出这段悲剧的文本。

思路：使用链表来模拟，遇到Home键，就将后边的文本插入到这段文本的最前边，遇到

End键，就插入到这段文本的最后边。但是用链表会用到指针，过程比较繁琐。这里用一个

Next数组模拟指向，Next[i]表示当前显示屏中s[i]右边的字符下标。再用一个cur表示当前

光标的位置，last表示最后一个字符的记录位置，这样遇到End键，就能直接找到光标下一

个指向的字符位置了。
```

