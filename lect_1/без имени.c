/*
Проверьте без использования арифметических операторов и операторов сравнения, равны ли два числа
 */

#include <stdio.h>

_Bool isEqual(int a, int b)
{
    return !(a^b);

}

int main(void)
{
    int a = 3, b = 5;
    isEqual(a,b)?printf("YES\n") : printf("NO\n");
    return 0;
}

