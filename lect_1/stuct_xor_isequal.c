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
    int a = 29, b = 29;
    isEqual(a,b)?printf("YES\n") : printf("NO\n");
    printf("a = %d, b = %d\n",a,b);
    printf("isEqual = %d\n", isEqual(a,b));
    return 0;
}



