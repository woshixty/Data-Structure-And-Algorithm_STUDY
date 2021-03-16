### UVA 156 - Ananagrams (map)

##### description

```tex
Most crossword puzzle fans are used to anagrams--groupsof words with the same letters in different orders--for exampleOPTS, SPOT, STOP, POTS and POST. Some words however do not have thisattribute, no matter how you rearrange their letters, you cannot formanother word. Such words are called ananagrams, an example isQUIZ.

Obviously such definitions depend on the domain within which we areworking; you might think that ATHENE is an ananagram, whereas anychemist would quickly produce ETHANE. One possible domain would be theentire English language, but this could lead to some problems. Onecould restrict the domain to, say, Music, in which case SCALE becomesarelative ananagram (LACES is not in the same domain) but NOTEis not since it can produce TONE.

Write a program that will read in the dictionary of a restricteddomain and determine the relative ananagrams. Note that single letterwords are, ipso facto, relative ananagrams since they cannot be``rearranged'' at all. The dictionary will contain no morethan 1000 words.
```

##### input

```tex
Input will consist of a series of lines. No line will be more than 80characters long, but may contain any number of words. Words consist ofup to 20 upper and/or lower case letters, and will not be brokenacross lines. Spaces may appear freely around words, and at least onespace separates multiple words on the same line. Note that words thatcontain the same letters but of differing case are considered to beanagrams of each other, thus tIeD and EdiT are anagrams. The file willbe terminated by a line consisting of a single #.
```

##### output

```tex
Output will consist of a series of lines. Each line will consist of asingle word that is a relative ananagram in the input dictionary.Words must be output in lexicographic (case-sensitive) order. Therewill always be at least one relative ananagram.
```

