/*
Передача функции в функцию
Указатель на функцию задаётся следующим образом:
 */

#include <stdio.h>
#include <stdint.h>

int func(int n) {
    printf("Hello func %d\n",n);
    return n+1;
}
int main()
{
    int (*fp)(int);
    fp = func;
    fp(5);
    return 0;
}

