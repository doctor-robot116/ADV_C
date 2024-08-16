/*
Напишите функцию, которая возвращает истину, если знаки двух заданных 32 битных чисел разные. Использовать операции сравнения запрещено

*/


#include <stdio.h>
#include <stdint.h>

_Bool difSign(int32_t a, int32_t b) {
    return (a>>31)^(b>>31);

}

int main(void)
{
    int a = -5, b =10;
    difSign(a,b)?printf("YES\n") : printf("NO\n");
    printf("a = %d, b = %d\n",a,b);
    printf("isEqual = %d\n", difSign(a,b));
    return 0;
}
