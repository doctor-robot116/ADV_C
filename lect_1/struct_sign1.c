/*
Поменяйте знак с отрицательного переменной x типа int на положительный через побитовые операции
*/
#include <stdio.h>
#include <inttypes.h>

int main()
{
    int32_t a, sign; // например -1 0b1111 1111
    scanf("%d", &a);
    printf("%x\n", a);
    sign = a >> 31;  // записываем маску
    printf("%d\n", a);
    a = a ^ sign;         // если число отрицательное то инверсия
    printf("%x\n", a);
    a = a + (sign & 0x1); // если число было отрицательное то +1
    printf("%x\n", a);
    return 0;
}
