#include<stdio.h>
#include<stdlib.h>

void hanoi(int n,char A,char B,char C)
{
    if(n<=1) {
        printf("1 move %c to %c\n",A,C);
        return ;
    }
    hanoi(n-1,A,C,B);
    printf("%d move %c to %c \n",n,A,C);
    hanoi(n-1,B,A,C);
}

int main() {
    int amount;
    scanf("%d", &amount);
    hanoi(amount, 'A', 'B', 'c');
    return 0;
}