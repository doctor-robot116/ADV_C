/*
Поменяйте знак переменной x типа float
 */

#include <stdio.h>
#include <stdint.h>


void changeSign(float *f)
{
    union {
        float f;
        uint32_t u;
    } tmp;
    tmp.f = *f;
    tmp.u = tmp.u ^ 0x80000000;
    *f = tmp.f;
}

int main(void)
{
    float f = -4.0;
    changeSign(&f);
    printf("f = %f\n", f);

    return 0;
}

