/*
Напишите функцию, которая вычитает единицу в случае, если число чётное, или не меняет его.
Использовать арифметические операции запрещено

*/


#include <stdio.h>
#include <stdint.h>

int div1IfEven(int a) {
    return a - !(a&0x1);
}


int main(void)
{
    int a = -5;
    difSign(a,b)?printf("YES\n") : printf("NO\n");
    printf("a = %d, b = %d\n",a,b);
    printf("isEqual = %d\n", difSign(a,b));
    return 0;
}
